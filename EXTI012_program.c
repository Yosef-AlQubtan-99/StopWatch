/*
 * ext_program.c
 *
 *  Created on: Aug 28, 2023
 *      Author: yosef
 */

#include  "STD_TYPES.h"
#include  "BIT_MATH.h"

#include  "DIO_interface.h"

#include  "EXTI0_register.h"
#include "EXTI012_config.h"
#include "EXTI012_interface.h"
#include "EXTI012_private.h"

void (*EXTI0_CallBack)(void);                   //global ptr points to a function for
												//receiving the address of the function ptr as a global
                                                //variable to be seen by void __vector_1(void)

void (*EXTI1_CallBack)(void);
void (*EXTI2_CallBack)(void);



void EXTI0_voidInit(void)
{
	switch(SENSE)
	{
	case LOW_LEVEL :
					CLR_BIT(MCUCR ,0);
					CLR_BIT(MCUCR ,1);
					break;

	case ANY_CHANGE :
					SET_BIT(MCUCR ,0);
					CLR_BIT(MCUCR ,1);
					break;

	case FALLING_EDGE :
					CLR_BIT(MCUCR ,0);
					SET_BIT(MCUCR ,1);
					break;

	case RISING_EDGE :
					SET_BIT(MCUCR ,0);
					SET_BIT(MCUCR ,1);
					break;

	}

	SET_BIT(GICR,6);                         //Activating PIE of INT0
}

void EXTI0_voidDisableInt(void)
{
	CLR_BIT(GICR,6);                         //DeActivating PIE of INT0
}


void EXTI1_voidInit(void)
{
	switch(SENSE)
	{
	case LOW_LEVEL :
					CLR_BIT(MCUCR ,0);
					CLR_BIT(MCUCR ,1);
					break;

	case ANY_CHANGE :
					SET_BIT(MCUCR ,0);
					CLR_BIT(MCUCR ,1);
					break;

	case FALLING_EDGE :
					CLR_BIT(MCUCR ,0);
					SET_BIT(MCUCR ,1);
					break;

	case RISING_EDGE :
					SET_BIT(MCUCR ,0);
					SET_BIT(MCUCR ,1);
					break;

	}

	SET_BIT(GICR,7);                         //Activating PIE of INT1
}

void EXTI1_voidDisableInt(void)
{
	CLR_BIT(GICR,7);                         //DeActivating PIE of INT1
}

void EXTI2_voidInit(void)
{
	switch(SENSE)
	{
	case LOW_LEVEL :
					CLR_BIT(MCUCR ,0);
					CLR_BIT(MCUCR ,1);
					break;

	case ANY_CHANGE :
					SET_BIT(MCUCR ,0);
					CLR_BIT(MCUCR ,1);
					break;

	case FALLING_EDGE :
					CLR_BIT(MCUCR ,0);
					SET_BIT(MCUCR ,1);
					break;

	case RISING_EDGE :
					SET_BIT(MCUCR ,0);
					SET_BIT(MCUCR ,1);
					break;

	}

	SET_BIT(GICR,5);                         //Activating PIE of INT2
}

void EXTI2_voidDisableInt(void)
{
	CLR_BIT(GICR,5);                         //DeActivating PIE of INT2
}

void EXTI0_voidSetCallBack(void (*Copy_pvCallBack)(void))
{
	EXTI0_CallBack = Copy_pvCallBack;
}

void EXTI1_voidSetCallBack(void (*Copy_pvCallBack)(void))
{
	EXTI1_CallBack = Copy_pvCallBack;
}

void EXTI2_voidSetCallBack(void (*Copy_pvCallBack)(void))
{
	EXTI2_CallBack = Copy_pvCallBack;
}


void __vector_1(void) __attribute__((signal));                  //attribute used for communicating compiler by (signal) signal tells comp.
                                                                //that microcontroller will execute this function
																//vector_1 obtained from the vector table in the data sheet
																//table 18 page 42
void __vector_1(void)
{
	EXTI0_CallBack();
}

void __vector_2(void) __attribute__((signal));


void __vector_2(void)
{
	EXTI1_CallBack();
}

void __vector_3(void) __attribute__((signal));


void __vector_3(void)
{
	EXTI2_CallBack();
}
