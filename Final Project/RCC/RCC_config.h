/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 8 April 2023												   	  */
/* Version  : V01	                                        				  */
/******************************************************************************/
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H
  


/* Options: 	RCC_HSE_CRYSTAL
				RCC_HSE_RC
				RCC_HSI		(16 MHZ)
				RCC_PLL			  */	
#define RCC_COLCK_TYPE    RCC_HSI


/* Note: Select a value only if you chose PLL as Input Clock Source */
/* Options:		RCC_PLL_IN_HSI
				RCC_PLL_IN_HSE			*/
#if RCC_COLCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT 	    RCC_PLL_IN_HSE
#define RCC_PLL_N			336				/* Multiplication Factor (2 --> 510) 433 IS WRONG*/
#define RCC_PLL_M			8				/* I/P Clock Division Factor (2 --> 63)*/
#define RCC_PLL_P			4				/* O/P Clock Division Factor (2,4,6,8) */
#endif

/* O/P Clock = PLL *  PLLN
					 -------
					 PLLM * PLLP   */

#endif
