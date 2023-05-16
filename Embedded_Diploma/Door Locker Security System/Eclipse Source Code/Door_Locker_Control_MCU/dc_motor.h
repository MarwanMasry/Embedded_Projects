 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                          Definition - Configurations                        *
 *******************************************************************************/
#define CLEAR_ALL_BITS_EXCEPT_FIRST_TWO_BITS_MUSK		(0X03U)


/*	Static configuration of DC Motor Two input pins	*/
#define DC_MOTOR_PORT_ID		PORTB_ID

#define DC_MOTOR_IN1_PIN		PIN0_ID
#define DC_MOTOR_IN2_PIN		PIN1_ID

/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
/*
 * Description:
 * This enum is used to get the state of motor either if we want to rotate it
 * Clockwise or Anti clockwise or turn it off this is done by modifying the input
 * pins of H Bridge driver
 *
 * 0 0   : OFF
 * 0 1   : Anti Clockwise
 * 1 0   : Clockwise
 */
typedef enum
{
	OFF , ROTATE_CLOCKWISE=0X02 , ROTATE_ANTICLOCKWISE=0X01
}MotorState;

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/*
 *	Description:
 *	It initialize the DC Motor by making it's INT pin as output pins in MCU
 *	and setting the Motor OFF at the beginning.
 */
void DC_MOTOR_init(void);

/*
 *	Description:
 *	This function takes the state of motor either it is Off , ClockWise ,Anticlockwise
 *	if the input is a value not a defined state , the function check First two bits
 *	of the value and according to them a state will be set.
 *	If the input is any value rather than the Three states of Motor it will be
 *	set to OFF mode
 *	It also provide the speed of motor that the user supply according to the duty
 *	cycle input from the user by setting a PWM signal to the enable of H bride.
 *	If the caller entered a duty cycle out of range [0 100] the function won't
 *	supply the enable to H bridge.
 */
void DC_MOTOR_setMotorState(MotorState a_state ,uint8 a_speed);




#endif /* DC_MOTOR_H_ */
