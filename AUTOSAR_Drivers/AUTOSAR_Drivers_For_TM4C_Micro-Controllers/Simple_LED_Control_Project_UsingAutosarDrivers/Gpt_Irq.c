 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Irq.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Gpt Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define GPT_IRQ_SW_MAJOR_VERSION              (1U)
#define GPT_IRQ_SW_MINOR_VERSION              (0U)
#define GPT_IRQ_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_IRQ_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_IRQ_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_IRQ_AR_RELEASE_PATCH_VERSION     (3U)

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/

/* GPT  Header file */
#include "Gpt.h"

/* AUTOSAR Version checking between Gpt_Irq.c and Gpt.h files */
#if ((GPT_IRQ_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_IRQ_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_IRQ_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt.h does not match the expected version"
#endif

/* Software Version checking between Gpt_Irq.c and Gpt.h files */
#if ((GPT_IRQ_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_IRQ_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_IRQ_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of Gpt.h does not match the expected version"
#endif   

/*******************************************************************************
 *                             ISR's Definitions                               *
 *******************************************************************************/
   
/*******************************************************************************
* Service Name: SysTick_Handler
* Description: SysTick Timer ISR
*******************************************************************************/
void SysTick_Handler( void )
{
    /*
     * Just call the function which access all the private resources to do the 
     * the required function 
     */
    Gpt_CalledBySystickISR();
}   


