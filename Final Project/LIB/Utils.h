/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 12 April 2023												   	  */
/* Version  : V01	                                        				  */
/******************************************************************************/
#ifndef UTILS_H
#define UTILS_H

#include "STD_TYPES.h"
#define REG32(BASE_ADDR, OFFSET)  (*(volatile uint32 *)((BASE_ADDR) + (OFFSET)))

#endif /* UTILS_H */
