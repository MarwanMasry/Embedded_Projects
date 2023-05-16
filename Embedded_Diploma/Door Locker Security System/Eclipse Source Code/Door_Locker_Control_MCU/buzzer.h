 /******************************************************************************
 *
 * Module: Buzzer Module
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the Buzzer driver
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                          Definition - Configurations                        *
 *******************************************************************************/
#define BUZZER_PORT_ID			PORTB_ID
#define BUZZER_PIN_ID			PIN7_ID

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/*
 * Description:
 * This function will initialize the buzzer by making the pin connected to it output
 */
void BUZZER_init(void);

/*
 * Description:
 * Turing on the buzzer by writing Logic High on the Buzzer Pin
 */
void BUZZER_ON(void);

/*
 * Description:
 * Turing on the buzzer by writing Logic Low on the Buzzer Pin
 */
void BUZZER_OFF(void);


#endif /* BUZZER_H_ */
