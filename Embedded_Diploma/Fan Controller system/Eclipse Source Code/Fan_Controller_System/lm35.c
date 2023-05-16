 /******************************************************************************
 *
 * Module: LM35 Sensor
 *
 * File Name: lm35.c
 *
 * Description: Source file for the LM35 sensor Driver.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "lm35.h"
#include "adc.h"


/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/
/*
 * Description:
 * Function responsible for calculate the temperature from the ADC digital value.
 */
sint16 LM35_getTemperature(void)
{
	sint16	L_tempValue = 0;

	/*	read the digital Value from corresponding analog voltage	*/
	uint16 L_digitalValue = ADC_readChannel(LM35_CHANNEL_NUMBER);

	/*
	 * Temperature C (current temp)[3]->sensor output voltage[2]->ADC reading (corresponding to the current temp)
	 *	205 C (max temp)              ->          2.05 V        -> ADC reading (corresponding to the max temp) [1]
     *                                            5 V     	    -> 1023
     *
 	 *[1]ADC reading (corresponding to the max temp) = 2.05 V * 1023 / 5 V
	 *[2] sensor output voltage =   (ADC reading (corresponding to the current temp) * 5) / (1023 )
	 *[3] Temperature C (current temperature) =  (ADC reading (corresponding to the current temp) * 205 C * 5) / (2.05 V * 1023)
	 *[3]
	 *[3]Temperature C (current temperature) =  (ADC reading (corresponding to the current temp) * max Temp * Vref )/
	 *    										(max output voltage from the sensor  * ADC maximum value)
	 *[3] Temperature C (current temperature) -= 55 ;
	 */

	L_tempValue = ( (((uint32)L_digitalValue*LM35_MAXIMUM_TEMP*g_referenceVoltage_ADC) / (LM35_MAXIMUM_VOLTAGE * ADC_MAX_DIGITAL_VALUE) ) - LM35_BASE_TEMP );

	return L_tempValue;
}
