/*
 * Global_variables.c
 *
 *  Created on: Sep 21, 2021
 *      Author: marwan
 */

/*	This counter is used in Display function where it only set one BJT to 1
 * 	and and other BJT is zeros according to this counter of counter is 0
 * 	so BJT of sec1 is on other is off  , if it is 1 so BJT of sec2 is on and
 * 	other is off ,.....
 */
unsigned char counter_for_BJT = 0;


/*	This array has 6 variables in which it is the 6 seven segment display
 *  hour2	hour1	min2	min1	sec2	sec1
 *  [5]		[4]		[3]		[2]		[1]		[0]
 */
unsigned char stop_watch[6] = {0} ;



