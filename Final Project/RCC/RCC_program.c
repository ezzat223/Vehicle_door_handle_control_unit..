/******************************************************************************/
/* Author   : Ezzat Hegazy											                        		  */
/* Date     : 12 April 2023										                      		   	  */
/* Version  : V02	                                                   				  */
/******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_config.h"
#include "RCC_interface.h"
#include "RCC_private.h"

				/*      RCC APIs    */
/*  Initialize System Clock */
void RCC_voidInitSysClock(void)
{ 
	#if   RCC_CLOCK_TYPE ==   RCC_HSE_CRYSTAL
		RCC_CR   = 0x00010000;
		RCC_CFGR = 0x00000001;
		
	#elif RCC_CLOCK_TYPE ==   RCC_HSE_RC
		RCC_CR   = 0x00050000;
		RCC_CFGR = 0x00000001;
		
	#elif RCC_CLOCK_TYPE ==   RCC_HSI
		RCC_CR   = 0x00000001;    // 8 is for trimming
		RCC_CFGR = 0x00000000;
		
	#elif RCC_CLOCK_TYPE ==   RCC_PLL
		#if		RCC_PLL_INPUT == RCC_PLL_IN_HSI
      RCC_PLLCFGR = 0x00000000;
      RCC_PLLCFGR |= RCC_PLL_M;
      RCC_PLLCFGR |= (RCC_PLL_N << 6);
      RCC_PLLCFGR |= (RCC_PLL_P << 16);

      RCC_CR      = 0x01000081;    // 8 is for trimming
      RCC_CFGR    = 0x00000002;
		#elif	RCC_PLL_INPUT == RCC_PLL_IN_HSE
      RCC_PLLCFGR = 0x00000000;
      RCC_PLLCFGR |= RCC_PLL_M;
      RCC_PLLCFGR |= (RCC_PLL_N << 6);
      RCC_PLLCFGR |= (RCC_PLL_P << 16);

      RCC_CR      = 0x01010000;
      RCC_CFGR    = 0x00000002;
		#endif
	
	#else
		#error("You chose Wrong clock type")
	#endif
}


/* Enable Clock for a Peripheral on a BUS */
void RCC_voidEnableClock(Rcc_PeripheralIdType PeripheralId)
{
  uint8 BusId = PeripheralId / 32;
  uint8 PeripheralBitPosition = PeripheralId % 32;
  switch (BusId) {
    case RCC_AHB1:
      SET_BIT(RCC_AHB1ENR, PeripheralBitPosition);
      break;
    case RCC_AHB2:
      SET_BIT(RCC_AHB2ENR, PeripheralBitPosition);
      break;
    case RCC_APB1:
      SET_BIT(RCC_APB1ENR, PeripheralBitPosition);
      break;
    case RCC_APB2:
      SET_BIT(RCC_APB2ENR, PeripheralBitPosition);
      break;
    default:
      break;
  }

}

/* Disable Clock for a Peripheral */
void RCC_voidDisableClock(Rcc_PeripheralIdType PeripheralId)
{
  uint8 BusId = PeripheralId / 32;
  uint8 PeripheralBitPosition = PeripheralId % 32;
  switch (BusId) {
    case RCC_AHB1:
      CLR_BIT(RCC_AHB1RSTR, PeripheralBitPosition);
      break;
    case RCC_AHB2:
      CLR_BIT(RCC_AHB2RSTR, PeripheralBitPosition);
      break;
    case RCC_APB1:
      CLR_BIT(RCC_APB1RSTR, PeripheralBitPosition);
      break;
    case RCC_APB2:
      CLR_BIT(RCC_APB2RSTR, PeripheralBitPosition);
      break;
    default:
      break;
  }
}

void delay(uint32 w)
{
	for (uint16 i = 0; i < w; i++)
	{
		for (uint16 j = 0; j < w; j++)
		{
			/* Assembly order No OPeration */
			asm("NOP");
		}
	}
}
