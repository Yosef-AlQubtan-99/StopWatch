/*
 * bit_math.h
 *
 *  Created on: Aug 14, 2023
 *      Author: yosef
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(var , bit_num)        	var|=(1<<bit_num)
#define CLR_BIT(var , bit_num)        	var&=(~(1<<bit_num))
#define TOGGLE_BIT(var , bit_num)     	var^=(1<<bit_num)
#define GET_BIT(var , bit_num)        	((var>>bit_num)&1)


#endif /* BIT_MATH_H_ */
