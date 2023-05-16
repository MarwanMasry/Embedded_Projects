 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the AVR GPIO driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "gpio.h"
#include "common_macros.h"  /* To use the macros like SET_BIT */
#include <avr/io.h>			/* To use the I/O Registers */

/*******************************************************************************
 *                          Public Function Definition	                       *
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
void GPIO_setupPinDirection(uint8 a_portNumber ,uint8 a_pinNumber ,PinDirectionType a_direction)
{

	/*
	 *  If the input port number or pin number are not correct, The function will
	 *  not handle the request.
	 */
	if( (a_portNumber >= NUM_OF_PORTS) || (a_pinNumber >= NUM_OF_PINS_PER_PORT ) )
	{
		/*	Do nothing	*/
	}
	else
	{
		/*	set the pin direction as input or output	*/
		switch(a_portNumber)
		{
		case PORTA_ID:
			if(a_direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRA,a_pinNumber);
			}
			else
			{
				SET_BIT(DDRA,a_pinNumber);
			}
			break;

		case PORTB_ID:
			if(a_direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRB,a_pinNumber);
			}
			else
			{
				SET_BIT(DDRB,a_pinNumber);
			}
			break;

		case PORTC_ID:
			if(a_direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRC,a_pinNumber);
			}
			else
			{
				SET_BIT(DDRC,a_pinNumber);
			}
			break;

		case PORTD_ID:
			if(a_direction == PIN_INPUT)
			{
				CLEAR_BIT(DDRD,a_pinNumber);
			}
			else
			{
				SET_BIT(DDRD,a_pinNumber);
			}
			break;

		default:
			/*	Do Nothing	*/
			break;
		}
	}
}


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
void GPIO_writePin(uint8 a_portNumber ,uint8 a_pinNumber ,uint8 a_value)
{
	/*
	 *  If the input port number or pin number are not correct, The function will
	 *  not handle the request.
	 *  IF the value is not Logic High or Logic Low the function will not handle the request
	 */
	if( (a_portNumber >= NUM_OF_PORTS) || (a_pinNumber >= NUM_OF_PINS_PER_PORT ) || (a_value > 1))
	{
		/*	Do nothing	*/
	}
	else
	{
		/*	Writes 1 or 0  in the pin	*/
		switch(a_portNumber)
		{
		case PORTA_ID:
			if(a_value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTA,a_pinNumber);
			}
			else
			{
				SET_BIT(PORTA,a_pinNumber);
			}
			break;

		case PORTB_ID:
			if(a_value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTB,a_pinNumber);
			}
			else
			{
				SET_BIT(PORTB,a_pinNumber);
			}
			break;

		case PORTC_ID:
			if(a_value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTC,a_pinNumber);
			}
			else
			{
				SET_BIT(PORTC,a_pinNumber);
			}
			break;

		case PORTD_ID:
			if(a_value == LOGIC_LOW)
			{
				CLEAR_BIT(PORTD,a_pinNumber);
			}
			else
			{
				SET_BIT(PORTD,a_pinNumber);
			}
			break;

		default:
			/*	Do Nothing	*/
			break;
		}
	}
}

/*
 * Description:
 * This function read the value of a specific pin if it is Logic High or Logic Low.
 *
 * If the input port number or pin number are not correct, The function will
 * return LOGIC_LOW.
 */
uint8 GPIO_readPin(uint8 a_portNumber ,uint8 a_pinNumber)
{
	uint8 L_pinValue = LOGIC_LOW;

	/*
	 * If the input port number or pin number are not correct, The function will
	 * not handle the request.
     */

	if( (a_portNumber >= NUM_OF_PORTS) || (a_pinNumber >= NUM_OF_PINS_PER_PORT ))
	{
		/*	Do nothing	*/
	}
	else
	{
		/*	 Read the value of a specific pin if it is Logic High or Logic Low.	*/
		switch(a_portNumber)
		{
		case PORTA_ID:
			if( BIT_IS_SET(PINA,a_pinNumber) )
			{
				L_pinValue = LOGIC_HIGH;
			}
			else
			{
				L_pinValue = LOGIC_LOW;
			}
			break;

		case PORTB_ID:
			if( BIT_IS_SET(PINB,a_pinNumber) )
			{
				L_pinValue = LOGIC_HIGH;
			}
			else
			{
				L_pinValue = LOGIC_LOW;
			}			break;

		case PORTC_ID:
			if( BIT_IS_SET(PINC,a_pinNumber) )
			{
				L_pinValue = LOGIC_HIGH;
			}
			else
			{
				L_pinValue = LOGIC_LOW;
			}
			break;

		case PORTD_ID:
			if( BIT_IS_SET(PIND,a_pinNumber) )
			{
				L_pinValue = LOGIC_HIGH;
			}
			else
			{
				L_pinValue = LOGIC_LOW;
			}
			break;

		default:
			/*	Do Nothing	*/
			break;
		}
	}
	return L_pinValue;
}


/*
 * Description:
 * This Function set the direction of all the pins the user have two options,
 *  First : you can use enums PORT_INPUT , PORT_OUTPUT to set all the port as
 *  input or output.
 *  Second : enter any 8 bits as input and according to this values the bits
 *  direction will be set.
 *
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 a_portNumber ,PortDirectionType a_direction)
{

	/*	If the input port number is greater than NUM_OF_PORTS  The function will
	 * not handle the request.   */
	if( a_portNumber >= NUM_OF_PORTS )
	{
		/*	Do nothing	*/
	}
	else
	{
		/*	set the direction of all pins of a specific port */
		switch(a_portNumber)
		{
		case PORTA_ID:
			DDRA = a_direction;
			break;

		case PORTB_ID:
			DDRB = a_direction;
			break;

		case PORTC_ID:
			DDRC = a_direction;
			break;

		case PORTD_ID:
			DDRD = a_direction;
			break;

		default:
			/*	Do Nothing	*/
			break;
		}
	}

}

/*
 * Description:
 * This function write a value in the PORT register of specific Port [A,B,C,D] if
 * The port direction is output.
 * If the port direction is input it activate/deactivate the internal Pull-Up resistor.
 *
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 a_portNumber ,uint8 a_value)
{

	/*	If the input port number  is greater than NUM_OF_PORTS The function will
	 * not handle the request.
	 */
	if( a_portNumber >= NUM_OF_PORTS )
	{
		/*	Do nothing	*/
	}
	else
	{
		/* Write the port value as required */
		switch(a_portNumber)
		{
		case PORTA_ID:
			PORTA = a_value;
			break;

		case PORTB_ID:
			PORTB = a_value;
			break;

		case PORTC_ID:
			PORTC = a_value;
			break;

		case PORTD_ID:
			PORTD = a_value;
			break;

		default:
			/*	Do Nothing	*/
			break;
		}
	}
}


/*
 * Description:
 * This function return the value of the required port register.
 *
 * If the input port number is not correct, The function will return 0 value.
 */
uint8 GPIO_readPort(uint8 a_portNumber)
{
	uint8 L_portValue = 0;

	/*	 If the input port number is not correct, The function will return 0 value.	*/
	if( a_portNumber >= NUM_OF_PORTS )
	{
		/*	Do nothing	*/
	}
	else
	{
		/* Return the value of the required port register */
		switch(a_portNumber)
		{
		case PORTA_ID:
			L_portValue = PINA;
			break;

		case PORTB_ID:
			L_portValue = PINB;
			break;

		case PORTC_ID:
			L_portValue = PINC;
			break;

		case PORTD_ID:
			L_portValue = PIND;
			break;

		default:
			/*	Do Nothing	*/
			break;
		}
	}
	return L_portValue;
}


#if (THIS_MCU_SUPPORT_INTERNAL_PUR == TRUE)
/*
 * Description:
 * This function activate the internal Pull up resistor for a specific pin if and
 * only the pin direction is input
 *
 * If the direction of the pin is output it won't activate the internal PUR
 * it will be write 1 on the pin
 */
void GPIO_activate_intenalPUR_forPin(uint8 a_portNumber ,uint8 a_pinNumber)
{
	GPIO_writePin(a_portNumber , a_pinNumber , LOGIC_HIGH);
}

/*
 * Description:
 * This function deactivate the internal Pull up resistor for a specific pin if and
 * only the pin direction is input
 *
 * If the direction of the pin is output it won't deactivate the internal PUR
 * it will be write 0 on the pin
 */
void GPIO_deactivate_intenalPUR_forPin(uint8 a_portNumber ,uint8 a_pinNumber)
{
	GPIO_writePin(a_portNumber , a_pinNumber , LOGIC_LOW);
}

#endif
