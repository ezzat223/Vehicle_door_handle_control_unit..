/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 02 May 2023												   	  */
/* Version  : V01	                                        				  */
/******************************************************************************/
#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include "Utils.h"
#include "STD_TYPES.h"


#define     GPIO_PORT               GPIO_A
/*              OPTIONS 
            ----------------
                GPIO_A
                GPIO_B
                GPIO_C
                GPIO_D                  */


#define     HANDLE_BUTTON_PIN           0
#define     DOOR_BUTTON_PIN             1

#define     VEHICLE_LOCK_LED_PIN        3
#define     HAZARD_LED_PIN              4
#define     AMBIENT_LIGHT_LED_PIN       5

#define     LOCKED                      2


#endif
