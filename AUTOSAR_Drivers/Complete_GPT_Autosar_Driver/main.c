/*
 ============================================================================
 Name        : main.c
 Author      : Marwan Abdelhakim Elmasry
 Description : Test Det Driver.
 Date        : 24/4/2022
 ============================================================================
 */

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 
#include "Gpt.h"
#include "Gpt_ModuleTest.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                              Main Function                                  *
 *******************************************************************************/ 
int main(void)
{
   
    Led_Red_Init();
  
    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();
    
    /* Assign priority level 3 to the SysTick Interrupt */
    NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) \
                | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
    
    /* Test case 1 for GPT Driver */
    Gpt_TestCase1();
    
    /* Test case 2 for GPT Driver */
    /*Gpt_TestCase2();*/
    
  return 0;
}
