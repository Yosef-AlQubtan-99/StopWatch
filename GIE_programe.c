/*
 * GIE_programe.c
 *
 *  Created on: Aug 28, 2023
 *      Author: yosef
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "GIE_interface.h"
#include "GIE_register.h"



void GIE_voidEnable(void)
{
	SET_BIT(SREG , 7);
}
void GIE_voidDisable(void)
{
	CLR_BIT(SREG , 7);
}
