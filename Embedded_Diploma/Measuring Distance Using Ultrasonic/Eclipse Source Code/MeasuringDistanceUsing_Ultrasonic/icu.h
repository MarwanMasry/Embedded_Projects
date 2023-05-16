 /******************************************************************************
 *
 * Module: ICU Module
 *
 * File Name: icu.h
 *
 * Description: Header file for the ICU driver.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
/*
 * Description:
 * The Timer  need a clock to operate the module so we have multiple prescaler
 *  So according to the Frequency the user need a divisor is chosen.
 *
 * This is used as Dynamic configuration to the initialization of the ICU.
 *
 * In TCCR1B register
 * Bit 2:0 – CS12:0: Clock Select
 * CS12 CS11 CS10 	Division Factor
 * 0 	 0	   0	 No clock
 * 0 	 0 	   1	 1
 * 0	 1 	   0	 8
 * 0	 1 	   1	 64
 * 1	 0 	   0	 256
 * 1	 0 	   1	 1024
 */
typedef enum
{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_DIV_BY_8, F_CPU_DIV_BY_64 \
	,F_CPU_DIV_BY_256, F_CPU_DIV_BY_1024
}Prescaler_ICU;

/*
 * Description:
 *
 * This is used as Dynamic configuration to the initialization of the ICU to select
 * which edge you want to detect Rising or Falling.
 */

typedef enum
{
	FALLING_EDGE , RISING_EDGE
}EdgeSelect_ICU;

/*
 * Description:
 * This structure has all the dynamic configuration for the ICU module to works
 * as the user want. All the user need to do supply the edge he want to supply
 * and prescaler that he want to work with and the Module will be initialized to
 * that configuration.
 */

typedef struct
{
	Prescaler_ICU 	s_prescaller;
	EdgeSelect_ICU	s_edge;

}DynamicConfiguration_ICU;


/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*
 * Description :
 * This function responsible for Turing on the timer module and set the
 * configuration needed for the module Dynamically.
 *  1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const DynamicConfiguration_ICU * a_configuration_Ptr);

/*
 * Description :
 * This function takes the address of the function that need to be called when
 * Event is detected.
 * It save the argument address of the function in a Global one so that it can be
 * called from the ISR.
 */
void ICU_setCallBackFunction( void (* a_callBackfunction_Ptr)(void) );


/*
 * Description:
 * This function change the the event which is detected by ICU without calling
 * the Initialization  function so that it we don't have to turn on timer , set its mode ,
 * initialize register values , set the Control bits as the ICU Initialization function
 * do.
 * In order for this function to operate right, It must be called after ICU_init function.
 */
void ICU_setEdgeDetectionType( EdgeSelect_ICU a_edge );


/*
 * Description:
 * This function return the value of TCNT1 at the time the event occur, This value
 * is saved in ICR1 register.
 */
uint16 ICU_getInputCaptureValue(void);


/*
 * Description:
 * This value reset the TCNT1 register so that the counter can count from Zero
 */
void ICU_clearTimerValue(void);


/*
 * Description:
 * This function will Turn off the Timer and stops the ICU driver
 */
void ICU_deInit(void);

#endif /* ICU_H_ */
