/******************************************************************************
 *
 * Module: ModuleTest
 *
 * File Name: Port_ModuleTest.c
 *
 * Description: Source file for the Port Test Cases.
 *
 * Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 
#include <assert.h>

#include "Gpt.h"
#include "Gpt_ModuleTest.h"
#include "tm4c123gh6pm_registers.h"
   
/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/
/* Call back function */
void Gpt_Notification_Systick(void)
{
  GPIO_PORTF_DATA_REG ^= (1<<1); /* Toggle the Red LED at PF1 */
}

/* Enable PF1 (RED LED) */
void Led_Red_Init(void)
{
    /* Enable clock for PORTF and allow time for clock to start */ 
    volatile unsigned long delay = 0;
    SYSCTL_REGCGC2_REG |= 0x00000020;
    delay = SYSCTL_REGCGC2_REG;
    GPIO_PORTF_AMSEL_REG &= ~(1<<1);      /* Disable Analog on PF1 */
    GPIO_PORTF_PCTL_REG  &= 0xFFFFFF0F;   /* Clear PMCx bits for PF1 to use it as GPIO pin */
    GPIO_PORTF_DIR_REG   |= (1<<1);       /* Configure PF1 as output pin */
    GPIO_PORTF_AFSEL_REG &= ~(1<<1);      /* Disable alternative function on PF1 */
    GPIO_PORTF_DEN_REG   |= (1<<1);       /* Enable Digital I/O on PF1 */
    GPIO_PORTF_DATA_REG  &= ~(1<<1);      /* Clear bit 1 in Data regsiter to turn off the led */
}

/* Test the Systick timer to operate on Continous Mode*/
void Gpt_TestCase1(void)
{
  Gpt_Init(&Gpt_Configuration1);
  
  Gpt_EnableNotification(GPT_CONFIG_SYSTICK_INDEX);
  
  Gpt_StartTimer(GPT_CONFIG_SYSTICK_INDEX, 7999999 + 1); 
  
  while(1)
  {
    Wait_For_Interrupt();
  }
}
   
/* Test the Systick timer to operate on one shot Mode*/
void Gpt_TestCase2(void)
{
  Gpt_Init(&Gpt_Configuration2);
  
  Gpt_EnableNotification(GPT_CONFIG_SYSTICK_INDEX);
  
  Gpt_StartTimer(GPT_CONFIG_SYSTICK_INDEX, 7999999 + 1); 
  
  while(1)
  {
    Wait_For_Interrupt();
  }
}    