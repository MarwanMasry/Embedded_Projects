 /******************************************************************************
 *
 * Module: LM35 Sensor
 *
 * File Name: lm35.h
 *
 * Description: Header file for the LM35 sensor Driver.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

#ifndef LM35_H_
#define LM35_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                          Definition - Configurations                        *
 *******************************************************************************/
#define LM35_CHANNEL_NUMBER				ADC2

/* The sensor measure form -55C to 150C and as MCU can't read negative voltage
 * we will shift these  number to be positive range [0 , 205] using a base
 * temperature 55C  then we  will subtract the base Temperature at the end of conversion.
 */
#define LM35_MAXIMUM_TEMP				205
#define LM35_MAXIMUM_VOLTAGE			2.05
#define LM35_BASE_TEMP					55


/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*
 * Description:
 * Function responsible for calculate the temperature from the ADC digital value.
 */
sint16 LM35_getTemperature(void);

#endif /* LM35_H_ */
