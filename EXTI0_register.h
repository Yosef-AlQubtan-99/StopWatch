/*
 * register.h
 *
 *  Created on: Aug 28, 2023
 *      Author: yosef
 */

#ifndef EXTI0_REGISTER_H_
#define EXTI0_REGISTER_H_

#define MCUCR       *((volatile u8 *)(0x55))
#define MCUCSR      *((volatile u8 *)(0x54))
#define GICR        *((volatile u8 *)(0x5B))
#define GIFR        *((volatile u8 *)(0x5A))


#endif /* EXTI0_REGISTER_H_ */
