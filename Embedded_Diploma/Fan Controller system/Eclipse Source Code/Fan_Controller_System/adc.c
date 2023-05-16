 /******************************************************************************
 *
 * Module: ADC Module
 *
 * File Name: adc.c
 *
 * Description: Source file for the ADC driver using Polling technique.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "adc.h"
#include <avr/io.h>
#include "common_macros.h"

/*******************************************************************************
 *                      Public Global Variables Definitions                    *
 *******************************************************************************/
/*
 *  It is used to save the reference voltage at any mode at all dynamic
 *  configurations
 */
volatile float32 g_referenceVoltage_ADC = 0 ;


/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/
/*
 * Description:
 * This function initialize the ADC Module according to the user configuration
 * by choosing the needed reference voltage and the prescaler he want.
 */
void ADC_init(const DynamicConfiguration_ADC	*a_configuration_Ptr)
{
	/*
	 *  ADMUX register bit selection :
	 *  1)REFS1:0 = we set this two bits according to the
	 *    dynamic configuration that is supplied by the user either choosing internal
	 *    mode or External AREF or use the AVCC as reference.
	 *  2)ADLAR   = 0 right adjusted
	 *  3)MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (a_configuration_Ptr ->s_referenceVoltSelection) << 6 ;

	/*
	 *  ADCSRA register bit selection:
	 *  1)ADEN    = 1 Enable ADC
	 * 	2)ADIE    = 0 Disable ADC Interrupt
	 *  3)ADATE   = 0 Disable Auto Trigger
	 *  4)ADPS2:0 = the selection chosen by the user to divide the processor CPU
	 *    to supply the ADC module with a clock.
	 */
	ADCSRA = (1<<ADEN) | (a_configuration_Ptr -> s_prescaler);



	/* We will save the value of reference voltage in all voltage reference
	 *  selection options in ADC
	 */

	if( (a_configuration_Ptr ->s_referenceVoltSelection) == INTERNAL_2560_MILLI_VOLT )
	{
		/* In case of using internal Voltage the value will be 2.56	*/
		g_referenceVoltage_ADC = 2.56;
	}
	else if( (a_configuration_Ptr ->s_referenceVoltSelection) == AVCC_5V)
	{
		/*	In case of choosing AVCC as a reference so the value will be 5	*/
		g_referenceVoltage_ADC = 5;
	}
	else if(  (a_configuration_Ptr ->s_referenceVoltSelection) == EXTERNAL_AREF)
	{
		/*	If the user want a specific voltage so he will supply it to AREF pin
		 *  and he need to modify this value as a static configurations , then
		 *  saving this value in the global variable
	     */
		g_referenceVoltage_ADC = ADC_EXTERNAL_REF_VOLT_VALUE ;
	}
}


/*
 * Description:
 * we have 8 channel of ADC and we can use only one channel at a time so we need
 * to know which channel are we going to work with.
 * This function takes the input channel as input and activates the ADC
 * and convert the current analog value at the input pin to a digital value and
 * return it.
 */
uint16 ADC_readChannel(ChannelNumber_ADC	a_channel)
{
	/*
	 * we cleared the 5 bits of MUX to make sure no garbage then oring the result
	 * with the channel number and finally put the value in bits MUX4:0
	 */
	ADMUX = (ADMUX & 0xE0) | ( a_channel & 0x07 );

	/*	Start conversation of ADC Module	*/
	SET_BIT(ADCSRA,ADSC);

	/*	Polling until conversion completes ,When ADIF is 1 the conversion is
	 *  complete and the Loop/Polling
	 *  ends
	 */
	while( BIT_IS_CLEAR(ADCSRA , ADIF) );

	/* Clear the ADC Interrupt flag in order to sense another conversion process
	 * of ADC
	 */
	SET_BIT(ADCSRA,ADIF);

	/*	Return the digital value after conversion is complete	*/
	return ADC;
}


