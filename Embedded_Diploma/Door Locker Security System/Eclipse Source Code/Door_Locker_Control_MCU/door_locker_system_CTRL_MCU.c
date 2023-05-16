/******************************************************************************
 *
 * File Name   : door_locker_system_CTRL_MCU.c
 *
 * Description : Source file of Door Locker Security System project
 * 				 Control Interface MCU
 *
 *  Date       : 8/11/2021
 *
 * Author      : Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "door_locker_system_CTRL_MCU.h"
#include "uart.h"
#include "timer.h"
#include "external_eeprom.h"
#include "twi.h"
#include "lcd.h"
#include <avr/delay.h>
#include "dc_motor.h"
#include <avr/io.h>
#include "buzzer.h"

/*******************************************************************************
 *                      Private Global Variables Definitions                   *
 *******************************************************************************/

/*	This is the array where we will the Password from EEPROM */
static volatile uint8 g_readPasswordFromEEPROM[PASSWORD_SIZE] = {0};

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
	char L_optionResult;  /* used to save the option selected in step 2 : '+','-' */
	uint8 L_stepStatus;	/* Used to know the status to take the decision to reset or not*/

	/*	Enable the Global interrupt Flag */
	SREG |= (1<<7);

	/* Dynamic configurations of Drivers*/
	DynamicConfiguration_UART L_config_UART = {DISABLE_PARITY , _8_DATA_BIT , _1_STOP_BIT , 9600 };
	DynamicConfiguration_TWI  L_config_TWI = {400000,100};  /* Bit rate 400 KHZ , MCU address = 100*/

	/*	Initialization of needed Modules	*/
	UART_init(&L_config_UART);
	TWI_init(&L_config_TWI);
	LCD_init();
	DC_MOTOR_init();
	BUZZER_init();


	/*	Super Loop	*/
	while(1)
	{
		/*********** STEP 1 ************/
		/* create Password 	*/
		APP_CreatePassword_CTRL_MCU();

		/* Store the Password Stored in EEPROM in global Variable as it will be
		 * used Multiple times
		 */
		EXTERNAL_EEPROM_readArrayOfBytes(ADDRESS_OF_PASSWORD_IN_EEPROM, g_readPasswordFromEEPROM, PASSWORD_SIZE);

		/*	Always Execute Step 2 until Resets happens  */
		do
		{
			/*********** STEP 2 ************/
			/*	Control MCU is now ready to receive the option selected at HMI_MCU  */
			UART_sendData(I_AM_READY);
			L_optionResult = UART_receiveData();


			if(L_optionResult == '+') /*	User Choose to Open Door 	*/
			{
				/*********** STEP 3 ************/
				/*	Do all requirements when user Choose to Open Door */
				APP_optionOpenDoorIsSelected_CTRL_MCU();

			}
			else if( L_optionResult == '-') /*	User Choose to Reset Password  */
			{
				/*********** STEP 4 ************/
				/*	Do all requirements when user Choose to Reset Password */
				APP_optionResetPasswordIsSelected_CTRL_MCU(&L_stepStatus);
				if(L_stepStatus == RESET)
				{
					/* If the status is to reset so we break out of step 2 loop
					 * then go to Step 1 so to start form all over again.
					 * If not we will go to step 2
					 */
					break;
				}
			}

		}while(1); /* Step 2 Loop we always loop Until Resets happens */
	}

	return 0;	/* End of Main function	*/
}

/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/

/*************** Step 1 functions *****************/
/*
 *  Description:
 *  This function take the password and the reentered password which written in
 *  HMI MCU and Compare them , If they match then the control MCU will send to
 *  HMI MCU that password matches and it is created and saved in EEPROM , if the
 *  password doesn't match it also tell HMI MCU that password was mismatch and
 *  will loop until a match happens.
 */
void APP_CreatePassword_CTRL_MCU(void)
{
	PasswordStatus L_compareResult ;

	/*	This is the array where we will save the Password Created */
	uint8 L_password  [PASSWORD_SIZE + 1] = {0};

	/*	This is the array where we will save the Reentered Password  */
	uint8 L_repeadtedPassword[PASSWORD_SIZE + 1] = {0};

	do
	{
		/*	Tell HMI_MCU that CTRL_MCU is ready to receive the Password Created */
		UART_sendData(I_AM_READY);
		UART_receiveString(L_password);


		/*	Tell HMI_MCU that CTRL_MCU is ready to receive the Reentered Password */
		UART_sendData(I_AM_READY);
		UART_receiveString(L_repeadtedPassword);


		/*	Compare Two Passwords */
		L_compareResult = APP_compareTwoPasswords(L_password ,L_repeadtedPassword) ;

		if( L_compareResult == PASSWORD_MATCH )
		{
			/*	If they match Then save The password inside External EEPROM */
			EXTERNAL_EEPROM_writeArrayOfBytes(ADDRESS_OF_PASSWORD_IN_EEPROM, L_password, PASSWORD_SIZE);
			_delay_ms(10);

			/*	Tell HMI_MCU that the Compare Result is Match */
			UART_sendData(PASSWORD_MATCH);
		}
		else
		{
			/*	Tell HMI_MCU that the Compare Result is Mismatch */
			UART_sendData(PASSWORD_MISMASTCH);
		}

		/*	If the compare result was mismatch then we will start from the
		 *  beginning , It will breaks only if the result was Match
		 */
	}while( L_compareResult == PASSWORD_MISMASTCH);

}

/*
 * Description :
 * This function compare the two Passwords , and return the result.
 */
PasswordStatus APP_compareTwoPasswords(uint8 *a_password , uint8 *a_repeatedPassword)
{
	uint8 i ;

	/*	Loop with password array and compare the two passwords */
	for(i = 0 ; i < PASSWORD_SIZE ;i++)
	{
		/*	If one number is not the same so Password Mismatch */
		if( a_password[i]  != a_repeatedPassword[i])
		{
			return PASSWORD_MISMASTCH;
		}
	}

	/*	reaching here means that the two Passwords matched */
	return PASSWORD_MATCH;
}

/*************** Step 3 functions *****************/
/*
 * Description:
 * This function do all the requirements needed when user select to open Door
 */
void APP_optionOpenDoorIsSelected_CTRL_MCU(void)
{
	PasswordStatus L_compareResult ;

	do
	{
		uint8 L_passwordTobeChecked [PASSWORD_SIZE + 1] = {0};

		/*	Tell HMI_MCU that CTRL_MCU is ready to receive the Password to Check
		 *  if it is right or wrong
		 */
		UART_sendData(I_AM_READY);
		UART_receiveString(L_passwordTobeChecked);

		/*	Compare Two Passwords */
		L_compareResult = APP_compareTwoPasswords(L_passwordTobeChecked , g_readPasswordFromEEPROM);

		if( L_compareResult == PASSWORD_MATCH )
		{
			/*	Tell HMI_MCU that the Compare Result is Match */
			UART_sendData(PASSWORD_MATCH);

			APP_openDoorOptionProcessing_CTRL_MCU();
		}
		else
		{
			/*	Tell HMI_MCU that the Compare Result is Mismatch */
			UART_sendData(PASSWORD_MISMASTCH);

			/* if Password was Mismatch give him another 2 Trials only */
			APP_passwordMismatchHandling_CTRL_MCU();
		}

	/*	We loop if the Password entered is wrong , We give 3 Trials more than
	*  An Alarm Goes ON
	*/
	}while( (L_compareResult == PASSWORD_MISMASTCH) && (g_mismatch < MAX_NUM_OF_MISMATCH));

	/*	Reaching here means that it enters the password Right or he has consumed
	 *  Three trials and in both cases the counter is reseted to start again from
	 *  the start
	 */
	g_mismatch = 0;
}


/*
 * Description:
 * This function will :
 * 1) Rotate DC Motor Clockwise            For 15 seconds
 * 2) Hold DC Motor                        For 3  seconds
 * 3) Rotate DC Motor Anti-Clockwise       For 15 seconds
 */
void APP_openDoorOptionProcessing_CTRL_MCU(void)
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
	TIMER_setCallBackFunction(TIMER1 , APP_timer1_15sec_CallBackFunction_CTRL_MCU);
	/* (1) Rotate DC Motor Clockwise  For 15 seconds */
	DC_MOTOR_setMotorState(ROTATE_CLOCKWISE , 100);
	/*	Timer1 ON */
	TIMER_init(&L_timerConfig15sec);
	/*	Wait until 15 seconds passes */
	while(!g_timerHasFinishedCounting15seconds);



	/*	Before Timer initialization we must clear the flag to know the effect of
	 *  Call back function
	 */
	g_timerHasFinishedCounting3seconds = FALSE ;
	/*	Set the Call back Function */
	TIMER_setCallBackFunction(TIMER1 , APP_timer1_3sec_CallBackFunction_CTRL_MCU);
	/* (2) Hold DC Motor    For 3  seconds */
	DC_MOTOR_setMotorState(OFF , 0);
	/*	Timer1 ON */
	TIMER_init(&L_timerConfig3sec);
	/*	Wait until 3 seconds passes */
	while(!g_timerHasFinishedCounting3seconds);



	/*	Before Timer initialization we must clear the flag to know the effect of
	 *  Call back function
	 */
	g_timerHasFinishedCounting15seconds = FALSE ;
	/*	Set the Call back Function */
	TIMER_setCallBackFunction(TIMER1 , APP_timer1_15sec_CallBackFunction_CTRL_MCU);
	/* (3) Rotate DC Motor Anti-Clockwise     For 15 seconds */
	DC_MOTOR_setMotorState(ROTATE_ANTICLOCKWISE , 100);
	/*	Timer1 ON */
	TIMER_init(&L_timerConfig15sec);
	/*	Wait until 15 seconds passes */
	while(!g_timerHasFinishedCounting15seconds);

}

/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. when timer is set to
 * count 3 seconds.
 */
void APP_timer1_3sec_CallBackFunction_CTRL_MCU(void)
{
	g_timerHasFinishedCounting3seconds = TRUE;

	/*	Turn OFF Timer 1*/
	TIMER_deInit(TIMER1);

	/*	Turn OFF Motor */
	DC_MOTOR_setMotorState(OFF,0);
}
/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. used when the timer
 * is set to count 15 seconds.
 */
void APP_timer1_15sec_CallBackFunction_CTRL_MCU(void)
{
	/*	Increment The Global which count the number of Interrupts */
	g_tick++;

	if(g_tick == NUMBER_OF_INTERRUPTS_TO_COUNT_15_SEC)
	{
		g_timerHasFinishedCounting15seconds = TRUE;

		/*	Turn OFF Timer 1*/
		TIMER_deInit(TIMER1);
		/*	Turn OFF Motor */
		DC_MOTOR_setMotorState(OFF,0);
		/*	Clear the number of Interrupts */
		g_tick = 0;
	}

}


/*************** Step 4 functions *****************/
/*
 * Description:
 * This function do all the requirements needed when user select Reset Password
 */
void APP_optionResetPasswordIsSelected_CTRL_MCU(uint8 *a_stepStatus)
{
	PasswordStatus L_compareResult ;

	do
	{
		uint8 L_passwordTobeChecked [PASSWORD_SIZE + 1] = {0};

		/*	Tell HMI_MCU that CTRL_MCU is ready to receive the Password to Check
		 *  if it is right or wrong
		 */
		UART_sendData(I_AM_READY);
		UART_receiveString(L_passwordTobeChecked);

		/*	Compare Two Passwords */
		L_compareResult = APP_compareTwoPasswords(L_passwordTobeChecked , g_readPasswordFromEEPROM);

		if( L_compareResult == PASSWORD_MATCH )
		{
			/*	Tell HMI_MCU that the Compare Result is Match */
			UART_sendData(PASSWORD_MATCH);

			/*	Return RESET value so that we can break out of the loop in main */
			*a_stepStatus = RESET;
		}
		else
		{
			/*	Tell HMI_MCU that the Compare Result is Mismatch */
			UART_sendData(PASSWORD_MISMASTCH);

			*a_stepStatus = NORESET; /*	No reset as Password Mismatch*/

			/* if Password was Mismatch give him another 2 Trials only */
			APP_passwordMismatchHandling_CTRL_MCU();
		}

	/*	We loop if the Password entered is wrong , We give 3 Trials more than
	*  An Alarm Goes ON
	*/
	}while( (L_compareResult == PASSWORD_MISMASTCH) && (g_mismatch < MAX_NUM_OF_MISMATCH));

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
 * 3 trials in which it turn on the Buzzer for 1 minute
 */
void APP_passwordMismatchHandling_CTRL_MCU(void)
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
		TIMER_setCallBackFunction(TIMER1 , APP_timer1_60sec_CallBackFunction_CTRL_MCU);
		/* Turn Alarm ON for 1 MIN */
		BUZZER_ON();
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
void APP_timer1_60sec_CallBackFunction_CTRL_MCU(void)
{
	/*	Increment The Global which count the number of Interrupts */
	g_tick++;

	if(g_tick == NUMBER_OF_INTERRUPTS_TO_COUNT_60_SEC)
	{
		g_timerHasFinishedCounting60seconds = TRUE;

		/*	Turn OFF Timer 1*/
		TIMER_deInit(TIMER1);

		/*	Turn OFF Buzzer */
		BUZZER_OFF();

		/*	Clear the number of Interrupts */
		g_tick = 0;
	}

}
