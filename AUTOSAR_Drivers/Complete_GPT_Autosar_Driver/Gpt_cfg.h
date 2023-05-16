 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller 
 *              - Gpt Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/
#ifndef GPT_CFG_H_
#define GPT_CFG_H_

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define GPT_CFG_SW_MAJOR_VERSION              (1U)
#define GPT_CFG_SW_MINOR_VERSION              (0U)
#define GPT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/*******************************************************************************
 *                          Pre-Compile Configuration                          *
 *******************************************************************************/

/* Pre-compile option that enables or disables development error detection. */
#define GPT_DEV_ERROR_DETECT                 (STD_ON)

/* Pre-compile option that enables or disables wakeup source reporting. */
#define GPT_REPORT_WAKEUP_SOURCE             (STD_OFF)
   
/* 
 * Reference to a container of the type McuClockReferencePoint,
 * to select an input clock. 
 */
#define GPT_CLOCK_REFERENCE     
   
/* 
 * Pre-compile option that adds or removes the service Gpt_DeInit() from the 
 * code. 
 */
#define GPT_DEINIT_API                       (STD_ON)   

/* 
 * Pre-compile option that adds or removes the services Gpt_EnableNotification() 
 * and Gpt_DisableNotification() from the code.
 */
#define GPT_ENABLE_DISABLE_NOTIFICATION_API  (STD_ON)   
 
/* 
 * Pre-compile option that adds or removes the service Gpt_GetTimeElapsed()
 * from the code.
 */
#define GPT_TIME_ELAPSED_API                 (STD_ON)

/* 
 * Pre-compile option that adds or removes the service Gpt_GetTimeRemaining() 
 * from the code.
 */
#define GPT_TIME_REMAINING_API               (STD_ON)   

/* 
 * Pre-compile option that adds or removes the service Gpt_GetVersionInfo() 
 * from the code.
 */
#define GPT_VERSION_INFO_API                 (STD_ON)

/* 
 * Pre-compile option that adds or removes the services Gpt_SetMode(), 
 * Gpt_EnableWakeup(), Gpt_DisableWakeup() and Gpt_CheckWakeup() from the code.
 */
#define GPT_WAKEUP_FUNCTIONALITY_API         (STD_OFF)
   

   
/* The Number of the configured Timer Channels */
#define GPT_CONFIGURED_TIMER_CHANNELS        (1U)

/* Timer Index in the array of structures in Gpt_PBcfg.c. */
#define GPT_CONFIG_SYSTICK_INDEX	     (uint8)0   

   

/* Configured timers' IDs. */
#define GPT_CONFIG_SYSTICK_TIMER_ID          GPT_SYSTICK_TIMER_ID

/* Configured timers' Modes. */
#define GPT_CONFIG_SYSTICK_MODE              GPT_CH_MODE_CONTINUOUS
   
/* Configured timers' Clock Source. */
#define GPT_CONFIG_SYSTICK_CLOCK_SOURCE      SYSTEM_CLOCK
   
   
/* Configured timers' maximum value. */
#define GPT_CONFIG_SYSTICK_MAX_VALUE         (0xFFFFFF)   
   
/* Configured timers' Prescalers. */
#define GPT_CONFIG_SYSTICK_PRESCALER         NO_PRESCALER   
   


#endif /* GPT_CFG_H_ */
