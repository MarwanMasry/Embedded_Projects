 /******************************************************************************
 *
 * Module: ADC Module
 *
 * File Name: adc.h
 *
 * Description: Header file for the ADC driver using Polling technique.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                          Definition - Configurations                        *
 *******************************************************************************/
#define ADC_MAX_DIGITAL_VALUE			1023
#define ADC_MIN_DIGITAL_VALUE			0
#define ADC_NUM_OF_BITS					10

/*	Static configuration in case of Using External Voltage reference  */
#define ADC_EXTERNAL_REF_VOLT_VALUE  	5

/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
/*
 * Description:
 * This enum will be used as parameter data type for read channel function where
 * we have 8 channel of ADC and we can use only one channel at a time so we need
 * to know which channel are we going to work with.
 *
 * In ADMUX register
 * Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits:
 * 00000 ADC0
 * 00001 ADC1
 * 00010 ADC2
 * 00011 ADC3
 * 00100 ADC4
 * 00101 ADC5
 * 00110 ADC6
 * 00111 ADC7
 *
 */
typedef enum
{
	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7
}ChannelNumber_ADC;

/*
 * Description:
 * The ADC has need a clock to operate the module so we have multiple prescaler
 * to get ADC frequency in range of 50 KHZ to 200HZ, So according to the processor
 * Frequency a divisor is chosen.
 * This is used as Dynamic configuration to the initialization of the ADC.
 *
 * In ADCSRA register
 * Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
 * ADPS2 ADPS1 ADPS0 Division Factor
 * 0 	 0	   0	 2
 * 0 	 0 	   1	 2
 * 0	 1 	   0	 4
 * 0	 1 	   1	 8
 * 1	 0 	   0	 16
 * 1	 0 	   1	 32
 * 1	 1 	   0	 64
 * 1	 1 	   1 	 128
 */
typedef enum
{
	F_CPU_DIV_BY_2 = 1, F_CPU_DIV_BY_4, F_CPU_DIV_BY_8, F_CPU_DIV_BY_16 \
	,F_CPU_DIV_BY_32, F_CPU_DIV_BY_64, F_CPU_DIV_BY_128
}Prescaler_ADC;

/*
 * Description:
 * As the module need to choose one of three mode for reference voltage:
 * 1)External reference voltage : by connecting external needed voltage in AREF pin.
 * 2)AVCC : choose the source volt of AVCC as reference volt which is 5 volt.
 * 3)Internal reference voltage : supply internally a reference volt with 2.56 volt.
 * This is used as Dynamic configuration to the initialization of the ADC.
 *
 * IN ADMUX register
 * Bit 7:6 – REFS1:0: Reference Selection Bits
 * 0 0 AREF, Internal Vref turned off
 * 0 1 AVCC with external capacitor at AREF pin
 * 1 1 Internal 2.56V Voltage Reference with external capacitor at AREF pin
 *
 *  */
typedef enum
{
	EXTERNAL_AREF , AVCC_5V , INTERNAL_2560_MILLI_VOLT = 3
}ReferenceVoltageSelection_ADC;

/*
 * Description:
 * This structure has all the dynamic configuration for the ADC module to works
 * as the user want. All the user need to do supply reference voltage mode selection
 * and prescaler that he want to work with and the Module will be initialized to
 * that configuration.
 */
typedef struct
{
	ReferenceVoltageSelection_ADC 	 s_referenceVoltSelection;
	Prescaler_ADC  					 s_prescaler;
}DynamicConfiguration_ADC;


/*******************************************************************************
 *                    Public Global Variables Decelerations                    *
 *******************************************************************************/
/*
 *  It is used to save the reference voltage at any mode at all dynamic
 *  configurations
 */
extern volatile float32 g_referenceVoltage_ADC  ;

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/*
 * Description:
 * This function initialize the ADC Module according to the user configuration
 * by choosing the needed reference voltage and the prescaler he want.
 */
void ADC_init(const DynamicConfiguration_ADC	*a_configuration_Ptr);


/*
 * Description:
 * we have 8 channel of ADC and we can use only one channel at a time so we need
 * to know which channel are we going to work with.
 * This function takes the input channel as input and activates the ADC
 * and convert the current analog value at the input pin to a digital value and
 * return it.
 */
uint16 ADC_readChannel(ChannelNumber_ADC	a_channel);



#endif /* ADC_H_ */
