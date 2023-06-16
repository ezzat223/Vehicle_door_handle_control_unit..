/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 7 JUNE 2023												   	  */
/* Version  : V03	                                        				  */
/******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "GPT_interface.h"

uint32 GPT_GlobalTicks = 0;

void door_unlock(void)
{
    GPT_StartTimer(TWO_SEC);
    /* VEHICLE ON */
    GPIO_WritePinValue(VEHICLE_LOCK_LED_PIN, HIGH);
    /* HAZARD Blinking (1 time only) each 0.5 SEC */
    GPIO_WritePinValue(HAZARD_LED_PIN, HIGH);
    /* AMBIENT ON for 2 SEC then OFF */
    GPIO_WritePinValue(AMBIENT_LIGHT_LED_PIN, HIGH);
    while(!GPT_CheckTimeIsElapsed())
    {      
        if(GPT_GetElapsedTime() == HALF_SEC)
        {
            GPIO_WritePinValue(HAZARD_LED_PIN, LOW);
        }
    }
    GPIO_WritePinValue(AMBIENT_LIGHT_LED_PIN, LOW);
}

void door_is_open(void)
{
    /* VEHICLE OFF */
    GPIO_WritePinValue(VEHICLE_LOCK_LED_PIN, LOW);
    /* HAZARD OFF */
    GPIO_WritePinValue(HAZARD_LED_PIN, LOW);
    /* AMBIENT ON */
    GPIO_WritePinValue(AMBIENT_LIGHT_LED_PIN, HIGH);
}

void anti_theft_vehicle_lock(void)
{
    GPT_StartTimer(TWO_SEC);
    /* VEHICLE OFF */
    GPIO_WritePinValue(VEHICLE_LOCK_LED_PIN, LOW);
    /* AMBIENT OFF */
    GPIO_WritePinValue(AMBIENT_LIGHT_LED_PIN, LOW);

    /* HAZARD Blinking (2 times only) each 0.5 SEC */
    GPIO_WritePinValue(HAZARD_LED_PIN, HIGH);
    while(!GPT_CheckTimeIsElapsed())
    {
        if(GPT_GetElapsedTime() == HALF_SEC)
        {
            GPIO_WritePinValue(HAZARD_LED_PIN, LOW);
        }
        if(GPT_GetElapsedTime() == ONE_SEC)
        {
            GPIO_WritePinValue(HAZARD_LED_PIN, HIGH);
        }
        if(GPT_GetRemainingTime() == HALF_SEC)
        {
            GPIO_WritePinValue(HAZARD_LED_PIN, LOW);
        }
    }
}

void closing_the_door()
{
    GPT_StartTimer(ONE_SEC);
    /* VEHICLE OFF */
    GPIO_WritePinValue(VEHICLE_LOCK_LED_PIN, LOW);
    /* HAZARD OFF */
    GPIO_WritePinValue(HAZARD_LED_PIN, LOW);
    /* AMBIENT ON for 1 sec then OFF */
    GPIO_WritePinValue(AMBIENT_LIGHT_LED_PIN, HIGH);

    while(!GPT_CheckTimeIsElapsed())
    {
        if(GPT_CheckTimeIsElapsed())
        {
            GPIO_WritePinValue(AMBIENT_LIGHT_LED_PIN, LOW);
        }
    }
}

void locking_the_door(void)
{
    GPT_StartTimer(TWO_SEC);
    /* VEHICLE OFF */
    GPIO_WritePinValue(VEHICLE_LOCK_LED_PIN, LOW);
    /* AMBIENT OFF */
    GPIO_WritePinValue(AMBIENT_LIGHT_LED_PIN, LOW);
    /* HAZARD Blinking (2 times only) each 0.5 SEC */
    GPIO_WritePinValue(HAZARD_LED_PIN, HIGH);

    while(!GPT_CheckTimeIsElapsed())
    {
        if(GPT_GetElapsedTime() == HALF_SEC)
        {
            GPIO_WritePinValue(HAZARD_LED_PIN, LOW);
        }
        if(GPT_GetElapsedTime() == ONE_SEC)
        {
            GPIO_WritePinValue(HAZARD_LED_PIN, HIGH);
        }
        if(GPT_GetRemainingTime() == HALF_SEC)
        {
            GPIO_WritePinValue(HAZARD_LED_PIN, LOW);
        }
    }
}

int main(void)
{
    /* Initialize GPIO & Default State */
    GPIO_Init();

    /* Initialize Clock on TIM2 */
    GPT_Init();

    while (1)
    {
                     /* Door unlock */
        /* Handle button is pressed */
        if(BUTTON_ReadState(HANDLE_BUTTON_PIN) == 1)
        {
            door_unlock();
            uint8 flag1 = 1;
            /* For Antitheft */
            GPT_StartTimer(TEN_SEC);
            while (flag1)
            {
                            /* Door is Open */
                /* Door unlock button is Pressed */
                if(BUTTON_ReadState(DOOR_BUTTON_PIN) == 1)
                {
                    door_is_open();
                    uint8 flag2=1;
                    while (flag2)
                    {
                                /* Closing the Door */
                        /* Door Lock button is Pressed */
                        if(BUTTON_ReadState(DOOR_BUTTON_PIN) == LOCKED)
                        {
                            closing_the_door();
                            uint8 flag3 =1;
                            while (flag3)
                            {
                                            /* Locking the Door */
                                /* Handle Lock button is Pressed */
                                if(BUTTON_ReadState(HANDLE_BUTTON_PIN) == LOCKED)
                                {
                                    locking_the_door();
                                    while((BUTTON_ReadState(HANDLE_BUTTON_PIN) == LOCKED) && (BUTTON_ReadState(DOOR_BUTTON_PIN) == LOCKED));
                                }
                            }
                        }
                    } 
                }
                            /* Anti theft lock */
                /* No buttons pressed for 10 sec */
                if(GPT_CheckTimeIsElapsed())
                {
                    anti_theft_vehicle_lock();
                    while(1);
                }
            }
        }
    }
    return 1;
}
