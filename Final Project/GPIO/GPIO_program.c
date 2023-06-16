/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 7 JUNE 2023												   	  */
/* Version  : V02	                                        				  */
/******************************************************************************/

#include	"STD_TYPES.h"
#include	"BIT_MATH.h"

#include	"GPIO_config.h"
#include	"GPIO_interface.h"
#include	"GPIO_private.h"

#include 	"GPT_interface.h"
#include	"RCC_interface.h"

#define GPIO_REG(REG_ID, PORT_ID) ((uint32 *)((PORT_ID) + (REG_ID)))

uint32 gpioAddresses[2] = 
{
	GPIOA_BASE_ADDR,
	GPIOB_BASE_ADDR
};


void GPIO_Init(void)
{
	/* Initialize System Clock */
	RCC_voidInitSysClock();

	/* Enable Clock for a Peripheral on a BUS */
	#if   GPIO_PORT == GPIO_A
		RCC_voidEnableClock(RCC_GPIOA);
	#elif GPIO_PORT == GPIO_B
		RCC_voidEnableClock(RCC_GPIOB);
	#endif

	uint32 *gpio_moder  = GPIO_REG(GPIOx_MODER,  gpioAddresses[GPIO_PORT]);
	uint32 *gpio_otyper = GPIO_REG(GPIOx_OTYPER, gpioAddresses[GPIO_PORT]);
	uint32 *gpio_pupdr  = GPIO_REG(GPIOx_PUPDR,  gpioAddresses[GPIO_PORT]);

	/* Intitialize Buttons as Input PULL_UP */
	for(uint8 button = HANDLE_BUTTON_PIN; button <= HANDLE_BUTTON_PIN+1; button++)
	{
		*gpio_moder &= ~(0x03 << (2*button));

		*gpio_pupdr &= ~(0x03 << (2*button));
		*gpio_pupdr |=  (1    << (2*button));
		
	}

	/* Intitialize LEDs as OUTPUT  PUSH_PULL */
	for(uint8 led = VEHICLE_LOCK_LED_PIN; led <= VEHICLE_LOCK_LED_PIN+2; led++)
	{
		*gpio_moder &= ~(0x03 << 2*led);
		*gpio_moder |=  (1    << 2*led);

		CLR_BIT(*gpio_otyper, led);

	}
}


/* A function to set a value (1 or 0) to a specific pin. */
void GPIO_WritePinValue(uint8 PinId,uint8 PinData)
{
	uint32 *gpio_odr = GPIO_REG(GPIOx_ODR, gpioAddresses[GPIO_PORT]);

	CLR_BIT(*gpio_odr, PinId);
	*gpio_odr |= (PinData << PinId);
}


uint8 GPIO_ReadPinState(uint8 PinId)
{
	uint32 *gpio_idr = GPIO_REG(GPIOx_IDR, gpioAddresses[GPIO_PORT]);
	uint8 LOC_uint8Result = 0;

	LOC_uint8Result = GET_BIT(*gpio_idr, PinId);
	return LOC_uint8Result;
}


/* (1) if falling edge , 0 otherwise */
uint8 BUTTON_ReadState(uint8 PinId)
{
	static uint8 prevState = 1;

	if((!GPIO_ReadPinState(PinId)) && (prevState == 1))
	{
		GPT_Delay(0.1);
		if(!GPIO_ReadPinState(PinId))
		{
			prevState = 0;
			return 1;
		}
	}
	else if(GPIO_ReadPinState(PinId))
	{
		prevState = 1;
		return LOCKED;
	}
	else
	{
		return 0;
	}
}
