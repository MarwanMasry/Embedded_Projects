/******************************************************************************
 *
 * Module: Ultrasonic Module
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the Ultrasonic driver.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                          Definition - Configurations                        *
 *******************************************************************************/
/*	Static configuration for Trigger PIN	*/
#define	ULTRASONIC_TRIGGER_SIGNAL_PORT_ID		PORTB_ID
#define	ULTRASONIC_TRIGGER_SIGNAL_PIN_ID		PIN5_ID

/*	ECHO high time/Timer1 value calculation configuration	*/
#define ULTRASONIC_USE_ICU_AT_PRESCALLER		8
#define TIMER_STEP 								(float32)ULTRASONIC_USE_ICU_AT_PRESCALLER/F_CPU
#define SOUND_velocity_IN_cmPERs_DIV_BY_2	 	34000/2
/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*
 * Description:
 * This function responsible for :
 * 1)Initialize the ICU driver as required.
 * 2)Setup the ICU call back function.
 * 3)Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void);

/*
 * Description:
 * This function will Send the trigger pulse by using Ultrasonic_Trigger function
 * to send the 8 pulses from the sensor to start calculating the time to travel and
 * return from the object and it Start the measurements by the ICU and return the
 * value of distance read.
 */

uint16 Ultrasonic_readDistance(void);

/*
 * Description:
 * This function turn off the Modules that is being used by Ultarsonic sensor
 * which is the Timer module.
 */
void Ultrasonic_deInit(void);

#endif /* ULTRASONIC_H_ */
