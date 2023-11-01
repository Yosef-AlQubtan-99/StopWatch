/*
 * TIMER0_interface.h
 *
 *  Created on: Aug 31, 2023
 *      Author: mostafa.mohammady
 */

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


void TIMER0_voidInit(void);
void TIMER0_voidSetOCRVal(u8 Copy_u8Val);
void TIMER0_voidSetCallBack(void (*Copy_pvCallBack)(void));
void Timer0_voidPause(void);
void Timer0_voidResume(void);

#endif /* TIMER0_INTERFACE_H_ */
