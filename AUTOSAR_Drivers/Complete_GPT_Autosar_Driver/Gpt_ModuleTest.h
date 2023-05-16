/******************************************************************************
 *
 * Module: ModuleTest
 *
 * File Name: Port_ModuleTest.h
 *
 * Description: Header file for the Port Test Cases.
 *
 * Marwan Abdelhakim Elmasry
 ******************************************************************************/
#ifndef GPT_MODULETEST_H_
#define GPT_MODULETEST_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 

 /*******************************************************************************
 *                              Pre-Processors                                 *
 *******************************************************************************/    
#define SYSTICK_PRIORITY_MASK  0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY  3
#define SYSTICK_PRIORITY_BITS_POS   29

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm("CPSIE I")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm("CPSID I")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm("CPSIE F")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm("CPSID F") 
 
/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/* Call back function */
extern void Gpt_Notification_Systick(void) ; 

/* Enable PF1 (RED LED) */
void Led_Red_Init(void);

/* Test the Systick timer to operate on Continous Mode*/
extern void Gpt_TestCase1(void);

/* Test the Systick timer to operate on one shot Mode*/
extern void Gpt_TestCase2(void);
   

   
   
   
#endif /* GPT_MODULETEST_H_ */
