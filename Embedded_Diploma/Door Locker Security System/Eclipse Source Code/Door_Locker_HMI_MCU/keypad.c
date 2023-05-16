 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for Keypad Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "keypad.h"
#include "gpio.h"

/*******************************************************************************
 *                         Private Function Deceleration	                   *
 *******************************************************************************/
#if (KEYPAD_NUM_OF_COLUMNS == 3)
/*
 * Description :
 * This function update the value of keypad button pressed according to keypad
 * which is used in real life or in simulator , Here this is the values in
 * 4x3 Keypad in Proteus
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_keyNumber);

#elif (KEYPAD_NUM_OF_COLUMNS == 4)

/*
 * Description :
 * This function update the value of keypad button pressed according to keypad
 * which is used in real life or in simulator , Here this is the values in
 * 4x4 Keypad in Proteus
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_keyNumber);

#endif

/*******************************************************************************
 *                          Public Function Definition	                       *
 *******************************************************************************/
/*
 * Description:
 * This is Synchronous function in which it won't exit from function until it get
 * only one reading from the keypad [read only one input from keypad]
 */
uint8 KEYPAD_getPressedKey(void)
{
	uint8 L_col , L_row ;

	/*	Always loop until the user press a key in the keypad when the user
	 *  Press the value save it and break the while 1
	 */
	while(1)
	{
		/* loop for columns */
		for(L_col = 0 ; L_col < KEYPAD_NUM_OF_COLUMNS ; L_col++)
		{
			/*
			 * Each time setup the direction for all keypad port as input pins,
			 * except this column will be output pin
			 */
			GPIO_setupPortDirection(KEYPAD_PORT_ID , PORT_INPUT);
			GPIO_setupPinDirection(KEYPAD_PORT_ID , KEYPAD_FIRST_COLUMN_PIN_ID + L_col ,PIN_OUTPUT);

			/*	In case of the MCU we use support internal PUR and you decide to
			 *  activate the keypad using internal PUR
			 */
			#if ( (THIS_MCU_SUPPORT_INTERNAL_PUR == TRUE ) && (SET_KEYPAD_USING_INTERNAL_PUR == TRUE) )
					/*	in case of internal pull up resistor we will loop on
					 *  them for activation
					 */
					for(L_row=0 ; L_row < KEYPAD_NUM_OF_ROWS ; L_row++)
					{
						GPIO_activate_intenalPUR_forPin(KEYPAD_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+L_row);
					}

					GPIO_writePin(KEYPAD_PORT_ID , KEYPAD_FIRST_COLUMN_PIN_ID + L_col ,LOGIC_LOW);
			#else
			/*	If the MCU doesn't support the Internal PUR option we will use External circuits */
					#if (KEYPAD_BUTTON_PRESSED == LOGIC_LOW)
						/*
						 * Column PORT value is set as low, so as soon as we change their DDR bit
						 * to 1 they become output with value LOW. In external pull up resistance
						 * we don't need pull up resistance setup.
						 */
						GPIO_writePin(KEYPAD_PORT_ID , KEYPAD_FIRST_COLUMN_PIN_ID + L_col ,LOGIC_LOW);
					#else
						/*
						 * In external pull down resistance we need to output logic high to the output column line.
						 * In external pull up resistance we don't need any port setup.
						 */
						GPIO_writePort(KEYPAD_PORT_ID , (1<<(KEYPAD_FIRST_COLUMN_PIN_ID+L_col)));
					#endif
			#endif

			/* loop for Rows and read them */
			for(L_row =0 ; L_row < KEYPAD_NUM_OF_ROWS ; L_row++)
			{
				/*	We will loop upon all the column with its corresponding pins if the user
				 *  press any key we will enter */
				if(  GPIO_readPin( KEYPAD_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+L_row ) == KEYPAD_BUTTON_PRESSED  )
				{
					/*	This while will handle the case where if i press the key and didn't
					 *  leave the key , without the loop the function will return the value
					 *  more than once and this not what we want so this while will make
					 *  function won't return a value until the user remove his finger
					 *  from the keypad
					 */
					while(  GPIO_readPin( KEYPAD_PORT_ID , KEYPAD_FIRST_ROW_PIN_ID+L_row ) == KEYPAD_BUTTON_PRESSED  );

					/*
					 * If the switch is pressed we pass the value of the switch to the function that return its corresponding symbol.
					 * and return the ASCII of this symbol.
					 */
					#if (KEYPAD_NUM_OF_COLUMNS == 3)
						return KEYPAD_4x3_adjustKeyNumber( (L_row*KEYPAD_NUM_OF_COLUMNS) + L_col + 1 );
					#elif (KEYPAD_NUM_OF_COLUMNS == 4)
						return KEYPAD_4x4_adjustKeyNumber( (L_row*KEYPAD_NUM_OF_COLUMNS) + L_col + 1);
					#endif
				}
			}
			/*
			#if (KEYPAD_BUTTON_PRESSED == LOGIC_HIGH)
			GPIO_writePin(KEYPAD_PORT_ID , KEYPAD_FIRST_COLUMN_PIN_ID + L_col ,LOGIC_LOW);
			#endif
			*/
		}
	}
	return 0;
}

/*******************************************************************************
 *                          Private Function Definition	                       *
 *******************************************************************************/

#if (KEYPAD_NUM_OF_COLUMNS == 3)
/*
 * Description :
 * This function update the value of keypad button pressed according to keypad
 * which is used in real life or in simulator , Here this is the values in
 * 4x3 Keypad in Proteus
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 a_keyNumber)
{
	uint8 L_keyValue = 0;

	switch(a_keyNumber)
	{
		case 10:
			L_keyValue = '*';  /* We return the ASCI of * as a value */
			break;

		case 11:
			L_keyValue = 0;
			break;

		case 12:
			L_keyValue = '#';  /* We return the ASCI of * as a value */
			break;

		default:
			L_keyValue = a_keyNumber;
			break;
	}

	return L_keyValue;
}

#elif (KEYPAD_NUM_OF_COLUMNS == 4)

/*
 * Description :
 * This function update the value of keypad button pressed according to keypad
 * which is used in real life or in simulator , Here this is the values in
 * 4x4 Keypad in Proteus
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 a_keyNumber)
{
	uint8 L_keyValue = 0;

	switch(a_keyNumber)
	{
		case 1:
			L_keyValue = 7;
			break;

		case 2:
			L_keyValue = 8;
			break;

		case 3:
			L_keyValue = 9;
			break;

		case 4:
			L_keyValue = '/'; /* We return the ASCI of / as a value */
			break;

		case 5:
			L_keyValue = 4;
			break;

		case 6:
			L_keyValue = 5;
			break;

		case 7:
			L_keyValue = 6;
			break;

		case 8:
			L_keyValue = '*'; /* We return the ASCI of * as a value */
			break;

		case 9:
			L_keyValue = 1;
			break;

		case 10:
			L_keyValue = 2;
			break;

		case 11:
			L_keyValue = 3;
			break;

		case 12:
			L_keyValue = '-';  /* We return the ASCI of - as a value */
			break;

		case 13:
			L_keyValue = 13;  /* this value represent ENTER */
			break;

		case 14:
			L_keyValue = 0;
			break;

		case 15:
			L_keyValue = '='; /* We return the ASCI of = as a value */
			break;

		case 16:
			L_keyValue = '+'; /* We return the ASCI of + as a value */
			break;

		default:
			/* we supposed to make a case for each value but this is for debugging
			 * in KEYPAD_getPressedKey to know if the function has a input parameter
			 *  value bigger than the range.
			 */
			L_keyValue = a_keyNumber;
			break;
	}

	return L_keyValue;

}


#endif
