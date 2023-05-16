 /******************************************************************************
 *
 * Module: ICU Module
 *
 * File Name: icu.c
 *
 * Description: Source file for the ICU driver.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "icu.h"
#include "gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/*******************************************************************************
 *                      Private Global Variables Definitions                   *
 *******************************************************************************/

/*
 *  It is used to Store the address of the call back Function which is sent
 *  locally to the ICU_setCallBackFunction function to be used in the ISR.
 */

static volatile void (* g_callBackFunction_Ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                             ISR's Definitions                               *
 *******************************************************************************/

/*
 * Description :
 * This function will call the call back function in which the user provides form
 * the application.
 */
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackFunction_Ptr != NULL_PTR)
	{
		(* g_callBackFunction_Ptr)();
	}
}


/*******************************************************************************
 *                          Public Function Definitions	                       *
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
void ICU_init(const DynamicConfiguration_ICU * a_configuration_Ptr)
{
	uint8 L_sreg = SREG;

	/*	Configure ICP1/PD6 as input	*/
	GPIO_setupPinDirection(PORTD_ID , PIN6_ID , PIN_INPUT);

	/*
	 * TCNT1 , ICR1 are 16 bit address so R/W in this register will be in more
	 * than one instruction.
	 * If an interrupt occurs between the two instructions accessing the 16-bit
	 * register, and the interrupt code updates the temporary register by accessing
	 * the same or any other of the 16-bit Timer Registers, then the result of
	 * the access outside the interrupt will be corrupted.
	 *  So we must do Atomic read/Write operations.
	 */
	SREG &= ~(1<<7); /*	Disable interrupts	*/

	TCNT1 = 0 ;		/*	Initialize to Zero	*/
	ICR1  = 0 ;		/*	Initialize to Zero	*/

	SREG = L_sreg; 	/*	Return to the default status control register values  */


	/*	TCCR1A register control bits
	 *  COM1A 1:0 = 0 : Normal port operation, OC1A disconnected.
	 *  COM1B 1:0 = 0 : Normal port operation, OC1B disconnected.
	 *  FOC1A = 0	  : NON PWM mode.
	 *  FOC1B = 0	  : NON PWM mode.
	 *  WGM1 1:0 = 0  : configure module to Normal mode.
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;

	/*	TCCR1B register control bits:
	 *  CS1  2:0 = The Prescaler exist in the dynamic configuration structure[s_prescaller]
	 *  ICES1    = The Event selected in the dynamic configuration structure [s_edge]
	 *  ICNC1 = 0 	  : Deactivate Input capture noise canceler.
	 *  WGM1 3:2 = 0  : configure module to Normal mode.
	 */
	TCCR1B = ( (a_configuration_Ptr ->s_edge) << ICES1 ) | (a_configuration_Ptr->s_prescaller);

	/*	Enable Input Capture Interrupt Module [MIE]	to generate interrupt when
	 * detecting an edge.
	 */
	TIMSK |= (1<<TICIE1);
}

/*
 * Description :
 * This function takes the address of the function that need to be called when
 * Event is detected.
 * It save the argument address of the function in a Global one so that it can be
 * called from the ISR.
 */
void ICU_setCallBackFunction( void (* a_callBackfunction_Ptr)(void) )
{
	/* Save the address of the Call back function in a global variable */
	g_callBackFunction_Ptr = a_callBackfunction_Ptr;
}


/*
 * Description:
 * This function change the the event which is detected by ICU without calling
 * the Initialization  function so that it we don't have to turn on timer , set its mode ,
 * initialize register values , set the Control bits as the ICU Initialization function
 * do.
 * In order for this function to operate right, It must be called after ICU_init function.
 */
void ICU_setEdgeDetectionType( EdgeSelect_ICU a_edge )
{
	/*	Change the Event configurations of the ICU driver according to the
	 *  input Parameter.
	 */
	TCCR1B = (TCCR1B & 0xBF) | ( a_edge << ICES1 );
}


/*
 * Description:
 * This function return the value of TCNT1 at the time the event occur, This value
 * is saved in ICR1 register.
 */
uint16 ICU_getInputCaptureValue(void)
{
	uint16 L_ICR1Value = 0 ;
	uint8 L_sreg = SREG;

	/*
	* TCNT1 , ICR1 are 16 bit address so R/W in this register will be in more
	* than one instruction.
	* If an interrupt occurs between the two instructions accessing the 16-bit
	* register, and the interrupt code updates the temporary register by accessing
	* the same or any other of the 16-bit Timer Registers, then the result of
	* the access outside the interrupt will be corrupted.
	*  So we must do Atomic read/Write operations.
	*/
	SREG &= ~(1<<7); /*	Disable interrupts	*/

	L_ICR1Value = ICR1;

	SREG = L_sreg; 	/*	Return to the default status control register values  */

	return L_ICR1Value;
}


/*
 * Description:
 * This value reset the TCNT1 register so that the counter can count from Zero
 */
void ICU_clearTimerValue(void)
{
	uint8 L_sreg = SREG;

	/*
	 * TCNT1 , ICR1 are 16 bit address so R/W in this register will be in more
	 * than one instruction.
	 * If an interrupt occurs between the two instructions accessing the 16-bit
	 * register, and the interrupt code updates the temporary register by accessing
	 * the same or any other of the 16-bit Timer Registers, then the result of
	 * the access outside the interrupt will be corrupted.
	 *  So we must do Atomic read/Write operations.
	 */
	SREG &= ~(1<<7); /*	Disable interrupts	*/

	TCNT1 = 0 ;		/*	Initialize to Zero	*/

	SREG = L_sreg; 	/*	Return to the default status control register values  */

}


/*
 * Description:
 * This function will Turn off the Timer and stops the ICU driver
 */
void ICU_deInit(void)
{
	uint8 L_sreg = SREG;

	/* Clear all timer control registers	*/
	TCCR1A = 0 ;
	TCCR1B = 0;

	/*
	* TCNT1 , ICR1 are 16 bit address so R/W in this register will be in more
	* than one instruction.
	* If an interrupt occurs between the two instructions accessing the 16-bit
	* register, and the interrupt code updates the temporary register by accessing
	* the same or any other of the 16-bit Timer Registers, then the result of
	* the access outside the interrupt will be corrupted.
	*  So we must do Atomic read/Write operations.
	*/
	SREG &= ~(1<<7); /*	Disable interrupts	*/

	TCNT1 = 0 ;		/*	Clear the register	*/
	ICR1  = 0 ;		/*	Clear the register	*/
	SREG = L_sreg; 	/*	Return to the default status control register values  */


	/*	Disable Input Capture Interrupt Module	*/
	TIMSK &= ~(1<<TICIE1);
}



