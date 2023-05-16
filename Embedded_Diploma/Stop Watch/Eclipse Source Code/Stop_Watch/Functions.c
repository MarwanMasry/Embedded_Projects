/*
 * Functions.c
 *
 *  Created on: Sep 21, 2021
 *      Author: marwan
 */

/*	Includes Needed	*/
#include "Global_variables.h"
#include <avr/delay.h>
#include <avr/io.h>

/*	Function Definition	*/

/*
 * This function is displaying all the numbers of the seven segment by
 *  using the Multiplexing method. In this method, at a time one 7-segment
 *  display is driven by the Micro-controller and the rest are OFF. It keeps
 *  switching the displays using transistors. Due to the persistence of vision,
 *   it appears as a normal display
 */
void Display_Stop_Watch(void)
{
	/*here we use insertion method -6 bit- in PORT A in which we only make one bit
	 * is zero in port A and other is zero
	 */
	PORTA = (PORTA & 0xC0) | ( (1<<counter_for_BJT) & 0x3F );
	/* here we use insertion we insert 4 bit in port c in which it is the
	 * number of the seven segment
	 */
	PORTC = (PORTC & 0xF0) | ( (stop_watch[counter_for_BJT]) & 0x0F );
	_delay_ms(5);

	counter_for_BJT++;

	if(counter_for_BJT == 6)
		counter_for_BJT = 0;
}

/*
 * This function is updating the stop watch always the Timer ISR is increasing
 * sec1 every second here we take care of the other numbers we will discuss
 * each condition bellow
 */

void Update_Stop_watch(void)
{
	/*	each 10 seconds counted by timer we increase sec2 where we complete
	 * 10 seconds then make sec1 = 0
	 */
	if(stop_watch[0]==10)
	{
		stop_watch[0]=0;
		stop_watch[1]++;
	}

	/*	each 60 seconds counted by timer we  increase min1 where we complete
	 *  60 seconds then make sec2 = 0
	 */
	if(stop_watch[1]==6 )
	{
		stop_watch[1]=0;
		stop_watch[2]++;
	}

	/*	each 10 minutes counted by timer we  increase min2 where we complete
	 *  10 minutes then make min1 = 0
	 */

	if(stop_watch[2]==10  )
	{
		stop_watch[2]=0;
		stop_watch[3]++;
	}


	/*	each 60 minutes counted by timer we  increase hour1 where we complete
	 *  1 hour then make min2 = 0
	 */

	if(stop_watch[3]==6)
	{
		stop_watch[3]=0;
		stop_watch[4]++;
	}


	/*	each 10 hours counted by timer we  increase hour2 where we complete
	 *  10 hour then make hour1 = 0
	 */
	if(stop_watch[4]==10)
	{
		stop_watch[4]=0;
		stop_watch[5]++;

		/*	we Stop the counter when reaching 99:59:59	*/
		if(stop_watch[5]==10)
		{
			/*	Turn off the Clock of the Timer so it stop Counting	*/
			TCCR1B &=  ~(1<<CS10) & ~(1<<CS12);
		}
	}



}
