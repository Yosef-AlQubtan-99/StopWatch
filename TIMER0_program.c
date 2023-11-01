/*
 * TIMER0_program.c
 *
 *  Created on: Aug 31, 2023
 *      Author: mostafa.mohammady
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER0_register.h"
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"


//Operating in CTC mode

void (*TIMER0_CallBack)(void);              //Global pointer
											//preferred static void (*TIMER0_CallBack)(void)=NULL;

void TIMER0_voidInit(void)
{
	//Select timer mode

#if (TIMER0_MODE==NORMAL_MODE)
	{
		CLR_BIT(TCCR0 ,6);
		CLR_BIT(TCCR0 ,3);

	}
#elif (TIMER0_MODE==CTC_MODE)
	{
		CLR_BIT(TCCR0 ,6);
		SET_BIT(TCCR0 ,3);

	}
#endif

	//Select PreScaler : Divide by 8
	CLR_BIT(TCCR0,2);
	SET_BIT(TCCR0,1);
	CLR_BIT(TCCR0,0);

	//Set the compare match
	OCR0 = TIMER0_OCRVAL;                  //OCR0=250


//Enabling timer interrupt
#if (TIMER0_MODE==NORMAL_MODE)
	{
		SET_BIT(TIMSK ,0);

	}
#elif (TIMER0_MODE==CTC_MODE)
	{

		SET_BIT(TIMSK ,1);

	}
#endif


}


void Timer0_voidPause(void)
{
	//Select PreScaler : No clock source
	CLR_BIT(TCCR0,2);
	CLR_BIT(TCCR0,1);
	CLR_BIT(TCCR0,0);
}
void Timer0_voidResume(void)
{
	//Select PreScaler : Divide by 8
	CLR_BIT(TCCR0,2);
	SET_BIT(TCCR0,1);
	CLR_BIT(TCCR0,0);
}


void TIMER0_voidSetOCRVal(u8 Copy_u8Val)
{
	OCR0 = Copy_u8Val;
}

void TIMER0_voidSetCallBack(void (*Copy_pvCallBack)(void))
{
	TIMER0_CallBack=Copy_pvCallBack;
}


void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	TIMER0_CallBack();
}
