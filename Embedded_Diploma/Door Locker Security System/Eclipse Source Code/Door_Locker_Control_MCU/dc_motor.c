 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                          Public Function Definition	                       *
 *******************************************************************************/
/*
 *	Description:
 *	It initialize the DC Motor by making it's INT pin as output pins in MCU
 *	and setting the Motor OFF at the beginning.
 */
void DC_MOTOR_init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID , DC_MOTOR_IN1_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID , DC_MOTOR_IN2_PIN,PIN_OUTPUT);

	/*
	 * Set the Motor OFF at the beginning.
	 * To Turn Off Motor :
	 * DC MOTOR IN1 BIT : 0
	 * DC MOTOR IN2 BIT : 0
	 */
	GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN1_PIN,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN2_PIN,LOGIC_LOW);

}


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
void DC_MOTOR_setMotorState(MotorState a_state ,uint8 a_speed)
{

	if( (a_speed < 0) || (a_speed > 100) )
	{
		/* If the caller entered a duty cycle out of range [0 100] the function won't
		 * supply the enable to H bridge.
 		 */
	}
	else
	{
		/*	Set the speed of the Motor according to duty cycle/ speed of the motor	*/
		Timer0_PWM_Init(a_speed);
	}


	/*	Clear all bits except first two bit to check them and set mode according to
	 *  these two bit value.
	 */
	a_state &= CLEAR_ALL_BITS_EXCEPT_FIRST_TWO_BITS_MUSK;

	switch(a_state)
	{
		case OFF:
			/*
			 * To Turn Off Motor :
			 * DC MOTOR IN1 BIT : 0
			 * DC MOTOR IN2 BIT : 0
			 */
			GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN1_PIN,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN2_PIN,LOGIC_LOW);
			break;

		case ROTATE_CLOCKWISE:
			/*
			 * To Turn Off Motor :
			 * DC MOTOR IN1 BIT : 0
			 * DC MOTOR IN2 BIT : 1
			 */

			GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN1_PIN,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN2_PIN,LOGIC_HIGH);
			break;

		case ROTATE_ANTICLOCKWISE:
			/*
			 * To Turn Off Motor :
			 * DC MOTOR IN1 BIT : 1
			 * DC MOTOR IN2 BIT : 0
			 */
			GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN1_PIN,LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN2_PIN,LOGIC_LOW);
			break;

		default:
			/*
			 * If the input is any value rather than the Three states of Motor it will be
			 *set to OFF mode
			 */
			GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN1_PIN,LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_PORT_ID , DC_MOTOR_IN2_PIN,LOGIC_LOW);
			break;
	}
}
