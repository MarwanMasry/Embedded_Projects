/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.c
 *
 * Description: Source file for Led Module.
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 
#include "Dio.h"
#include "Led.h"

/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/
/* Description: Set the LED state to ON */
void LED_setOn(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_ON);  /* LED ON */
}

/* Description: Set the LED state to OFF */
void LED_setOff(void)
{
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,LED_OFF); /* LED OFF */
}

/* Description: Refresh the LED state */
void LED_refreshOutput(void)
{
    Dio_LevelType state = Dio_ReadChannel(DioConf_LED1_CHANNEL_ID_INDEX);
    Dio_WriteChannel(DioConf_LED1_CHANNEL_ID_INDEX,state); /* re-write the same value */
}

/*Description: Toggle the LED state */
void LED_toggle(void)
{
    Dio_LevelType state = Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);
}
