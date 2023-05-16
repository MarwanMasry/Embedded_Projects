 /******************************************************************************
 *
 * Module: Buzzer Module
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "gpio.h"
#include "buzzer.h"

/*******************************************************************************
 *                          Public Function Definition	                       *
 *******************************************************************************/
/*
 * Description:
 * This function will initialize the buzzer by making the pin connected to it output
 */
void BUZZER_init(void)
{
	/*	Set the buzzer pin as output pin */
	GPIO_setupPinDirection(BUZZER_PORT_ID ,BUZZER_PIN_ID ,PIN_OUTPUT);

	/*	Turn it OFF at beginning	*/
	GPIO_writePin(BUZZER_PORT_ID ,BUZZER_PIN_ID ,LOGIC_LOW);
}

/*
 * Description:
 * Turing on the buzzer by writing Logic High on the Buzzer Pin
 */
void BUZZER_ON(void)
{
	GPIO_writePin(BUZZER_PORT_ID ,BUZZER_PIN_ID ,LOGIC_HIGH);
}

/*
 * Description:
 * Turing on the buzzer by writing Logic Low on the Buzzer Pin
 */
void BUZZER_OFF(void)
{
	GPIO_writePin(BUZZER_PORT_ID ,BUZZER_PIN_ID ,LOGIC_LOW);
}
