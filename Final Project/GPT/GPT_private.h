/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 7 May 2023												   	  */
/* Version  : V01	                                        				  */
/******************************************************************************/
#ifndef GPT_PRIVATE_H
#define GPT_PRIVATE_H

#include "STD_TYPES.h"

typedef struct 
{
    uint32 CR1;    
    uint32 CR2;    
    uint32 SMCR;    
    uint32 DIER;    
    uint32 SR;     
    uint32 EGR;    
    uint32 CCMR1;  
    uint32 CCMR2;   
    uint32 CCER;
    uint32 CNT;    
    uint32 PSC;    
    uint32 ARR;
    uint32 RESERVED1;  
    uint32 CCR1;    
    uint32 CCR2;    
    uint32 CCR3;    
    uint32 CCR4; 
    uint32 RESERVED2;            
    uint32 DCR;   
    uint32 DMAR; 
    uint32 OR;    // TIM2 & TIM5
} TIM_t;

                    /* APB1 */
#define     TIM2    ((volatile TIM_t *) 0x40000000)
#define     TIM3    ((volatile TIM_t *) 0x40000400)
#define     TIM4    ((volatile TIM_t *) 0x40000800)
#define     TIM5    ((volatile TIM_t *) 0x40000C00)


#endif
