/*
 ============================================================================
 Name        : app.c
 Author      : Marwan Abdelhakim Elmasry
 Description : Measuring Distance Using Ultrasonic Sensor
 Date        : 20/10/2021
 ============================================================================
 */

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h>
#include <avr/delay.h>

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/*
 * Description:
 * This function Display The distance sensed by the Ultrasonic sensor.
 */
void APP_displayDistance(uint16 *a_distance_Ptr);

/*******************************************************************************
 *                          	Main Function			                       *
 *******************************************************************************/
int main (void)
{
	/*	The Distance sensed by ultrasonic	*/
	uint16 L_distance = 0 ;

	/*	Enable the Global Interrupt bit	*/
	SREG |= (1<<7);

	/*	Initialization functions of the Modules */
	LCD_init();
	Ultrasonic_init();

	/*	Super Loop	*/
	while(1)
	{
		/*	Read the distance read by the Ultrasonic sensor	*/
		L_distance = Ultrasonic_readDistance();

		/*	Display on LCD the Distance Sensed by Ultrasonic	*/
		APP_displayDistance(&L_distance);

		/*	We use the sensor to measure distance  multiple times BUT the time
		 *  between each measure Must be at least 50 ms to read values correctly
		 *  The best practice is 60 ms
		 */
		_delay_ms(60);

	}

	return 0;	/*	End of main	  */
}

/*******************************************************************************
 *                          Public Function Definition	                       *
 *******************************************************************************/

/*
 * Description:
 * This function Display The distance sensed by the Ultrasonic sensor.
 */
void APP_displayDistance(uint16 *a_distance_Ptr)
{

	/*	Always display the Distance in the screen	*/
	LCD_displayStringAtRowColumn(0,0,"Ultrasonic  Test");
	LCD_displayStringAtRowColumn(2,0,"Distance  Sensed");
	LCD_displayStringAtRowColumn(3,0,"is : ");
	LCD_displayNumber(*a_distance_Ptr);
	LCD_displayString(" CM  ");
}
