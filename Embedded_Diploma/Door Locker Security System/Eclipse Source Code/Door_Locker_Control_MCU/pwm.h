 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: pwm.h
 *
 * Description: Header file for simple PWM generation function
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef PWM_H_
#define PWM_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*
 * Description:
 * Generate a PWM signal with frequency 500Hz
 * Timer0 will be used with pre-scaler F_CPU/8
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * Duty Cycle can be changed be update the value in
 * The Compare Register
 */
void Timer0_PWM_Init(uint8 a_dutyCycle);


#endif /* PWM_H_ */
