/*
 * Main.c
 *
 *  Created on: Sep 20, 2021
 *      Author: marwan
 */


/*	Includes Needed	*/
#include <avr/io.h>
#include "Global_variables.h"
#include "Functions.h"
#include "Timer1_External_Interrupts_IO.h"


/*	Main	Funciton	*/
int main (void)
{
	/* Enabling Global interrupts flag	*/
	SREG |= (1<<7);

	/*	Enable Port C and A for interfacing with 6 SSDs	*/
	PORTC_PORTA_Init();

	/*	Enable Timer to count 1 sec	*/
	Timer1_Init();

	/*	Enabling all theree External function for stop watch features stop clear resume	*/
	INT0_Init();
	INT1_Init();
	INT2_Init();

	while(1)
	{
		/*All we do in Main function is displaying the Numbers and updating them	*/

		Display_Stop_Watch();

		Update_Stop_watch();
	}

	return 0;
}

