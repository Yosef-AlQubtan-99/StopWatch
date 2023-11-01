/*
 * TIMER0_register.h
 *
 *  Created on: Aug 31, 2023
 *      Author: mostafa.mohammady
 */

#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_


#define    TCCR0             *((volatile u8*)(0x53))
#define    TCNT0             *((volatile u8*)(0x52))
#define    OCR0              *((volatile u8*)(0x5C))
#define    TIMSK             *((volatile u8*)(0x59))
#define    TIFR              *((volatile u8*)(0x58))


#endif /* TIMER0_REGISTER_H_ */
