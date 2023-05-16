 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for Keypad Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_



/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                         Definition - Configuration                          *
 *******************************************************************************/

/* Static configuration for Keypad port*/
#define KEYPAD_PORT_ID						PORTB_ID

#define KEYPAD_FIRST_ROW_PIN_ID				PIN0_ID
#define KEYPAD_FIRST_COLUMN_PIN_ID			PIN4_ID

/* Static configuration for Keypad number of column and rows */
#define KEYPAD_NUM_OF_COLUMNS				4
#define KEYPAD_NUM_OF_ROWS					4


/* Static configuration for Keypad To work with Internal Pull up resistor if it
 * is supported by MCU , If it is not supported by MCU, This will be handled
 * in KEYPAD_getKeyPressed() function in keypad.c file
 */
#define SET_KEYPAD_USING_INTERNAL_PUR		TRUE

/* Static configuration for Keypad Logic.
 *
 * External/Internal Pull up resistor :
 * KEYPAD_BUTTON_PRESSED	is LOGIC_LOW
 * KEYPAD_BUTTON_RELEASED	is LOGIC_HIGH
 *
 * External Pull down resistor:
 * KEYPAD_BUTTON_PRESSED	is LOGIC_HIGH
 * KEYPAD_BUTTON_RELEASED	is LOGIC_LOW
 */
#define KEYPAD_BUTTON_PRESSED				LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED				LOGIC_HIGH


/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*
 * Description:
 * This is Synchronous function in which it won't exit from function until it get
 * only one reading from the keypad [read only one input from keypad]
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
