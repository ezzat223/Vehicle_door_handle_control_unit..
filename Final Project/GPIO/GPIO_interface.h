/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 02 May 2023												   	  */
/* Version  : V01	                                        				  */
/******************************************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
#include "STD_TYPES.h"

		/* Define Ports */
#define 	GPIO_A  0
#define 	GPIO_B  1
#define 	GPIO_C  2
#define 	GPIO_D  3

		/* Define PIN_S */
#define		PIN0	0
#define		PIN1	1
#define		PIN2	2
#define		PIN3	3
#define		PIN4	4
#define		PIN5	5
#define		PIN6	6
#define		PIN7	7
#define		PIN8	8
#define		PIN9	9
#define		PIN10	10
#define		PIN11	11
#define		PIN12	12
#define		PIN13	13
#define		PIN14	14
#define		PIN15	15

		/*PinMode   (MODER) */
#define 	GPIO_INPUT  0
#define 	GPIO_OUTPUT 1
#define 	GPIO_AF     2
#define 	GPIO_ANALOG 3

		/*DefaultState*/
		/* OutPut Type (OTYPER) */
#define 	OUTPUT_PUSH_PULL  0
#define 	OUTPUT_OPEN_DRAIN 1

		/* InPut Type (PUPDR) */
#define 	INPUT_NO_PULL		0
#define 	INPUT_PULL_UP		1
#define 	INPUT_PULL_DOWN		2


		/* Data */
#define 	LOW  	0
#define 	HIGH 	1

/* initialize the GPIO registers with the initial values to support the connected hardware actions.*/
void GPIO_Init(void);

/* A function to set a value (1 or 0) to a specific pin. */
void GPIO_WritePinValue(uint8 PinId,uint8 PinData);

/* (1) if falling edge , 0 otherwise */
uint8 GPIO_ReadPinState(uint8 PinId);

/* Falling, Rising, Idle */
uint8 BUTTON_ReadState(uint8 PinId);

#endif





