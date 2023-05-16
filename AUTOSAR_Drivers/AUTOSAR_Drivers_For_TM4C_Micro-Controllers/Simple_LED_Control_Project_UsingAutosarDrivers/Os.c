 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.c
 *
 * Description: Source file for Os Scheduler.
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 
#include "Os.h"
#include "App.h"
#include "Gpt.h"
#include "OS_Registers.h"

/*******************************************************************************
 *                      Private Global Variables Definitions                   *
 *******************************************************************************/
/* Global variable store the Os Time */
STATIC uint8 g_Time_Tick_Count = ZERO;

/* Global variable to indicate the the timer has a new tick */
STATIC uint8 g_New_Time_Tick_Flag = ZERO;

/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/
/* Description: 
 * Function responsible for:
 * 1. Enable Interrupts
 * 2. Start the Os timer
 * 3. Execute the Init Task
 * 4. Start the Scheduler to run the tasks
 */
void Os_start(void)
{
    /* Global Interrupts Enable */
    Enable_Interrupts();
    
    /* Assign priority level 3 to the SysTick Interrupt */
     NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) \
                    | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
    
    /* Initilize The GPT Driver to Configure Systick Timer */
    Gpt_Init(&Gpt_Configuration);
    
    /* Interrupt Enable for Systick Timer */
    Gpt_EnableNotification(GPT_CONFIG_SYSTICK_INDEX);

    /* Start Systic timer in continous mode with base time 20 milli second */
    Gpt_StartTimer(GPT_CONFIG_SYSTICK_INDEX, NUM_OF_TICKS_FOR_OS_BASE_TIME); 
 
    /* Execute the Init Task */
    Init_Task();

    /* Start the Os Scheduler */
    Os_Scheduler();
}

/* Description: Function called by the Timer Driver in the MCAL layer using the call back pointer */
void Gpt_Notification_Systick(void)
{
    /* Increment the Os time by OS_BASE_TIME */
    g_Time_Tick_Count   += OS_BASE_TIME;

    /* Set the flag to 1 to indicate that there is a new timer tick */
    g_New_Time_Tick_Flag = ONE;
    }

/* Description: The Engine of the Os Scheduler used for switch between different tasks */
void Os_Scheduler(void)
{
    while(1)
    {
	/* Code is only executed in case there is a new timer tick */
	if(g_New_Time_Tick_Flag == ONE)
	{
	    switch(g_Time_Tick_Count)
            {
		case TWENTY:
		case HUNDRED:
			    Button_Task();
			    g_New_Time_Tick_Flag = ZERO;
			    break;
		case FOURTY:
		case EIGHTY:
			    Button_Task();
			    Led_Task();
			    g_New_Time_Tick_Flag = ZERO;
			    break;
		case SIXITY:
			    Button_Task();
			    App_Task();
			    g_New_Time_Tick_Flag = ZERO;
			    break;
		case HUNDRED_AND_TWENTY:
			    Button_Task();
			    App_Task();
			    Led_Task();
			    g_New_Time_Tick_Flag = ZERO;
			    g_Time_Tick_Count = ZERO;
			    break;
                default: 
                            ;/* Do Nothing */
            }
	}
    }
}
