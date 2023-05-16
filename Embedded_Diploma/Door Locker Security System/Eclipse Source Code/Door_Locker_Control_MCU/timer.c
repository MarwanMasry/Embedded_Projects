 /******************************************************************************
 *
 * Module: Timer0,1,2  Modules
 *
 * File Name: timer.c
 *
 * Description: Source file for the Timer0,1,2 driver.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/*******************************************************************************
 *                          Private Function Prototype	                       *
 *******************************************************************************/
/*
 * Description :
 * This function Helps The TIMER_init function Where it is only responsible for
 * initializing Timer0 according to the Dynamic Configurations set by the user.
 */
static void TIMER0_init(const DynamicConfiguration_TIMER * a_configuration_Ptr);

/*
 * Description :
 * This function Helps The TIMER_init function Where it is only responsible for
 * initializing Timer1 according to the Dynamic Configurations set by the user.
 */
static void TIMER1_init(const DynamicConfiguration_TIMER * a_configuration_Ptr);

/*
 * Description :
 * This function Helps The TIMER_init function Where it is only responsible for
 * initializing Timer2 according to the Dynamic Configurations set by the user.
 */
static void TIMER2_init(const DynamicConfiguration_TIMER * a_configuration_Ptr);

/*******************************************************************************
 *                      Private Global Variables Definitions                   *
 *******************************************************************************/
/*
 *  It is used to Store the address of the call back Function for Timer 0 which
 *  is sent locally to the TIMER_setCallBackFunction function to be used in the ISR.
 */

static volatile void (* g_callBackFunctionforTimer0_Ptr)(void) = NULL_PTR;

/*
 *  It is used to Store the address of the call back Function for Timer 1 which
 *  is sent locally to the TIMER_setCallBackFunction function to be used in the ISR.
 */

static volatile void (* g_callBackFunctionforTimer1_Ptr)(void) = NULL_PTR;

/*
 *  It is used to Store the address of the call back Function for Timer 2 which
 *  is sent locally to the TIMER_setCallBackFunction function to be used in the ISR.
 */
static volatile void (* g_callBackFunctionforTimer2_Ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                        Private Function Definitions	                       *
 *******************************************************************************/
/*
 * Description :
 * This function Helps The TIMER_init function Where it is only responsible for
 * initializing Timer0 according to the Dynamic Configurations set by the user.
 */
static void TIMER0_init(const DynamicConfiguration_TIMER * a_configuration_Ptr)
{

	/*	Let the Timer0 start Counting from the initial value that is given */
	TCNT0 = (uint8) a_configuration_Ptr->s_initialValue ;


	/*	If we are working at CTC mode only we should set Compare value as give */
	if(a_configuration_Ptr->s_timerMode  == T0_T2_CTC_MODE)
	{
		OCR0 = (uint8) a_configuration_Ptr->s_compareValue;
	}


	/*	Enable The CTC mode Interrupt Or Normal Mode Interrupt accoridng to
	 *  Mode selected by the user
	 */
	if(a_configuration_Ptr->s_timerMode  == T0_T2_CTC_MODE)
	{
		/*	Enable CTC mode interrupt from TIMSK register	*/
		TIMSK |= (1<<OCIE0);
	}
	else if(a_configuration_Ptr->s_timerMode  == NORMAL_MODE)
	{
		/*	Enable Normal mode interrupt from TIMSK register	*/
		TIMSK |= (1<<TOIE0);
	}

	/*	TCCR0 register control bits:
	 *
	 *  COM0 1:0 = 0 : Normal port operation, OC0 disconnected.
	 *  FOC0 = 1     : NON PWM mode.
	 *  WGM0 1:0     : They are set according to the parameter Mode used, it
	 *  			   will set the mode to CTC or Normal if the user choose
	 *  			   any of them in the configurations
	 *  CS0 2:0      : They are set according to the Prescaler chosen by the
	 *  			   used at the dynamic configurations.
	 */

	TCCR0 = (1<<FOC0) |  (a_configuration_Ptr->s_prescaler) \
					  |( (a_configuration_Ptr->s_timerMode & 0x01) << WGM00) \
					  |( (a_configuration_Ptr->s_timerMode & 0x02) <<(WGM01-1)) ;
}

/*
 * Description :
 * This function Helps The TIMER_init function Where it is only responsible for
 * initializing Timer1 according to the Dynamic Configurations set by the user.
 */
static void TIMER1_init(const DynamicConfiguration_TIMER * a_configuration_Ptr)
{

	uint8 L_sreg = SREG;
	/*
	 * TCNT1 , OCR1A are 16 bit address so R/W in this register will be in more
	 * than one instruction.
	 * If an interrupt occurs between the two instructions accessing the 16-bit
	 * register, and the interrupt code updates the temporary register by accessing
	 * the same or any other of the 16-bit Timer Registers, then the result of
	 * the access outside the interrupt will be corrupted.
	 *  So we must do Atomic read/Write operations.
	 */
	SREG &= ~(1<<7); /*	Disable interrupts	*/

	TCNT1 = a_configuration_Ptr->s_initialValue ;  /* Set initial value of timer */

	/*	If we are working at CTC mode only we should set Compare value as give */
	if(a_configuration_Ptr->s_timerMode  == T1_CTC_MODE)
	{
		OCR1A = a_configuration_Ptr->s_compareValue;
	}

	SREG = L_sreg; 	/*	Return to the default status control register values  */

	/*	Enable The CTC mode Interrupt Or Normal Mode Interrupt accoridng to
	 *  Mode selected by the user
	 */
	if(a_configuration_Ptr->s_timerMode  == T1_CTC_MODE)
	{
		/*	Enable CTC mode interrupt from TIMSK register	*/
		TIMSK |= (1<<OCIE1A);
	}
	else if(a_configuration_Ptr->s_timerMode  == NORMAL_MODE)
	{
		/*	Enable Normal mode interrupt from TIMSK register	*/
		TIMSK |= (1<<TOIE1);
	}


	/*	TCCR1A register control bits:
	 *
	 *  COM1A 1:0 = 0 : Normal port operation, OC1A disconnected.
	 *  COM1B 1:0 = 0 : Normal port operation, OC1B disconnected.
	 *  FOC1A = 1	  : NON PWM mode.
	 *  FOC1B = 1	  : NON PWM mode.
	 *  WGM1 1:0      : They are set according to the parameter Mode used, it
	 *  			    will set the mode to CTC or Normal if the user choose
	 *  			    any of them in the configurations
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B) | (a_configuration_Ptr->s_timerMode & 0x03);

	/*	TCCR1B register control bits:
	 *
	 *  CS1 2:0    : They are set according to the Prescaler chosen by the
	 *  		     used at the dynamic configurations.
	 *  ICES1 = 0  : Has not effect we are Disabling ICU
	 *  ICNC1 = 0  : Has not effect we are Disabling ICU
	 *  WGM1 3:2   : They are set according to the parameter Mode used, it
	 *  			 will set the mode to CTC or Normal if the user choose
	 *  			 any of them in the configurations
	 */
	TCCR1B  =       (a_configuration_Ptr->s_prescaler)  \
			     | ((a_configuration_Ptr->s_timerMode & 0x0C) << 1);
}

/*
 * Description :
 * This function Helps The TIMER_init function Where it is only responsible for
 * initializing Timer2 according to the Dynamic Configurations set by the user.
 */
static void TIMER2_init(const DynamicConfiguration_TIMER * a_configuration_Ptr)
{

	/*	Let the Timer2 start Counting from the initial value that is given */
	TCNT2 = (uint8) a_configuration_Ptr->s_initialValue ;


	/*	If we are working at CTC mode only we should set Compare value as give */
	if(a_configuration_Ptr->s_timerMode  == T0_T2_CTC_MODE)
	{
		OCR2 = (uint8) a_configuration_Ptr->s_compareValue;
	}


	/*	Enable The CTC mode Interrupt Or Normal Mode Interrupt according to
	 *  Mode selected by the user
	 */
	if(a_configuration_Ptr->s_timerMode  == T0_T2_CTC_MODE)
	{
		/*	Enable CTC mode interrupt from TIMSK register	*/
		TIMSK |= (1<<OCIE2);
	}
	else if(a_configuration_Ptr->s_timerMode  == NORMAL_MODE)
	{
		/*	Enable Normal mode interrupt from TIMSK register	*/
		TIMSK |= (1<<TOIE2);
	}

	/*	TCCR2 register control bits:
	 *
	 *  COM2 1:0 = 0 : Normal port operation, OC2 disconnected.
	 *  FOC2 = 1     : NON PWM mode.
	 *  WGM2 1:0     : They are set according to the parameter Mode used, it
	 *  			   will set the mode to CTC or Normal if the user choose
	 *  			   any of them in the configurations
	 *  CS2 2:0      : They are set according to the Prescaler chosen by the
	 *  			   used at the dynamic configurations.
	 */

	TCCR2 = (1<<FOC2) |  (a_configuration_Ptr->s_prescaler) \
					  |( (a_configuration_Ptr->s_timerMode & 0x01) << WGM20) \
					  |( (a_configuration_Ptr->s_timerMode & 0x02) <<(WGM21-1)) ;


}


/*******************************************************************************
 *                             ISR's Definitions                               *
 *******************************************************************************/

/************** Timer0's ISR **************/
/*
 * Description :
 * This function will call the call back function which the user provides form the
 * application. This ISR will be called when Timer0 finishes counting at Normal mode
 */
ISR(TIMER0_OVF_vect)
{
	if(g_callBackFunctionforTimer0_Ptr != NULL_PTR)
	{
		(* g_callBackFunctionforTimer0_Ptr)();
	}
}

/*
 * Description :
 * This function will call the call back function which the user provides form the
 * application. This ISR will be called when Timer0 finishes counting at CTC mode
 */
ISR(TIMER0_COMP_vect)
{
	if(g_callBackFunctionforTimer0_Ptr != NULL_PTR)
	{
		(* g_callBackFunctionforTimer0_Ptr)();
	}
}


/************** Timer1's ISR **************/
/*
 * Description :
 * This function will call the call back function which the user provides form the
 * application. This ISR will be called when Timer1 finishes counting at Normal mode
 */
ISR(TIMER1_OVF_vect)
{
	if(g_callBackFunctionforTimer1_Ptr != NULL_PTR)
	{
		(* g_callBackFunctionforTimer1_Ptr)();
	}
}

/*
 * Description :
 * This function will call the call back function which the user provides form the
 * application. This ISR will be called when Timer1 finishes counting at CTC mode
 */
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackFunctionforTimer1_Ptr != NULL_PTR)
	{
		(* g_callBackFunctionforTimer1_Ptr)();
	}
}


/************** Timer2's ISR **************/
/*
 * Description :
 * This function will call the call back function which the user provides form the
 * application. This ISR will be called when Timer2 finishes counting at Normal mode
 */
ISR(TIMER2_OVF_vect)
{
	if(g_callBackFunctionforTimer2_Ptr != NULL_PTR)
	{
		(* g_callBackFunctionforTimer2_Ptr)();
	}
}

/*
 * Description :
 * This function will call the call back function which the user provides form the
 * application. This ISR will be called when Timer2 finishes counting at CTC mode
 */
ISR(TIMER2_COMP_vect)
{
	if(g_callBackFunctionforTimer2_Ptr != NULL_PTR)
	{
		(* g_callBackFunctionforTimer2_Ptr)();
	}
}

/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/

/*
 * Description :
 * This function responsible for Turing on the timer module to calculate time for
 * all three timers and set the configuration needed for a specific timer Dynamically:
 *
 *  1. Set the required clock for timer
 * 	2. Set the Operating Mode
 * 	3. Put initial value to start counting
 * 	4. Put a compare value in case of using CTC Mode
 */
void TIMER_init(const DynamicConfiguration_TIMER * a_configuration_Ptr)
{
	if( a_configuration_Ptr->s_timerID == TIMER0)
	{
		/*	Initializing Timer 0 according to the Dynamic configurations   */
		TIMER0_init(a_configuration_Ptr);
	}
	else if( a_configuration_Ptr->s_timerID == TIMER1)
	{
		/*	Initializing Timer 1 according to the Dynamic configurations   */
		TIMER1_init(a_configuration_Ptr);
	}
	else if( a_configuration_Ptr->s_timerID == TIMER2)
	{
		/*	Initializing Timer 2 according to the Dynamic configurations   */
		TIMER2_init(a_configuration_Ptr);
	}
}

/*
 * Description :
 * This function takes the address of the function that need to be called when
 * Timer finishes counting.
 * It save the argument address of the function in a Global one so that it can be
 * called from the ISR.
 */
void TIMER_setCallBackFunction(TimerSelect a_timerID ,void (* a_callBackfunction_Ptr)(void))
{
	if( a_timerID == TIMER0)
	{
		/* Save the address of the Call back function in a global variable of Timer0 */
		g_callBackFunctionforTimer0_Ptr = a_callBackfunction_Ptr;
	}
	else if( a_timerID == TIMER1)
	{
		/* Save the address of the Call back function in a global variable of Timer1 */
		g_callBackFunctionforTimer1_Ptr = a_callBackfunction_Ptr;

	}
	else if( a_timerID == TIMER2)
	{
		/* Save the address of the Call back function in a global variable of Timer2 */
		g_callBackFunctionforTimer2_Ptr = a_callBackfunction_Ptr;
	}
}

/*
 * Description:
 * This function will Turn off the Timer which is selected by the user as an input.
 */
void TIMER_deInit(TimerSelect a_timerID)
{
	if( a_timerID == TIMER0)
	{
		/*	Turn Off Timer0 clock */
		TCCR0 = 0;
		/*	Resting the values of initial value and compare value  */
		TCNT0 = 0;
		OCR0  = 0;
		/*	Disabling the Interrupts of CTC , Normal mode in Timer0  */
		TIMSK &= ~(1<<OCIE0);
		TIMSK &= ~(1<<TOIE0);
	}
	else if( a_timerID == TIMER1)
	{
		uint8 L_sreg = SREG;

		/* Turn Timer 1 OFF	*/
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

		TCNT1 = 0 ;		/*	Clear the initial value register	*/
		OCR1A = 0 ;		/*	Clear the Compare value register	*/
		SREG = L_sreg; 	/*	Return to the default status control register values  */

		/*	Disabling the Interrupts of CTC , Normal mode in Timer1  */
		TIMSK &= ~(1<<OCIE1A);
		TIMSK &= ~(1<<TOIE1);

	}
	else if( a_timerID == TIMER2)
	{
		/*	Turn Off Timer2 clock */
		TCCR2 = 0;
		/*	Resting the values of initial value and compare value  */
		TCNT2 = 0;
		OCR2  = 0;
		/*	Disabling the Interrupts of CTC , Normal mode in Timer2  */
		TIMSK &= ~(1<<OCIE2);
		TIMSK &= ~(1<<TOIE2);

	}
}
