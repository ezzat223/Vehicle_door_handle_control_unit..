/******************************************************************************/
/* Author   : Ezzat Hegazy												            	   */
/* Date     : 7 JUNE 2023												            	   */
/* Version  : V04	                                        				         */
/******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPT_config.h"
#include "GPT_interface.h"
#include "GPT_private.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"


extern uint32 GPT_GlobalTicks;


// /* Initialize the GPT registers with the needed initial values to support the needed timing actions */
void GPT_Init(void)
{
   /* Initialize Clock on TIM2 */
   RCC_voidEnableClock(RCC_TIM2);

   /* Set PSC */
   TIM2 -> PSC = PSC_VALUE;

   /* set the Auto-reload value to the same value */
	TIM2 -> ARR = 4999;

   // Enable the counter
   SET_BIT(TIM2 -> CR1, 0);

   while(!GET_BIT(TIM2 -> SR, 0));

   CLR_BIT(TIM2 -> SR, 0);
}

/* request the GPT to start and send its number of tickets before timer overflow and stop */
void GPT_StartTimer(uint32 OverFlowTicks)
{
   CLR_BIT(TIM2 -> CR1, 0);
   CLR_BIT(TIM2 -> SR, 0);
	GPT_GlobalTicks = OverFlowTicks;
	TIM2 -> CNT = 0;
	TIM2 -> ARR = OverFlowTicks;

   // Enable the counter
   SET_BIT(TIM2 -> CR1, 0);
}

/* return (1) if an overflow occurred after the last call of GPT_StartTimer
      (0) if no overflow occurred **OR** GPT_StartTimer wasn't not called from the last read */
uint8 GPT_CheckTimeIsElapsed(void)
{
   if ((TIM2 -> SR & (1 << 0)) == 1)
   {
       // Timer has elapsed, reset the timer started flag
      GPT_GlobalTicks = 0;
      CLR_BIT(TIM2 -> SR, 0);
      return 1;
   }
   else
   {
      return 0;
   }
}

/* return number of elapsed ticks from the last call of the GPT_StartTimer,
      0 if it is not called and
      0xffffffff if an overflow occurred                                                          */
uint32 GPT_GetElapsedTime(void)
{
   uint32 elapsedTicks = TIM2 -> CNT;
   if ((TIM2 -> SR & (1 << 0)) == 1)
   {
      return 0xffffffff;
   }
   else if(GPT_GlobalTicks == 0)
   {
      return 0;
   }
   else
   {
      return elapsedTicks;
   }
}

/* return number of remaining ticks till the overflow ticks passed to GPT_StartTimer,
      0xffffffff if GPT_startTime is not called,
      0 if an overflow occurred                                                         */
uint32 GPT_GetRemainingTime(void)
{
   uint32 elapsedTicks = TIM2 -> CNT;
   if (GET_BIT(TIM2 -> SR, 0) == 1)
   {
      return 0;
   }
   else if(GPT_GlobalTicks == 0)
   {
      return 0xffffffff;
   }
   else
   {
      return ((TIM2 -> ARR) - elapsedTicks);
   }
}

      /* Delay */
void GPT_Delay(uint32 seconds)
{
   uint32 goal = (seconds*1000)-1;
   if(TIM2 -> CNT == 0)
   {
      CLR_BIT(TIM2 -> CR1, 0);
      CLR_BIT(TIM2 -> SR, 0);
      TIM2 -> ARR = 0xffffffff;
      SET_BIT(TIM2 -> CR1, 0);
      while((TIM2 -> CNT) < goal);
   }
   else
   {
      uint32 current = (TIM2 -> CNT);
      while((TIM2 -> CNT) < (current + goal));
   }
}