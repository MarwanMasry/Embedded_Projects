 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.h
 *
 * Description: Header file for Os Scheduler.
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/
#ifndef OS_H_
#define OS_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 
#include "Std_Types.h"

/*******************************************************************************
 *                          Pre-Processors Definition                          *
 *******************************************************************************/
/* Timer counting time in ms */
#define OS_BASE_TIME                       (20U)

/* Number of Ticks for OS base time */   
#define NUM_OF_TICKS_FOR_OS_BASE_TIME      (uint32)(320000)

/*  Needed Numbers */
#define ONE                                (1U)
#define TWENTY                             (20U)
#define HUNDRED                            (100U)
#define FOURTY                             (40U)
#define EIGHTY                             (80U)
#define SIXITY                             (60U)   
#define HUNDRED_AND_TWENTY                 (120U)

/* Defines needed to set the priority of Systic Timer */
#define SYSTICK_PRIORITY_MASK  0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY  3
#define SYSTICK_PRIORITY_BITS_POS   29

/*******************************************************************************
 *                                   Macros                                    *
 *******************************************************************************/

/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    __asm("CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   __asm("CPSID I")

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/   
/* Description: 
 * Function responsible for:
 * 1. Enable Interrupts
 * 2. Start the Os timer
 * 3. Execute the Init Task
 * 4. Start the Scheduler to run the tasks
 */
void Os_start(void);

/* Description: The Engine of the Os Scheduler used for switch between different tasks */
void Os_Scheduler(void);

/* Description: Function called by the Timer Driver in the MCAL layer using the call back pointer */
void Os_NewTimerTick(void);

#endif /* OS_H_ */
