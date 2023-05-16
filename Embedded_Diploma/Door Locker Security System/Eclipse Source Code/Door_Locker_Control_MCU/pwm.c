 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: pwm.c
 *
 * Description: Source file for simple PWM generation function
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "pwm.h"
#include <avr/io.h>

/*******************************************************************************
 *                          Public Function Definition	                       *
 *******************************************************************************/

/*
 * Description:
 * Generate a PWM signal with frequency 500Hz
 * Timer0 will be used with pre-scaler F_CPU/8
 * F_PWM=(F_CPU)/(256*N) = (10^6)/(256*8) = 500Hz
 * Duty Cycle can be changed be update the value in
 * The Compare Register
 */
void Timer0_PWM_Init(uint8 a_dutyCycle)
{
	/*	Set Timer Initial Value to 0	*/
	TCNT0 = 0;

	/*	Set Compare Value according to the duty cycle that the user supply	*/
	OCR0  = ((uint16)a_dutyCycle*255) / 100 ;

	/* Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC	*/
	DDRB  = DDRB | (1<<PB3);

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

