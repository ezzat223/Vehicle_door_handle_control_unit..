/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 7 May 2023												   	  */
/* Version  : V01	                                        				  */
/******************************************************************************/

#ifndef GPT_INTERFACE_H
#define GPT_INTERFACE_H

/* Initialize the GPT registers with the needed initial values to support the needed timing actions */
void GPT_Init(void);

/* request the GPT to start and send its number of tickets before timer overflow and stop */
void GPT_StartTimer(uint32 OverFlowTicks);

/* return (1) if an overflow occurred after the last call of GPT_StartTimer and 
          (0) if no overflow occurred or GPT_StartTimer wasn't not called from the last read */
uint8 GPT_CheckTimeIsElapsed(void);

/* return number of elapsed ticks from the last call of the GPT_StartTimer, 
        0 if it is not called and 
        0xffffffff if an overflow occurred                                                          */
uint32 GPT_GetElapsedTime(void);

/* return number of remaining ticks till the overflow ticks passed to GPT_StartTimer, 
          0xffffffff if GPT_startTime is not called, 
          0 if an overflow occurred                                                         */
uint32 GPT_GetRemainingTime(void);

/* GPT delay function */
void GPT_Delay(uint32 seconds);

#define HALF_SEC        499
#define ONE_SEC         999
#define TWO_SEC         1999
#define TEN_SEC         9999

#endif
