/******************************************************************************
 *
 * File Name   : door_locker_system_CTRL_MCU.h
 *
 * Description : Header file of Door Locker Security System project
 * 				 Control Interface MCU
 *
 *  Date       : 8/11/2021
 *
 * Author      : Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

#ifndef DOOR_LOCKER_SYSTEM_CTRL_MCU_H_
#define DOOR_LOCKER_SYSTEM_CTRL_MCU_H_

/*******************************************************************************
*                              Includes Needed                                *
*******************************************************************************/
#include "std_types.h"

/*******************************************************************************
*                         Definition - Configuration                          *
*******************************************************************************/
#define	PASSWORD_SIZE								5U

#define NUMBER_OF_INTERRUPTS_TO_COUNT_3_SEC 		1
#define NUMBER_OF_INTERRUPTS_TO_COUNT_15_SEC		2
#define NUMBER_OF_INTERRUPTS_TO_COUNT_60_SEC		8

#define ADDRESS_OF_PASSWORD_IN_EEPROM			    0x0311U

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
 *  This function take the password and the reentered password which written in
 *  HMI MCU and Compare them , If they match then the control MCU will send to
 *  HMI MCU that password matches and it is created and saved in EEPROM , if the
 *  password doesn't match it also tell HMI MCU that password was mismatch and
 *  will loop until a match happens.
 */

void APP_CreatePassword_CTRL_MCU(void);

/*
 * Description :
 * This function compare the two Passwords , and return the result.
 */
PasswordStatus APP_compareTwoPasswords(uint8 *a_password , uint8 *a_repeatedPassword);

/*************** Step 3 functions *****************/
/*
 * Description:
 * This function do all the requirements needed when user select to open Door
 */
void APP_optionOpenDoorIsSelected_CTRL_MCU(void);
/*
 * Description:
 * This function will :
 * 1) Rotate DC Motor Clockwise            For 15 seconds
 * 2) Hold DC Motor                        For 3  seconds
 * 3) Rotate DC Motor Anti-Clockwise       For 15 seconds
 */
void APP_openDoorOptionProcessing_CTRL_MCU(void);

/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. when timer is set to
 * count 3 seconds.
 */
void APP_timer1_3sec_CallBackFunction_CTRL_MCU(void);
/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. used when the timer
 * is set to count 15 seconds.
 */
void APP_timer1_15sec_CallBackFunction_CTRL_MCU(void);


/*************** Step 4 functions *****************/
/*
 * Description:
 * This function do all the requirements needed when user select Reset Password
 */
void APP_optionResetPasswordIsSelected_CTRL_MCU(uint8 *a_stepStatus);

/*************** Step 5 functions *****************/
/*
 * Description:
 * This function handles the case where the user enters Wrong password until
 * 3 trialsin which it turn on the Buzzer for 1 minute
 */
void APP_passwordMismatchHandling_CTRL_MCU(void);

/*
 * Description :
 * This function is Called when Timer1 trigger interrupt. used when the timer
 * is set to count 60 seconds.
 */
void APP_timer1_60sec_CallBackFunction_CTRL_MCU(void);


 #endif /* DOOR_LOCKER_SYSTEM_CTRL_MCU_H_ */
