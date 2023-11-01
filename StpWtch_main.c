/*
 * StpWtch_main.c
 *
 *  Created on: Oct 6, 2023
 *      Author: yosef
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include <avr/io.h>

#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "GIE_interface.h"
#include "EXTI012_interface.h"

u8 secU=0,secT=0,minU=0,minT=0,hourU=0,hourT=0;         //declaring units and tens for 7 seg.
u8 CLK_mode=0;
u8 AlarmFlag=0;

void StpWtch_Reset (void);
void IncSec (void);
void DecSec (void);
void CLKMode_Switch (u8 Copy_hourT , u8 Copy_hourU , u8 Copy_minT , u8 Copy_minU , u8 Copy_secT , u8 Copy_secU);
void Set_Alarm(u8 Copy_hourT , u8 Copy_hourU , u8 Copy_minT , u8 Copy_minU , u8 Copy_secT , u8 Copy_secU);
void Set_Timer(u8 Copy_hourT , u8 Copy_hourU , u8 Copy_minT , u8 Copy_minU , u8 Copy_secT , u8 Copy_secU);

int main(void)
{
//	u8 mode=1;
	//assigning ports direction and activating PullUp res.

	DIO_voidSetPortDirection(DIO_u8PORTA , 0xff);         //PortA is an o/p port for certain 7seg enable
														  //Essentially 6pins for the used component could be more



	DIO_voidSetPortValue(DIO_u8PORTA , 0x00);

	DIO_voidSetPortDirection(DIO_u8PORTC , 0b00111111);         	  //C0~3 are o/p ports for Data out to decoder

	DIO_voidSetPinDirection(DIO_u8PORTC , 7 , DIO_u8INPUT);           //Pin C7 Switches between
																	  //clock mode and stop watch mode

	DIO_voidSetPinDirection(DIO_u8PORTC , 6 , DIO_u8INPUT);           //Pin C6 for timer or alarm activation

	DIO_voidSetPinValue(DIO_u8PORTC , 7 , DIO_u8HIGH);                //Activating PullUP Resistance
	DIO_voidSetPinValue(DIO_u8PORTC , 6 , DIO_u8HIGH);                //Activating PullUP Resistance

	DIO_voidSetPinDirection(DIO_u8PORTD , 2 , DIO_u8INPUT);           //interrupt pin INT0
	DIO_voidSetPinValue(DIO_u8PORTD , 2 , DIO_u8HIGH );               //PullUP Resistance INT0

	DIO_voidSetPinDirection(DIO_u8PORTD , 3 , DIO_u8INPUT);           //interrupt pin INT1
	DIO_voidSetPinValue(DIO_u8PORTD , 3 , DIO_u8HIGH );               //PullUP Resistance INT1

	DIO_voidSetPinDirection(DIO_u8PORTB , 2 , DIO_u8INPUT);           //interrupt pin INT2
	DIO_voidSetPinValue(DIO_u8PORTB , 2 , DIO_u8HIGH );               //PullUP Resistance INT2


	//Initiating Interrupts and assigning CallBack funcs
	GIE_voidEnable();

	EXTI0_voidInit();
	EXTI0_voidSetCallBack(StpWtch_Reset);                         //INT0 Pin is for Resetting the Stop watch

	EXTI1_voidInit();
	EXTI1_voidSetCallBack(Timer0_voidPause);                      //INT1 Pin is for Pausing the Stop watch

	EXTI2_voidInit();
	EXTI2_voidSetCallBack(Timer0_voidResume);					  //INT2 Pin is for Resuming the Stop watch

	TIMER0_voidInit();
	TIMER0_voidSetCallBack(IncSec);

	while(1)
	{

	//Activates secU   (7seg representing seconds' units)
	DIO_voidSetPortValue(DIO_u8PORTA, 0b00111111);
	DIO_voidSetPinValue(DIO_u8PORTA, 0 , DIO_u8LOW);
	PORTC=secU;
//	_delay_ms(2);
	DIO_voidSetPortValue(DIO_u8PORTA, 0b00111111);

	//Activates secT   (7seg representing seconds' Tens)
	DIO_voidSetPinValue(DIO_u8PORTA, 1 , DIO_u8LOW);
	PORTC=secT;
//	_delay_ms(2);
	DIO_voidSetPortValue(DIO_u8PORTA, 0b00111111);


	//Activates minU   (7seg representing minutes' units)
	DIO_voidSetPinValue(DIO_u8PORTA, 2 , DIO_u8LOW);
	PORTC=minU;
//	_delay_ms(2);
	DIO_voidSetPortValue(DIO_u8PORTA, 0b00111111);

	//Activates minT   (7seg representing minutes' Tens)
	DIO_voidSetPinValue(DIO_u8PORTA, 3 , DIO_u8LOW);
	PORTC=minT;
//	_delay_ms(2);
	DIO_voidSetPortValue(DIO_u8PORTA, 0b00111111);

	//Activates hourU   (7seg representing hours' units)
	DIO_voidSetPinValue(DIO_u8PORTA, 4 , DIO_u8LOW);
	PORTC=hourU;
//	_delay_ms(2);
	DIO_voidSetPortValue(DIO_u8PORTA, 0b00111111);

	//Activates hourT   (7seg representing hours' Tens)
	DIO_voidSetPinValue(DIO_u8PORTA, 5 , DIO_u8LOW);
	PORTC=hourT;
//	_delay_ms(2);
	DIO_voidSetPortValue(DIO_u8PORTA, 0b00111111);

	if (DIO_u8GetPinValue(DIO_u8PORTC,7)==0 && CLK_mode==0)
	{
		Timer0_voidResume(); 					//in case of switching mode without starting the stpwtch
		CLKMode_Switch(2,3,5,9,5,0);
		               ///////////////////////////////////////////////////////
		CLK_mode=1;

		EXTI0_voidDisableInt();         	//Disable RESET interrupt
		EXTI1_voidDisableInt();         	//Disable Pause interrupt
		EXTI2_voidDisableInt();				//Disable Resume interrupt

		while (DIO_u8GetPinValue(DIO_u8PORTC,7)==0)
			{
				asm("NOP");						//for avoiding accidental continuous press
			}
	}


	else if(DIO_u8GetPinValue(DIO_u8PORTC,7)==0 && CLK_mode==1)
	{
		StpWtch_Reset();
		CLK_mode=0;

		EXTI0_voidInit();				//Enable RESET interrupt
		EXTI1_voidInit();				//Enable Pause interrupt
		EXTI2_voidInit();				//Enable Resume interrupt
	while (DIO_u8GetPinValue(DIO_u8PORTC,7)==0)
	{
		asm("NOP");						//for avoiding accidental continuous press
	}
	}


	if (DIO_u8GetPinValue(DIO_u8PORTC,6)==0 && CLK_mode==0)              //Stopwatch is active clock disabled
	{
		TIMER0_voidSetCallBack(DecSec);                                  //Timer Submode activ
		Timer0_voidResume();
		Set_Timer(0,0,0,0,2,0);
		while (DIO_u8GetPinValue(DIO_u8PORTC,6)==0)
		{
			asm("NOP");						//for avoiding accidental continuous press
		}
	}
//	else if(DIO_u8GetPinValue(DIO_u8PORTC,6)==0 && CLK_mode==1)			//Clock active Stopwatch disabled
//	{
//		Set_Alarm(0,0,0,0,2,0);                                         //Activating Alarm Submode
//
//	}

	}
}

void StpWtch_Reset (void)
{
	TIMER0_voidSetCallBack(IncSec);
	secU=0,secT=0,minU=0,minT=0,hourU=0,hourT=0;
	Timer0_voidPause();
}

void CLKMode_Switch (u8 Copy_hourT , u8 Copy_hourU , u8 Copy_minT , u8 Copy_minU , u8 Copy_secT , u8 Copy_secU)
{
	Timer0_voidResume();
	IncSec();
	secU=Copy_secU,
	secT=Copy_secT,
	minU=Copy_minU,
	minT=Copy_minT,
	hourU=Copy_hourU,
	hourT=Copy_hourT;
}

void IncSec (void)
{
	TIMER0_voidSetCallBack(IncSec);
	static u16 Local_u16Counter=0;
	Local_u16Counter++;                     //PreScalar is assigned for 250usec to reach OCR val -> 250
											//Tick Time= 1usec

	if (Local_u16Counter==500)             //Checking the completion of 1sec
	{
//		if (AlarmFlag==1)
//		{
//			Set_Alarm();
//		}

		secU++;
		if (secU==10)
		{
			secU=0;
			secT++;
		}
		if (secT==6)
		{
			secU=0;
			secT=0;
			minU++;
		}

		if (minU==10)
		{
			minU=0;
			minT++;
		}
		if (minT==6)
		{
			hourU++;
			minT=0;
			minU=0;
		}

		if (hourU==10)
		{
			hourT++;
			hourU=0;
		}
		if (hourU==4 && hourT==2)
		{
			StpWtch_Reset();
			Timer0_voidResume();
		}

		Local_u16Counter=0;                 // For beginning a new second

	}
}
void Set_Alarm(u8 Copy_hourT , u8 Copy_hourU , u8 Copy_minT , u8 Copy_minU , u8 Copy_secT , u8 Copy_secU)
{
	AlarmFlag=1;
	if(Copy_hourT==hourT &&
	   Copy_hourU==hourU &&
	   Copy_minT==minT &&
	   Copy_minU==minU &&
	   Copy_secT==secT &&
	   Copy_secU==secU)
	{
		DIO_voidSetPinValue(DIO_u8PORTC , 5 , DIO_u8HIGH);

	}
}

void Set_Timer(u8 Copy_hourT , u8 Copy_hourU , u8 Copy_minT , u8 Copy_minU , u8 Copy_secT , u8 Copy_secU)
{
	secU=Copy_secU,
	secT=Copy_secT,
	minU=Copy_minU,
	minT=Copy_minT,
	hourU=Copy_hourU,
	hourT=Copy_hourT;
}

void DecSec (void)
{
	TIMER0_voidSetCallBack(DecSec);
	static u16 Local_u16Counter=0;
	Local_u16Counter++;                     //PreScalar is assigned for 250usec to reach OCR val -> 250
											//Tick Time= 1usec
	u8 Local_TimerOvrFlw=0;

//	if (Local_TimerOvrFlw==1)
//	{
//		DIO_voidSetPinValue(DIO_u8PORTC , 5 , DIO_u8LOW);           //Timer Expired
//		Timer0_voidPause();
//	}
	if (Local_u16Counter==500)             //Checking the completion of 1sec
	{

	if (hourT==0 && hourU==0 && minT==0 && minU==0 && secT==0 && secU==0)
	{
		DIO_voidSetPinValue(DIO_u8PORTC , 5 , DIO_u8HIGH);           //Timer Expired
		Local_TimerOvrFlw=1;
		_delay_ms(2000);
		Timer0_voidPause();
	}

	else if (secU==0 && secT ==0 && minU==0 && minT==0 && hourU==0 && hourT>0)
	{
		hourT--;
		hourU=9;
		minT=5;
		minU=9;
		secT=5;
		secU=9;
	}
	else if (secU==0 && secT ==0 && minU==0 && minT==0 && hourU>0)
	{
		hourU--;
		minT=5;
		minU=9;
		secT=5;
		secU=9;
	}
	else if (secU==0 && secT ==0 && minU==0 && minT>0)
	{
		minT--;
		minU=9;
		secT=5;
		secU=9;
	}
	else if (secU==0 && secT ==0 && minU>0)
	{
		minU--;
		secT=5;
		secU=9;
	}
	else if (secU==0 && secT>0)
	{
		secT--;
		secU=9;
	}
	else {
		secU--;
	}
			Local_u16Counter=0;                 // For beginning a new second
	}
}




