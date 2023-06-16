/******************************************************************************/
/* Author   : Ezzat Hegazy													  */
/* Date     : 8 April 2023												   	  */
/* Version  : V01	                          CHANGE IT EVERY TIME YOU CHANGE */
/******************************************************************************/
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR, BIT)       VAR |= (1 << (BIT))
#define CLR_BIT(VAR, BIT)       (VAR &= ~(1 << (BIT)))
#define GET_BIT(VAR, BIT)       ((VAR >> BIT) & 1)
#define TOG_BIT(VAR, BIT)       VAR ^= (1 << (BIT))

#endif
