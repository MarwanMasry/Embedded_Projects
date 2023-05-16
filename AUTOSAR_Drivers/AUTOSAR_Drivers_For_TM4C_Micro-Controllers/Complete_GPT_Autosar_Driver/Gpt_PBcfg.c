 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller
 *              - Gpt Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/  
#include "Gpt_PBcfg.h"

#include "Gpt_cfg.h"
/* AUTOSAR Version checking between Gpt_PBcfg.h and Gpt_cfg.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_CFG_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_CFG_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_CFG_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_cfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_PBcfg.h and Gpt_cfg.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_CFG_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_CFG_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_CFG_SW_PATCH_VERSION))
  #error "The SW version of Gpt_cfg.h does not match the expected version"
#endif 

/*******************************************************************************
 *                       Call Back Function Decleration                        *
 *******************************************************************************/

/*
 * Description: 
 * This Prototype will be generated using the Configuration Generator Tool as 
 * we need to make extern to the call back function so that we can pass it to 
 * configuration structure.
 * Note: The name of call back function will be supported by the user and according
 *       to that that name the prototype will be generated, Also it is the user
 *       responsibility to implement the call back function in any of his .c files.
 */  
 extern void Gpt_Notification_Systick(void);   
   
/*******************************************************************************
 *                      Public Global Variables Definitions                    *
 *******************************************************************************/  
   
/* GPT configuration structure, that hold the configurations of all Timers. */
const Gpt_ConfigType Gpt_Configuration1 = 
{
    GPT_SYSTICK_TIMER_ID, GPT_CH_MODE_CONTINUOUS, SYSTEM_CLOCK, GPT_CONFIG_SYSTICK_MAX_VALUE, NO_PRESCALER, Gpt_Notification_Systick 
};

const Gpt_ConfigType Gpt_Configuration2 = 
{
    GPT_SYSTICK_TIMER_ID, GPT_CH_MODE_ONESHOT, SYSTEM_CLOCK, GPT_CONFIG_SYSTICK_MAX_VALUE, NO_PRESCALER, Gpt_Notification_Systick 
};