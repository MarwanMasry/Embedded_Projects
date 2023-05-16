 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Source file for the LCD driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "lcd.h"
#include "gpio.h"
#include <avr/delay.h>
#include "common_macros.h"
#include <stdlib.h>

/*******************************************************************************
 *                          Public Function Definition	                       *
 *******************************************************************************/
/*
 * Description:
 * This function initialize the required pins to be output for LCD and send the
 * needed commands to the LCD MCU to initialize it.
 */
void LCD_init(void)
{
#if	((LCD_DATA_PIN_MODE == 4))
	uint8 i ;
#endif

	/*	Initialize RS , RW , E as Output	*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID , LCD_RS_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID , LCD_RW_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID , LCD_E_PIN_ID , PIN_OUTPUT);

#if	((LCD_DATA_PIN_MODE == 4))
	/*	Initialize the 4 data Pins of data as output 	*/
	for(i = 0 ; i < 4  ; ++i)
	{
		GPIO_setupPinDirection( LCD_DATA_PORT_ID , LCD_FIRST_DATA_PIN_ID + i , PIN_OUTPUT);
	}

	/*	Send Command return home for  cursor to home position (address 0)	*/
	LCD_sendCommand(LCD_RETURN_HOME);

	/*	Send Command to Choose 4 bits data mode		*/
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#else
	/*	Initialize the all the data port as output 	*/
	GPIO_setupPortDirection( LCD_DATA_PORT_ID , PORT_OUTPUT);

	/*	Send Command return home for  cursor to home position (address 0)	*/
	LCD_sendCommand(LCD_RETURN_HOME);

	/*	Send Command to Choose 8 bits data mode		*/
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	/*	Send Command to turn Display on and make cursor OFF	*/
	LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_OFF);

	/*	Send Command to clear all the screen DDRAM data	*/
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}


/*
 * Description:
 * In this function we will send the command to the LCD MCU following the steps
 * and rules of AC/Timing characteristics of the LCD in data sheet and the LCD
 * will do the required command.
 */
void LCD_sendCommand(uint8 a_command)
{
#if (LCD_DATA_PIN_MODE == 4)
	uint8 L_portValue = 0;
	uint8 L_savingBitsMask = 0xF0;
#endif

	/*	RS = 0 to write in Command register	*/
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID , LOGIC_LOW);
	/*	RW = 0 to write not read	*/
	GPIO_writePin(LCD_RW_PORT_ID , LCD_RW_PIN_ID , LOGIC_LOW);

	/*  Delay for Processing Tas = 50 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Enable LCD E = 1	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_HIGH);

	/*  Delay for Processing Tpw - tdsw = 290 ns - 100 ns = 190 ns  in
	 *  AC characteristics in data sheet
	 */
	_delay_ms(1);

#if  (LCD_DATA_PIN_MODE == 4)
	/*	If we use 4 bit we need to save the value of bits here as we will change
	 *  only 4 bit not all the port
	 */
	L_portValue = GPIO_readPort(LCD_DATA_PORT_ID);

	/*	Write the Higher Byte of the command in the 4 bits and conserve other Bits	*/
	L_portValue = (L_portValue & ROL(L_savingBitsMask,LCD_FIRST_DATA_PIN_ID)) | ( ((a_command & 0xF0)>>4) << LCD_FIRST_DATA_PIN_ID ) ;
	GPIO_writePort(LCD_DATA_PORT_ID , L_portValue);

	/*  Delay for Processing Tdsw = 100 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Disable LCD E = 0	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_LOW);

	/*  Delay for Processing Th = 13 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Write 0 to the 4 bits of Data bits	*/
	L_savingBitsMask = 0xF0;
	L_portValue = L_portValue & ROL(L_savingBitsMask,LCD_FIRST_DATA_PIN_ID) ;

	/*	Enable LCD E = 1	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_HIGH);

	/*  Delay for Processing Tpw - tdsw = 290 ns - 100 ns = 190 ns  in
	 *  AC characteristics in data sheet
	 */
	_delay_ms(1);


	/*	Write the Lower Byte of the command in the 4 bits and conserve other Bits	*/
	L_savingBitsMask = 0xF0;
	L_portValue = GPIO_readPort(LCD_DATA_PORT_ID);
	L_portValue = (L_portValue & ROL(L_savingBitsMask,LCD_FIRST_DATA_PIN_ID)) | ( (a_command & 0x0F) << LCD_FIRST_DATA_PIN_ID ) ;
	GPIO_writePort(LCD_DATA_PORT_ID , L_portValue);

	/*  Delay for Processing Tdsw = 100 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Disable LCD E = 0	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_LOW);

	/*  Delay for Processing Th = 13 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Write 0 to the 4 bits of Data bits	*/
	L_savingBitsMask = 0xF0;
	L_portValue = L_portValue & ROL(L_savingBitsMask,LCD_FIRST_DATA_PIN_ID) ;

#else
	/*	Write the Command in all 8 data bits	*/
	GPIO_writePort(LCD_DATA_PORT_ID , a_command );

	/*  Delay for Processing Tdsw = 100 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Disable LCD E = 0	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_LOW);

	/*  Delay for Processing Th = 13 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Write 0 to the 8 bits of Data bits	*/
	GPIO_writePort(LCD_DATA_PORT_ID , LOGIC_LOW );

#endif
}

/*
 * Description:
 * In this function we will send the data to the LCD MCU following the steps
 * and rules of AC/Timing characteristics of the LCD in data sheet and The LCD
 * will display it on the screen.
 */
void LCD_displayCharacter(uint8 a_character)
{
#if (LCD_DATA_PIN_MODE == 4)
	uint8 L_portValue = 0;
	uint8 L_savingBitsMask = 0xF0;
#endif

	/*	RS = 1 to write in Data register	*/
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID , LOGIC_HIGH);
	/*	RW = 0 to write not read	*/
	GPIO_writePin(LCD_RW_PORT_ID , LCD_RW_PIN_ID , LOGIC_LOW);

	/*  Delay for Processing Tas = 50 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Enable LCD E = 1	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_HIGH);

	/*  Delay for Processing Tpw - tdsw = 290 ns - 100 ns = 190 ns  in
	 *  AC characteristics in data sheet
	 */
	_delay_ms(1);

#if  (LCD_DATA_PIN_MODE == 4)
	/*	If we use 4 bit we need to save the value of bits here as we will change
	 *  only 4 bit not all the port
	 */
	L_portValue = GPIO_readPort(LCD_DATA_PORT_ID);

	/*	Write the Higher Byte of the command in the 4 bits and conserve other Bits	*/
	L_portValue = (L_portValue & ROL(L_savingBitsMask,LCD_FIRST_DATA_PIN_ID)) | ( ((a_character & 0xF0)>>4) << LCD_FIRST_DATA_PIN_ID ) ;
	GPIO_writePort(LCD_DATA_PORT_ID , L_portValue);

	/*  Delay for Processing Tdsw = 100 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Disable LCD E = 0	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_LOW);

	/*  Delay for Processing Th = 13 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Write 0 to the 4 bits of Data bits	*/
	L_savingBitsMask = 0xF0;
	L_portValue = L_portValue & ROL(L_savingBitsMask,LCD_FIRST_DATA_PIN_ID) ;

	/*	Enable LCD E = 1	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_HIGH);

	/*  Delay for Processing Tpw - tdsw = 290 ns - 100 ns = 190 ns  in
	 *  AC characteristics in data sheet
	 */
	_delay_ms(1);


	/*	Write the Lower Byte of the command in the 4 bits and conserve other Bits	*/
	L_savingBitsMask = 0xF0;
	L_portValue = GPIO_readPort(LCD_DATA_PORT_ID);
	L_portValue = (L_portValue & ROL(L_savingBitsMask,LCD_FIRST_DATA_PIN_ID)) | ( (a_character & 0x0F) << LCD_FIRST_DATA_PIN_ID ) ;
	GPIO_writePort(LCD_DATA_PORT_ID , L_portValue);

	/*  Delay for Processing Tdsw = 100 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Disable LCD E = 0	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_LOW);

	/*  Delay for Processing Th = 13 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Write 0 to the 4 bits of Data bits	*/
	L_savingBitsMask = 0xF0;
	L_portValue = L_portValue & ROL(L_savingBitsMask,LCD_FIRST_DATA_PIN_ID) ;

#else
	/*	Write the Command in all 8 data bits	*/
	GPIO_writePort(LCD_DATA_PORT_ID , a_character );

	/*  Delay for Processing Tdsw = 100 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Disable LCD E = 0	*/
	GPIO_writePin(LCD_E_PORT_ID , LCD_E_PIN_ID , LOGIC_LOW);

	/*  Delay for Processing Th = 13 ns  in AC characteristics in data sheet	*/
	_delay_ms(1);

	/*	Write 0 to the 8 bits of Data bits	*/
	GPIO_writePort(LCD_DATA_PORT_ID , LOGIC_LOW );

#endif

}

/*
 * Description:
 * This function move the cursor in the LCD screen to any position in the
 * dimension of the LCD.
 * If the row or column of the input is larger than the dimension of the LCD
 * the function won't move the cursor.
 */
void LCD_moveCursor(uint8 a_row , uint8 a_col)
{
	uint8	L_memoryAddress = 0;

	/*
	 *  If the row or column of the input is larger than the dimension of the LCD
	 * the function won't move the cursor.
	 */
	if( (a_row >= LCD_NUM_OF_ROW) || (a_col >= LCD_NUM_OF_COLUMN))
	{
		/*	Do Nothing	*/
	}
	else
	{
		/*	In order to access a location in DDRAM we must do this
		 *  We must send a command of 8 bit =  0x80  |  [address you want]
		 *  we calculate the address by using the data sheet and know the
		 *  Mapped registers of each row.
		 */
		switch(a_row)
		{
			case 0:
				L_memoryAddress = a_col;
				break;
			case 1:
				L_memoryAddress = a_col + 0x40;
				break;
			case 2:
				L_memoryAddress = a_col + 0x10;
				break;
			case 3:
				L_memoryAddress = a_col + 0x50;
				break;

		}
	}

	/*	Access the memory address in DDRAM by orring the memory address with 0x80
	 *	and send the result as command
	 */
	LCD_sendCommand( LCD_SET_CURSOR_LOCATION | L_memoryAddress );
}

/*
 * Description:
 * This function display a whole string in the Screen but take care
 * 1) The string will be written at cursor position or after the last character
 *    in the screen
 * 2) If the size of the string is larger than the remaining position at the line
 * 	  your string will be cut and only part of it will be displayed
 */
void LCD_displayString(const char *a_str)
{
	uint8 i = 0;

	/*	Loop though the array and each time display only one character	*/
	while( a_str[i] != '\0')
	{
		LCD_displayCharacter(a_str[i]);
		i++;
	}
}

/*
 * Description:
 * This function display a whole string in the Screen at specified row and column.
 * If the size of the string is larger than the remaining position at the Line
 * your string will be cut and only part of it will be displayed.
 */
void LCD_displayStringAtRowColumn(uint8 a_row , uint8 a_col , const char *a_str)
{
	/*	First move the Cursor to the required location	*/
	LCD_moveCursor(a_row , a_col);
	/*	Display the String	*/
	LCD_displayString(a_str);
}


/*
 * Description:
 * This function display a Number in the Screen but take care
 * 1) The Number will be written at cursor position or after the last character
 *    in the screen
 * 2) If the size of the Number is larger than the remaining position at the line
 * 	  your Number will be cut and only part of it will be displayed
 */
void LCD_displayNumber(sint32 a_number)
{
	/*	Buffer to save the ASCI values of the number	*/
	char L_buff [16] = {0};

	/*	Function convert each separate number to ASCI value and save it to L_buff
	 *  10 is to tell the function to convert a_number to ASCI of number with base
	 *  10.
	 */
	itoa(a_number , L_buff , 10);

	/*	Display the String	*/
	LCD_displayString(L_buff);
}

/*
 * Description:
 * This function display a whole Number in the Screen at specified row and column.
 * If the size of the Number is larger than the remaining position at the Line
 * your Number will be cut and only part of it will be displayed.
 */
void LCD_displayNumberAtRowColumn(uint8 a_row , uint8 a_col , sint32 a_number)
{
	/*	First move the Cursor to the required location	*/
	LCD_moveCursor(a_row , a_col);
	/*	Display the String	*/
	LCD_displayNumber(a_number);
}

/*
 * Description:
 * This function Clears display and returns cursor to the home position (address 0).
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_SCREEN);
}

/*
 * Description:
 * This function shift all 2 Lines by one position to left
 * You may lose data if you shift left to a location that exceed the dimension
 * of the LCD
 */
void LCD_shiftLeftEntireDisplayByOnePosition(void)
{
	LCD_sendCommand(LCD_SHIFT_LEFT_ENTIRE_DISPLAY);
}

/*
 * Description:
 * This function shift all 2 Lines by one position to right
 * You may lose data if you shift right to a location that exceed the dimension
 * of the LCD
 */
void LCD_shiftRightEntireDisplayByOnePosition(void)
{
	LCD_sendCommand(LCD_SHIFT_RIGHT_ENTIRE_DISPLAY);
}

/*
 * Description:
 * This function turn off the display of the screen without clearing its content
 * [it don't clear the DDRAM content] which mean if you call this function it
 * appear the LCD is cleared but when it you call function display On the content
 * of the old data will appear again.
 */
void LCD_displayOff(void)
{
	LCD_sendCommand(LCD_DISPLAY_OFF_CURSOR_OFF);
}

/*
 * Description:
 * This function will turn on display and any character exists on the DDRAM of
 * the LCD will appear in the screen
 */
void LCD_displayOn(void)
{
	LCD_sendCommand(LCD_DISPLAY_ON_CURSOR_BLINKING);
}

