/******************************************************************************
 *
 * File Name   : door_locker_system_HMI_MCU.c
 *
 * Description : Source file of Door Locker Security System project
 * 				 Human Interface MCU
 *
 *  Date       : 8/11/2021
 *
 * Author      : Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "door_locker_system_HMI_MCU.h"
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer.h"
#include <avr/io.h>

/*******************************************************************************
 *                      Private Global Variables Definitions                   *
 *******************************************************************************/

/*	Flags to Know that the Timer has finished */
static volatile uint8 g_timerHasFinishedCounting3seconds 	= FALSE;
static volatile uint8 g_timerHasFinishedCounting15seconds	= FALSE;
static volatile uint8 g_timerHasFinishedCounting60seconds	= FALSE;

/*	Global to count the number of Interrupts	*/
static volatile uint8 g_tick = 0;

/*	Global to count How many Mismatch Happens	*/
static volatile uint8 g_mismatch = 0;

/*******************************************************************************
 *                          	Main Function			                       *
 *******************************************************************************/


int main(void)
{
	char L_optionResult ; /* used to save the option selected in step 2 : '+','-' */
	uint8 L_stepStatus; /* Used to know the status to take the decision to reset or not*/

	/*	Enable the Global interrupt Flag */
	SREG |= (1<<7);

	/* Dynamic configurations of Drivers*/
	DynamicConfiguration_UART L_config_UART = {DISABLE_PARITY , _8_DATA_BIT , _1_STOP_BIT , 9600 };

	/*	Initialization of needed Modules	*/
	LCD_init();
	UART_init(&L_config_UART);


	/*	Super Loop	*/
	while(1)
	{
		/*********** STEP 1 ************/
		/* create Password */
		APP_CreatePassword_HMI_MCU();

		/*	Always Execute Step 2 until Resets happens  */
		do
		{
			/*********** STEP 2 ************/
			/*	Get the result form Option Menu	*/
			L_optionResult = APP_getTheResultFromOptionMenu();
			/*	Send the Option selected to control MCU when it is ready */
			while( UART_receiveData() != I_AM_READY);
			UART_sendData(L_optionResult);

			if(L_optionResult == '+') /*	User Choose to Open Door 	*/
			{
				/*********** STEP 3 ************/
				/*	Do all requirements when user Choose to Open Door */
				APP_optionOpenDoorIsSelected_HMI_MCU();

			}
			else if( L_optionResult == '-') /*	User Choose to Reset Password  */
			{
				/*********** STEP 4 ************/
				/*	Do all requirements when user Choose to Reset Password */
				APP_optionResetPasswordIsSelected_HMI_MCU(&L_stepStatus);

				if(L_stepStatus == RESET)
				{
					/* If the status is to reset so we break out of step 2 loop
					 * then go to Step 1 so to start form all over again.
					 * If not we will go to step 2
					 */
					break;
				}
			}

		}while(1);	/* Step 2 Loop we always loop Until Resets happens */

	}

	return 0;	/* End of Main function	*/
}

/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/

/*************** Step 1 functions *****************/
/*
 *  Description:
 * 	This function will ask the user to enter the password he want to create then
 * 	asks him another time to re enter the password and then send the two passwords
 * 	to CTRL MCU to take the decision either they match or not and we won't exit
 * 	this function until we create a password with match the reentered password
 */
void APP_CreatePassword_HMI_MCU(void)
{
	const char *L_stringToBeDisplayed ;
	PasswordStatus L_compareResult ;

	/*	This is the array where we will save the Password Created */
	uint8 L_password  [PASSWORD_SIZE + 1] = {0};

	/*	This is the array where we will save the Reentered Password  */
	uint8 L_repeadtedPassword[PASSWORD_SIZE + 1] = {0};

	do
	{
		/*	Create a Password  */
		L_stringToBeDisplayed = "Create The Pass:";
		APP_getPassword( L_stringToBeDisplayed, L_password);

		/*	Reenter the Password  */
		L_stringToBeDisplayed = "Re-Enter Pass:";
		APP_getPassword( L_stringToBeDisplayed, L_repeadtedPassword);

		/*	Send the Password to control MCU when it is ready */
		while( UART_receiveData() != I_AM_READY);
		UART_sendString(L_password);

		/*	Send the Rendered Password to control MCU when it is ready */
		while( UART_receiveData() != I_AM_READY);
		UART_sendString(L_repeadtedPassword);


		/*	Loop until Control MCU ready to give me the result of comparing
		 *  the password and repeated result.
		 */
		L_compareResult = UART_receiveData() ;

	}while(L_compareResult == PASSWORD_MISMASTCH); /* Loop until two passwords matches */

}

/*
 * Description:
 * This function will read 5 number from the Keypad which is password the function
 * won't return until the user enter ENTER key on keypad , it can only read 5
 * Number as password, More than the function won't read the values.
 * The function display the String which is input and then read the password.
 */
void APP_getPassword(const char *a_str , uint8 *a_password)
{
	uint8 i = 0 ,L_keypadValue = 0 ;;

	/*	Clear the screen first	*/
	LCD_clearScreen();

	/*	Display the Input string on LCD */
	LCD_displayStringAtRowColumn(0,0,a_str);

	/*	Move cursor to Line 2	*/
	LCD_moveCursor(1,0);

	/*	Loop and read the Password enter by user in keypad.
	 * 	The loop will loop until it take 5 integers from 0 to 9 any values
	 * 	other than that , it will continue to loop to get integer value.
	 */
	while( i < PASSWORD_SIZE)
	{
		L_keypadValue = KEYPAD_getPressedKey();

		/*	Take only values form 0 to 9	*/
		if( (L_keypadValue>= 0) && (L_keypadValue <= 9) )
		{
			a_password[i] = L_keypadValue ;

			/*	Each character entered display '*' */
			LCD_displayCharacter('*');

			i++;
		}
	}
	/*	This is a trick to convert the array to a string so that we can Send
	 *  this password using UART function [ UART_sendString() ] which need
	 *  String as a parameter
	 */
	a_password[i] = '\0';

	/*	we won't break out of the loop until the user press enter on keypad
	 *  and all the key values which is pressed after taking 5 password values
	 *  will be ignored.
	 *  Enter return a value 13 from keypad so thats why compare 12 with the variable.
	 */
	while( (L_keypadValue = KEYPAD_getPressedKey() ) != 13 );
}

/*
 * Description:
 * This function display the array which contain the password[5 numbers] at
 * specific column and row on the LCD.
 * All you need to supply is the Row and Column and the array to display.
 */
void APP_displayPasswordAtRowColumn(uint8 a_row , uint8 a_col ,const uint8* a_password)
{
	uint8 i = 0;

	/*	First move the Cursor to the required location	*/
	LCD_moveCursor(a_row , a_col);

	/*	Display the Password	*/
	for(i = 0 ; i < PASSWORD_SIZE ; i++)
	{
		LCD_displayNumber(a_password[i]);
	}
}

/*************** Step 2 functions *****************/

/*
 * Description:
 * we return the result of option Menu either it is '+' to open Door or it is '-'
 * to Reset Password.
 */
uint8 APP_getTheResultFromOptionMenu(void)
{
	uint8 L_option ;

	/*	Display the Main Options : */
	LCD_clearScreen();
	LCD_displayStringAtRowColumn(0,0,"  Main Options  ");
	LCD_displayStringAtRowColumn(1,0,"1)+ :Open Door");
	LCD_displayStringAtRowColumn(2,0,"2)- :Change Pass");

	/*	Loop until we get '+' or '-' otherwise stay in the loop */
	do
	{
		L_option = KEYPAD_getPressedKey();
	}while((L_option != '+') && (L_option != '-'));

	return L_option;
}

/*************** Step 3 functions *****************/
/*
 * Description:
 * This function do all the requirements needed when user select to open Door
 */
void APP_optionOpenDoorIsSelected_HMI_MCU(void)
{
	PasswordStatus L_verifyPasswordResult ;

	do
	{
		/*	See if the password written by user is Match or Mismatch */
		L_verifyPasswordResult = APP_verifyPassword_HMI_MCU();

		if( L_verifyPasswordResult == PASSWORD_MATCH )
		{
				/*	Do all the Processing needed to open The door  */
				APP_openDoorOptionProcessing_HMI_MCU();
		}
		else
		{
			/*********** STEP 5 ************/
			/* if Password was Mismatch give him another 2 Trials only */
			APP_passwordMismatchHandling_HMI_MCU();
		}

		/*	We loop if the Password entered is wrong , We give 3 Trials more than
		 *  An Alarm Goes ON
		 */
	}while( (L_verifyPasswordResult == PASSWORD_MISMASTCH) && (g_mismatch < MAX_NUM_OF_MISMATCH));

	/*	Reaching here means that it enters the password Right or he has consumed
	 *  Three trials and in both cases the counter is reseted to start again from
	 *  the start
	 */
	g_mismatch = 0;
}

/*
 * Description:
 * This function will :
 * 1) Display Door is Unlocking..  For 15 seconds
 * 2) Display Door is Hold         For 3  seconds
 * 3) Display Door is Unlocking..  For 15 seconds
 */
void APP_openDoorOptionProcessing_HMI_MCU(void)
{
	/*	Timer1 Dynamic configurations to count 3 , 15 seconds */

	/*	3 seconds, Only one Compare match is enough */
	DynamicConfiguration_TIMER L_timerConfig3sec = {TIMER1 , T1_CTC_MODE ,F_CPU_DIV_BY_1024,0, 23438};
	/*	15 seconds, Two Compare match is needed which mean two interrupts */
	DynamicConfiguration_TIMER L_timerConfig15sec = {TIMER1 , T1_CTC_MODE ,F_CPU_DIV_BY_1024,0, 58594};


	/*	Before Timer initialization we must clear the flag to know the effect of
	 *  Call back function
	 */
	g_timerHasFinishedCounting15seconds = FALSE ;
	/*	Set the Call back Function */
	TIMER_setCallBackFunction(TIMER1 , APP_timer1_15sec_CallBackFunction_HMI_MCU);
	/* (1) Display Door is Unlocking..  For 15 seconds */
	LCD_clearScreen();
	LCD_displayStringAtRowColumn(0,0,"    Unlocking   ");
	LCD_displayStringAtRowColumn(1,0,"    The Door... ");
	/*	Timer1 ON */
	TIMER_init(&L_timerConfig15sec);
	/*	Wait until 15 seconds passes */
	while(!g_timerHasFinishedCounting15seconds);



	/*	Before Timer initialization we must clear the flag to know the effect of
	 *  Call back function
	 */
	g_timerHasFinishedCounting3seconds = FALSE ;
	/*	Set the Call back Function */
	TIMER_setCallBackFunction(TIMER1 , APP_timer1_3sec_CallBackFunction_HMI_MCU);
	/* (2) Display Door is Hold         For 3  seconds */
	LCD_clearScreen();
	LCD_displayStringAtRowColumn(0,0,"    Holding    ");
	LCD_displayStringAtRowColumn(1,0,"    The Door...");
	/*	Timer1 ON */
	TIMER_init(&L_timerConfig3sec);
	/*	Wait until 3 seconds passes */
	while(!g_timerHasFinishedCounting3seconds);



	/*	Before Timer initialization we must clear the flag to know the effect of
	 *  Call back function
	 */
	g_timerHasFinishedCounting15seconds = FALSE ;
	/*	Set the Call back Function */
	TIMER_setCallBackFunction(TIMER1 , APP_timer1_15sec_CallBackFunction_HMI_MCU);
	/* 3) Display Door is Unlocking..  For 15 seconds */
	LCD_clearScreen();
	LCD_displayStringAtRowColumn(0,0,"    Locking     ");
	LCD_displayStringAtRowColumn(1,0,"    The Door... ");
	/*	Timer1 ON */
	TIMER_init(&L_timerConfig15sec);
	/*	Wait until 15 seconds passes */
	while(!g_timerHasFinishedCounting15seconds);
}

/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. when the timer is set
 * to count 3 seconds.
 */
void APP_timer1_3sec_CallBackFunction_HMI_MCU(void)
{
	g_timerHasFinishedCounting3seconds = TRUE;

	/*	Turn OFF Timer 1*/
	TIMER_deInit(TIMER1);
}
/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. used when the timer
 * is set to count 15 seconds.
 */
void APP_timer1_15sec_CallBackFunction_HMI_MCU(void)
{
	/*	Increment The Global which count the number of Interrupts */
	g_tick++;

	if(g_tick == NUMBER_OF_INTERRUPTS_TO_COUNT_15_SEC)
	{
		g_timerHasFinishedCounting15seconds = TRUE;

		/*	Turn OFF Timer 1*/
		TIMER_deInit(TIMER1);

		/*	Clear the number of Interrupts */
		g_tick = 0;
	}
}
/*
 * Description :
 * This function ask the user for the password and send it TO control MCU
 * to check it and the control MCU return the result either Match or Mismatch
 */
PasswordStatus APP_verifyPassword_HMI_MCU(void)
{
	PasswordStatus L_compareResult ;
	const char *L_stringToBeDisplayed ;
	/*	Array to save the password to Open the Door */
	uint8 L_passwordToOpenDoor [PASSWORD_SIZE + 1] = {0};

	/*	Ask to Enter the password so that the option chosen is made */
	L_stringToBeDisplayed = "Enter The Pass:";
	APP_getPassword( L_stringToBeDisplayed, L_passwordToOpenDoor);

	/*	Send the Password to control MCU when it is ready */
	while( UART_receiveData() != I_AM_READY);
	UART_sendString(L_passwordToOpenDoor);

	/*	Loop until Control MCU ready to give me the result of comparing
	 *  the password and repeated result.
	 */
	L_compareResult = UART_receiveData() ;

	return L_compareResult;
}

/*************** Step 4 functions *****************/
/*
 * Description:
 * This function do all the requirements needed when user select Reset Password
 */
void APP_optionResetPasswordIsSelected_HMI_MCU(uint8 *a_stepStatus)
{
	PasswordStatus L_verifyPasswordResult ;

	do
	{
		/*	See if the password written by user is Match or Mismatch */
		L_verifyPasswordResult = APP_verifyPassword_HMI_MCU();

		if( L_verifyPasswordResult == PASSWORD_MATCH )
		{
				/*	Return RESET value so that we can break out of the loop in main */
				*a_stepStatus = RESET;
		}
		else
		{
			/*********** STEP 5 ************/

			*a_stepStatus = NORESET; /*	No reset as Password Mismatch*/

			/* if Password was Mismatch give him another 2 Trials only */
			APP_passwordMismatchHandling_HMI_MCU();
		}

		/*	We loop if the Password entered is wrong , We give 3 Trials more than
		 *  An Alarm Goes ON
		 */
	}while( (L_verifyPasswordResult == PASSWORD_MISMASTCH) && (g_mismatch < MAX_NUM_OF_MISMATCH));

	/*	Reaching here means that it enters the password Right or he has consumed
	 *  Three trials and in both cases the counter is reseted to start again from
	 *  the start
	 */
	g_mismatch = 0;

}

/*************** Step 5 functions *****************/
/*
 * Description:
 * This function handles the case where the user enters Wrong password until
 * 3 trials in which it display Error MSG when entering 3 times wrong password
 * for 1 minute.
 */
void APP_passwordMismatchHandling_HMI_MCU(void)
{
	/*	60 seconds, 8 Compare match is needed which mean 8 interrupts */
	DynamicConfiguration_TIMER L_timerConfig60sec = {TIMER1 , T1_CTC_MODE ,F_CPU_DIV_BY_1024,0, 58594};

	g_mismatch++;

	/*	If the Wrong trials is equal to Max number of trial and Alarm is set ON */
	if(g_mismatch == MAX_NUM_OF_MISMATCH)
	{
		/*	Before Timer initialization we must clear the flag to know the effect of
		 *  Call back function
		 */
		g_timerHasFinishedCounting60seconds = FALSE ;
		/*	Set the Call back Function */
		TIMER_setCallBackFunction(TIMER1 , APP_timer1_60sec_CallBackFunction_HMI_MCU);
		/* Display EEROR MSG for 1 MIN */
		LCD_clearScreen();
		LCD_displayStringAtRowColumn(0,0,"  !!! ERROR !!! ");
		LCD_displayStringAtRowColumn(1,0,"  !!! Thief !!! ");
		/*	Timer1 ON */
		TIMER_init(&L_timerConfig60sec);
		/*	Wait until 60 seconds passes */
		while(!g_timerHasFinishedCounting60seconds);

	}
}

/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. used when the timer
 * is set to count 60 seconds.
 */
void APP_timer1_60sec_CallBackFunction_HMI_MCU(void)
{
	/*	Increment The Global which count the number of Interrupts */
	g_tick++;

	if(g_tick == NUMBER_OF_INTERRUPTS_TO_COUNT_60_SEC)
	{
		g_timerHasFinishedCounting60seconds = TRUE;

		/*	Turn OFF Timer 1*/
		TIMER_deInit(TIMER1);

		/*	Clear the number of Interrupts */
		g_tick = 0;
	}
}
