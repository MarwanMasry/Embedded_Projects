/*
 ============================================================================
 Name        : app.c
 Author      : Marwan Abdelhakim Elmasry
 Description : Fan Controller System
 Date        : 10/10/2021
 ============================================================================
 */

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "adc.h"
#include "lcd.h"
#include "dc_motor.h"
#include "lm35.h"

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/*
 * Description:
 * This function will take the temperature and the flag status of the fan
 * and according to the temperature the speed and the rotation of Fan is calculated
 * speed <  30   : Fan OFF  , speed : 0%
 * speed >= 30   : Fan ON   , speed : 25%
 * speed >= 60   : Fan ON   , speed : 50%
 * speed >= 90   : Fan ON   , speed : 75%
 * speed >= 120  : Fan ON   , speed : 100%
 */
void APP_fanMotorProcessing(sint16 *a_temp_Ptr , uint8 *a_fanFlag);

/*
 * Description:
 * This function display Fan is ON or Fan is OFF in the LCD according to the
 * input status
 */
void APP_displayFanStatus(uint8 *a_fanFlag);

/*
 * Description:
 * This function Display the sensed temperature by LM35 in the LCD
 */
void APP_displayLM35Temperature(sint16 *a_temp_Ptr);

/*******************************************************************************
 *                          	Main Function			                       *
 *******************************************************************************/
int main (void)
{
	/*	The Temperature sensed by LM35	*/
	sint16 L_temperature = 0 ;
	/*	Flag to know if the fan is on or off	*/
	uint8 L_fanIsOn = FALSE;

	/*	Dynamic configuration for ADC driver	*/
	DynamicConfiguration_ADC L_config = {F_CPU_DIV_BY_8 ,INTERNAL_2560_MILLI_VOLT};

	/*	Initialization functions of the Modules */
	LCD_init();
	DC_MOTOR_init();
	ADC_init(&L_config);

	/*	Super Loop	*/
	while(1)
	{
		/*	Configure the fan speed,status according to temperature	*/
		APP_fanMotorProcessing(&L_temperature , &L_fanIsOn);

		/*	Display on LCD the status of fan	*/
		APP_displayFanStatus(&L_fanIsOn);

		/*	Display the LM35 temperature on LCD	*/
		APP_displayLM35Temperature(&L_temperature);
	}

	return 0;	/*	End of main	  */
}

/*******************************************************************************
 *                          Public Function Definition	                       *
 *******************************************************************************/

/*
 * Description:
 * This function will take the temperature and the flag status of the fan
 * and according to the temperature the speed and the rotation of Fan is calculated
 * speed <  30   : Fan OFF  , speed : 0%
 * speed >= 30   : Fan ON   , speed : 25%
 * speed >= 60   : Fan ON   , speed : 50%
 * speed >= 90   : Fan ON   , speed : 75%
 * speed >= 120  : Fan ON   , speed : 100%
 */
void APP_fanMotorProcessing(sint16 *a_temp_Ptr , uint8 *a_fanFlag)
{
	/*	Always read the Temperature of the sensor	*/
		*a_temp_Ptr = LM35_getTemperature();


		if( *a_temp_Ptr < 30)
		{
			/*	If the temperature is less than 30C turn off the fan	*/
			DC_MOTOR_setMotorState(OFF ,0);
			*a_fanFlag = FALSE ;
		}
		else if(*a_temp_Ptr >= 120)
		{
			/*	If the temperature is greater than or equal 120C turn on
			 * the fan with 100% of its maximum speed
			 */
			DC_MOTOR_setMotorState(ROTATE_CLOCKWISE , 100);
			*a_fanFlag = TRUE;
		}
		else if( *a_temp_Ptr >= 90)
		{
			/*	If the temperature is greater than or equal 90C turn on
			 *  the fan with 75% of its maximum speed
			 */
			DC_MOTOR_setMotorState(ROTATE_CLOCKWISE , 75);
			*a_fanFlag = TRUE;
		}
		else if(*a_temp_Ptr >= 60)
		{
			/*	If the temperature is greater than or equal 60C turn on
			 *  the fan with 50% of its maximum speed
			 */
			DC_MOTOR_setMotorState(ROTATE_CLOCKWISE , 50);
			*a_fanFlag = TRUE;
		}
		else if(*a_temp_Ptr >= 30)
		{
			/*	If the temperature is greater than or equal 30C turn on
			 * the fan with 25% of its maximum speed
			 */
			DC_MOTOR_setMotorState(ROTATE_CLOCKWISE , 25);
			*a_fanFlag = TRUE;
		}

}

/*
 * Description:
 * This function display Fan is ON or Fan is OFF in the LCD according to the
 * input status
 */

void APP_displayFanStatus(uint8 *a_fanFlag)
{
	/*	Display the state of the Fan of the LCD	according to state flag of the fan	*/
	if(*a_fanFlag)
	{
		LCD_displayStringAtRowColumn(0,3,"Fan is ON ");
	}
	else
	{
		LCD_displayStringAtRowColumn(0,3,"Fan is OFF");
	}

}

/*
 * Description:
 * This function Display the sensed temperature by LM35 in the LCD
 */
void APP_displayLM35Temperature(sint16 *a_temp_Ptr)
{

	/*	Always display the temperature which is measured by LM35 in the screen	*/
	LCD_displayStringAtRowColumn(1,3,"Temp = ");
	LCD_displayNumber(*a_temp_Ptr);
	LCD_displayString(" C  ");
}
