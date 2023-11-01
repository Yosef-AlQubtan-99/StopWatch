/*
 * interface.h
 *
 *  Created on: Aug 28, 2023
 *      Author: yosef
 */

#ifndef EXTI012_INTERFACE_H_
#define EXTI012_INTERFACE_H_

void EXTI0_voidInit(void);
void EXTI1_voidInit(void);
void EXTI2_voidInit(void);
void EXTI0_voidDisableInt(void);
void EXTI1_voidDisableInt(void);
void EXTI2_voidDisableInt(void);
void EXTI0_voidSenseControl(u8 Copy_u8Sense);
void EXTI0_voidSetCallBack(void (*Copy_pvCallBack)(void));                      //pointer to function as an arg. for void setcallback
void EXTI1_voidSetCallBack(void (*Copy_pvCallBack)(void));
void EXTI2_voidSetCallBack(void (*Copy_pvCallBack)(void));


#define   LOW_LEVEL            1
#define   ANY_CHANGE           2
#define   FALLING_EDGE         3
#define   RISING_EDGE          4




#endif /* EXTI012_INTERFACE_H_ */
