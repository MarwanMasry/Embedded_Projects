 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the AVR GPIO driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                          Definition - Configurations                        *
 *******************************************************************************/
#define NUM_OF_PORTS			4
#define NUM_OF_PINS_PER_PORT	8

#define PORTA_ID				0
#define PORTB_ID				1
#define PORTC_ID				2
#define PORTD_ID				3

#define PIN0_ID					0
#define PIN1_ID					1
#define PIN2_ID					2
#define PIN3_ID					3
#define PIN4_ID					4
#define PIN5_ID					5
#define PIN6_ID					6
#define PIN7_ID					7

/*	Static configuration whether we want to support Internal Pull up resistor or not*/
#define THIS_MCU_SUPPORT_INTERNAL_PUR	TRUE

/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0XFF
}PortDirectionType;


/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*
 * Description:
 * This function sets the pin direction as input or output according to
 * the arguments, First one specifies the port in which the pin exists and the
 * Second one is the pin number and the Third one is direction of the pin.
 *
 * If the input port number or pin number are not correct, The function will
 * not handle the request.
 */
void GPIO_setupPinDirection(uint8 a_portNumber ,uint8 a_pinNumber ,PinDirectionType a_direction);


/*
 * Description:
 * This function writes Logic High or Logic Low  in the pin according to the parameters
 * specification. First argument is  the port in which the pin exisits and theSecond
 * one is the pin number and the Third one is value in which it will be written
 * a Logic High or Logic Low.
 *
 * If the input port number or pin number are not correct, The function will
 * not handle the request.
 * IF the value is not Logic High or Logic Low the function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 a_portNumber ,uint8 a_pinNumber ,uint8 value);


/*
 * Description:
 * This function read the value of a specific pin if it is Logic High or Logic Low.
 *
 * If the input port number or pin number are not correct, The function will
 * return LOGIC_LOW.
 */
uint8 GPIO_readPin(uint8 a_portNumber ,uint8 a_pinNumber);


/*
 * Description:
 * This Function set the direction of all the pins the user have two options,
 * First : you can use enums PORT_INPUT , PORT_OUTPUT to set all the port as
 * input or output.
 * Second : enter any 8 bits as input and according to this values the bits
 * direction will be set.
 *
 * If the input port number is not correct, The function will not handle the request.
 *
 */
void GPIO_setupPortDirection(uint8 a_portNumber ,PortDirectionType a_direction);


/*
 * Description:
 * This function write a value in the PORT register of specific Port [A,B,C,D] if
 * The port direction is output.
 * If the port direction is input it activate/deactivate the internal Pull-Up resistor.
 *
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 a_portNumber ,uint8 a_value);


/*
 * Description:
 * This function return the value of the required port register.
 *
 * If the input port number is not correct, The function will return 0 value.
 */
uint8 GPIO_readPort(uint8 a_portNumber);


#if (THIS_MCU_SUPPORT_INTERNAL_PUR == TRUE)
/*
 * Description:
 * This function activate the internal Pull up resistor for a specific pin if and
 * only the pin direction is input
 *
 * If the direction of the pin is output it won't activate the internal PUR
 * it will be write 1 on the pin
 */
void GPIO_activate_intenalPUR_forPin(uint8 a_portNumber ,uint8 a_pinNumber);

/*
 * Description:
 * This function deactivate the internal Pull up resistor for a specific pin if and
 * only the pin direction is input
 *
 * If the direction of the pin is output it won't deactivate the internal PUR
 * it will be write 0 on the pin
 */
void GPIO_deactivate_intenalPUR_forPin(uint8 a_portNumber ,uint8 a_pinNumber);

#endif

#endif /* GPIO_H_ */
