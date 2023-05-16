/******************************************************************************
 *
 * Module: Timer0,1,2  Modules
 *
 * File Name: timer.h
 *
 * Description: Header file for the Timer0,1,2 driver.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
/*
 * Description:
 * The Timer  need a clock so the module can operate so we have multiple prescaler.
 * According to the Frequency the user need a divisor is chosen.
 * This is used as Dynamic configuration to the initialization for the Timer.
 *
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
}Prescaler_TIMER;

/*
 * Description:
 * This enumeration also used for Timer Dynamic configuration it is used to choose
 * The operating Mode of the Timer.
 * Normal Mode has a one Mask for all timer While CTC mode has two	, one for both
 * Timer0,2 and one for Timer1. This is because these different masks helps me in
 * initialization function with insertions.
 * Timer1 will work with CTC mode with Top value OCR1A
 */
typedef enum
{
	NORMAL_MODE , T0_T2_CTC_MODE = 2 , T1_CTC_MODE = 4
}OperatingMode_TIMER;

/*
 * Description:
 * This enumeration is used for Timer Dynamic configuration it is used to Select
 * The Timer you want to work with out of 3.
 */
typedef enum
{
	TIMER0 , TIMER1 ,TIMER2
}TimerSelect;


/*
 * Description:
 * This structure has all the dynamic configuration for the Timer module to works
 * as the user want. All the user need to do is :
 * 1) Select the timer
 * 2) Choose the Mode
 * 3) Choose a prescaler
 * 4) Initial value for the counter to start counting
 * 5) Compare value in case of using CTC mode
 */
typedef struct
{
	TimerSelect					s_timerID;
	OperatingMode_TIMER			s_timerMode;
	Prescaler_TIMER				s_prescaler;
	uint16 						s_initialValue;
	uint16						s_compareValue;
}DynamicConfiguration_TIMER;

/*******************************************************************************
 *                          Public Function Prototype	                       *
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
void TIMER_init(const DynamicConfiguration_TIMER * a_configuration_Ptr);

/*
 * Description :
 * This function takes the address of the function that need to be called when
 * Timer finishes counting.
 * It save the argument address of the function in a Global one so that it can be
 * called from the ISR.
 */
void TIMER_setCallBackFunction(TimerSelect a_timerID ,void (* a_callBackfunction_Ptr)(void));

/*
 * Description:
 * This function will Turn off the Timer which is selected by the user as an input.
 */
void TIMER_deInit(TimerSelect a_timerID);



#endif /* TIMER_H_ */
