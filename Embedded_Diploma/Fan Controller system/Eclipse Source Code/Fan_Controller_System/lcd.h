 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                          Definition - Configurations                        *
 *******************************************************************************/
/*	Port configurations	*/
#define LCD_DATA_PORT_ID					PORTC_ID
#define LCD_FIRST_DATA_PIN_ID				PIN0_ID

/*	RS , E , RW pins configurations */
#define LCD_RS_PORT_ID						PORTD_ID
#define LCD_RS_PIN_ID						PIN0_ID

#define LCD_RW_PORT_ID						PORTD_ID
#define LCD_RW_PIN_ID						PIN1_ID

#define LCD_E_PORT_ID						PORTD_ID
#define LCD_E_PIN_ID						PIN2_ID

/*	Port Row and column configurations	*/
#define LCD_NUM_OF_ROW						2
#define LCD_NUM_OF_COLUMN					16

/*	LCD data bit mode 8 bit or 4 bits	*/
#define LCD_DATA_PIN_MODE					8

#if (LCD_DATA_PIN_MODE != 4   && LCD_DATA_PIN_MODE != 8  )

#error "You must choose the mode of LCD either 4 bit or 8 bit mode ONLY."

#endif

/* LCD Commands */
#define LCD_TWO_LINES_EIGHT_BITS_MODE  		0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   		0x28

#define LCD_CLEAR_SCREEN               		0x01
#define LCD_RETURN_HOME               	 	0x02
#define LCD_DISPLAY_ON_CURSOR_OFF      		0x0C
#define LCD_DISPLAY_ON_CURSOR_ON       		0x0E
#define LCD_DISPLAY_ON_CURSOR_BLINKING      0x0F
#define LCD_DISPLAY_OFF_CURSOR_OFF      	0x08

#define LCD_SHIFT_LEFT_ENTIRE_DISPLAY		0X18
#define LCD_SHIFT_RIGHT_ENTIRE_DISPLAY		0X1C

#define LCD_SET_CURSOR_LOCATION        		0x80

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/*
 * Description:
 * This function initialize the required pins to be output for LCD and send the
 * needed commands to the LCD MCU to initialize it.
 */
void LCD_init(void);


/*
 * Description:
 * In this function we will send the command to the LCD MCU following the steps
 * and rules of AC/Timing characteristics of the LCD in data sheet and the LCD
 * will do the required command.
 */
void LCD_sendCommand(uint8 a_command);

/*
 * Description:
 * In this function we will send the data to the LCD MCU following the steps
 * and rules of AC/Timing characteristics of the LCD in data sheet and The LCD
 * will display it on the screen.
 */
void LCD_displayCharacter(uint8 a_character);

/*
 * Description:
 * This function move the cursor in the LCD screen to any position in the
 * dimension of the LCD.
 * If the row or column of the input is larger than the dimension of the LCD
 * the function won't move the cursor.
 */
void LCD_moveCursor(uint8 a_row , uint8 a_col);

/*
 * Description:
 * This function display a whole string in the Screen but take care
 * 1) The string will be written at cursor position or after the last character
 *    in the screen
 * 2) If the size of the string is larger than the remaining position at the line
 * 	  your string will be cut and only part of it will be displayed
 */
void LCD_displayString(const char *a_str);

/*
 * Description:
 * This function display a whole string in the Screen at specified row and column.
 * If the size of the string is larger than the remaining position at the Line
 * your string will be cut and only part of it will be displayed.
 */
void LCD_displayStringAtRowColumn(uint8 a_row , uint8 a_col , const char *a_str);


/*
 * Description:
 * This function display a Number in the Screen but take care
 * 1) The Number will be written at cursor position or after the last character
 *    in the screen
 * 2) If the size of the Number is larger than the remaining position at the line
 * 	  your Number will be cut and only part of it will be displayed
 */
void LCD_displayNumber(sint32 a_number);

/*
 * Description:
 * This function display a whole Number in the Screen at specified row and column.
 * If the size of the Number is larger than the remaining position at the Line
 * your Number will be cut and only part of it will be displayed.
 */
void LCD_displayNumberAtRowColumn(uint8 a_row , uint8 a_col , sint32 number);

/*
 * Description:
 * This function Clears display and returns cursor to the home position (address 0).
 */
void LCD_clearScreen(void);

/*
 * Description:
 * This function shift all 2 Lines by one position to left
 */
void LCD_shiftLeftEntireDisplayByOnePosition(void);

/*
 * Description:
 * This function shift all 2 Lines by one position to right
 */
void LCD_shiftRightEntireDisplayByOnePosition(void);

/*
 * Description:
 * This function turn off the display of the screen without clearing its content
 * [it don't clear the DDRAM content] which mean if you call this function it
 * appear the LCD is cleared but when it you call function display On the content
 * of the old data will appear again.
 */
void LCD_displayOff(void);

/*
 * Description:
 * This function will turn on display and any character exists on the DDRAM of
 * the LCD will appear in the screen
 */
void LCD_displayOn(void);


#endif /* LCD_H_ */
