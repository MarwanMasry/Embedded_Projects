/******************************************************************************
 *
 * File Name   : door_locker_system_HMI_MCU.h
 *
 * Description : Header file of Door Locker Security System project
 * 				 Human Interface MCU
 *
 *  Date       : 8/11/2021
 *
 * Author      : Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

#ifndef DOOR_LOCKER_SYSTEM_HMI_MCU_H_
#define DOOR_LOCKER_SYSTEM_HMI_MCU_H_


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                         Definition - Configuration                          *
 *******************************************************************************/
#define	PASSWORD_SIZE								5

#define NUMBER_OF_INTERRUPTS_TO_COUNT_3_SEC 		1
#define NUMBER_OF_INTERRUPTS_TO_COUNT_15_SEC		2
#define NUMBER_OF_INTERRUPTS_TO_COUNT_60_SEC		8

#define MAX_NUM_OF_MISMATCH							3

/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
/*
 * Description :
 * This enumerations is used in comparing the result of two Passwords
 */
typedef enum
{
	PASSWORD_MATCH , PASSWORD_MISMASTCH
}PasswordStatus;

/*
 * Description :
 * This enumerations is to know if Want to Reset the program and start form all
 * over again.
 */
typedef enum
{
	RESET , NORESET
}StepStatus;

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*************** Step 1 functions *****************/
/*
 *  Description:
 * 	This function will ask the user to enter the password he want to create then
 * 	asks him another time to re enter the password and then send the two passwords
 * 	to CTRL MCU to take the decision either they match or not and we won't exit
 * 	this function until we create a password with match the reentered password
 */
void APP_CreatePassword_HMI_MCU(void);

/*
 * Description:
 * This function will read 5 number from the Keypad which is password the function
 * won't return until the user enter ENTER key on keypad , it can only read 5
 * Number as password, More than the function won't read the values.
 * The function display the String which is input and then read the password.
 */
void APP_getPassword(const char *a_str , uint8 *a_password);

/*
 * Description:
 * This function display the array which contain the password[5 numbers] at
 * specific column and row on the LCD.
 * All you need to supply is the Row and Column and the array to display.
 */
void APP_displayPasswordAtRowColumn(uint8 a_row , uint8 a_col ,const uint8* a_password);

/*************** Step 2 functions *****************/
/*
 * Description:
 * we return the result of option Menu either it is '+' to open Door or it is '-'
 * to Reset Password.
 */
uint8 APP_getTheResultFromOptionMenu(void);

/*************** Step 3 functions *****************/
/*
 * Description:
 * This function do all the requirements needed when user select to open Door
 */
void APP_optionOpenDoorIsSelected_HMI_MCU(void);

/*
 * Description:
 * This function will :
 * 1) Display Door is Unlocking..  For 15 seconds
 * 2) Display Door is Hold         For 3  seconds
 * 3) Display Door is Unlocking..  For 15 seconds
 */
void APP_openDoorOptionProcessing_HMI_MCU(void);

/*
 * Description :
 * This function ask the user for the password and send it TO control MCU
 * to check it and the control MCU return the result either Match or Mismatch
 */
PasswordStatus APP_verifyPassword_HMI_MCU(void);

/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. when the timer is set
 * to count 3 seconds.
 */
void APP_timer1_3sec_CallBackFunction_HMI_MCU(void);
/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. used when the timer
 * is set to count 15 seconds.
 */
void APP_timer1_15sec_CallBackFunction_HMI_MCU(void);

/*************** Step 4 functions *****************/
/*
 * Description:
 * This function do all the requirements needed when user select Reset Password
 */
void APP_optionResetPasswordIsSelected_HMI_MCU(uint8 *a_stepStatus);

/*************** Step 5 functions *****************/
/*
 * Description:
 * This function handles the case where the user enters Wrong password until
 * 3 trials in which it display Error MSG when entering 3 times wrong password
 * for 1 minute.
 */
void APP_passwordMismatchHandling_HMI_MCU(void);

/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. used when the timer
 * is set to count 60 seconds.
 */
void APP_timer1_60sec_CallBackFunction_HMI_MCU(void);


#endif /* DOOR_LOCKER_SYSTEM_HMI_MCU_H_ */
