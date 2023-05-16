 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Types.h
 *
 * Description: Header file that has all the needed type decelerations
 *              - Gpt Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef GPT_TYPES_H_
#define GPT_TYPES_H_

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define GPT_TYPES_SW_MAJOR_VERSION              (1U)
#define GPT_TYPES_SW_MINOR_VERSION              (0U)
#define GPT_TYPES_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_TYPES_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_TYPES_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_TYPES_AR_RELEASE_PATCH_VERSION     (3U)


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/      
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Gpt Types */
#if ((GPT_TYPES_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
 || (GPT_TYPES_AR_RELEASE_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
 || (GPT_TYPES_AR_RELEASE_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif
   
/* GPT Pre-Compile Configuration Header file */
#include "Gpt_Cfg.h"

/* AUTOSAR Version checking between Gpt_Cfg.h and Gpt_Types.h files */
#if ((GPT_CFG_AR_RELEASE_MAJOR_VERSION != GPT_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_MINOR_VERSION != GPT_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_PATCH_VERSION != GPT_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_Cfg.h and Gpt_Types.h files */
#if ((GPT_CFG_SW_MAJOR_VERSION != GPT_TYPES_SW_MAJOR_VERSION)\
 ||  (GPT_CFG_SW_MINOR_VERSION != GPT_TYPES_SW_MINOR_VERSION)\
 ||  (GPT_CFG_SW_PATCH_VERSION != GPT_TYPES_SW_PATCH_VERSION))
  #error "The SW version of Gpt_Cfg.h does not match the expected version"
#endif   
   
/*******************************************************************************
 *                          Pre-Processors Definition                          *
 *******************************************************************************/
/* Needed for Frequency Pre scaler */
#define NO_PRESCALER            STD_LOW   
   
/*******************************************************************************
 *                             Types Deceleration	                       *
 *******************************************************************************/   
/*
 * Description:
 * Numeric ID of a GPT channel.
 */
typedef uint8 Gpt_ChannelType;

/*
 * Description:
 * Type for reading and setting the timer values (in number of ticks).
 */
typedef uint32 Gpt_ValueType;

/*
 * Description: 
 * This Type is used to select the Prescaler for 12 General purpose timer 
 * supported in TM4C123GH6PM.
 *
 * The Six 16 or 32 Bit Timers has a prescaler value from 0 to 255 
 * Prescale (8-bit value).
 * 
 * The Six 32 or 64 Bit Timers has a prescaler value from 0 to 65535  
 * Prescale (16-bit value)
 */
typedef uint16 Gpt_Prescaler;

/*
 * Description:
 * The ID of the all supported Timers, it may by SYSTICK timer or any other 
 * General purpose timer supported in TM4C123GH6PM the micro-controller. 
 */
typedef enum
{
    GPT_SYSTICK_TIMER_ID,
    GPT_16_OR_32_BIT_TIMER_0_ID,
    GPT_16_OR_32_BIT_TIMER_1_ID,
    GPT_16_OR_32_BIT_TIMER_2_ID,
    GPT_16_OR_32_BIT_TIMER_3_ID, 
    GPT_16_OR_32_BIT_TIMER_4_ID,
    GPT_16_OR_32_BIT_TIMER_5_ID,
    GPT_32_OR_64_BIT_WIDE_TIMER_0_ID,
    GPT_32_OR_64_BIT_WIDE_TIMER_1_ID,
    GPT_32_OR_64_BIT_WIDE_TIMER_2_ID,
    GPT_32_OR_64_BIT_WIDE_TIMER_3_ID,
    GPT_32_OR_64_BIT_WIDE_TIMER_4_ID,
    GPT_32_OR_64_BIT_WIDE_TIMER_5_ID
}Gpt_ChannelTypeID;


/*
 * Description:
 * Specifies the status of each timer at runtime.
 */
typedef enum
{
    UNINITIALIZED,
    INITIALIZED,
    STOPPED,
    RUNNING,
    EXPIRED
}Gpt_ChannelStatus;

/*
 * Description:
 * Specifies the behaviour of the timer channel after the target time is reached.
 * Continuous mode : After reaching the target time, the timer continues running
 *                   with the value "zero" again.
 * One Shot mode   : After reaching the target time, the timer stops 
 *                  automatically (timer expired).
 */
typedef enum
{
    GPT_CH_MODE_CONTINUOUS,     
    GPT_CH_MODE_ONESHOT
}Gpt_ChannelMode;

/*
 * Description:
 * Allows the selection of different power modes.
 */
typedef enum
{
    GPT_MODE_NORMAL, 
    GPT_MODE_SLEEP
}Gpt_ModeType;

/*
 * Description: 
 * This enum is used to select the Clock Source, In Systick Timer we have the 
 * option to drive the Clock from the system Clock which is supplied using PLL
 * using MCAL Driver and it can be any value and also their is the option where 
 * The CLK source is Precision internal oscillator (Pl0SC) divided by 4, same 
 * concept applied to the 12 General Purpose timers in TM4C123GH6PM.
 */
typedef enum
{
    SYSTEM_CLOCK,
    PIOSC_DIV_BY_4
}Gpt_ChannelClkSrcRef;

/*
 * Description:
 * This is the data structure including configuration of each timer channel:
 *
 * 1- ChannelID: The ID of the supported Timers
 * 2- ChannelMode: Specifies the behaviour of the timer channel after the target 
 *                 time is reached.
 * 3- ChannelClkSourceRef: The Source of CLK that feeds the Timers.
 * 4- channelTickValueMax: Maximum value in ticks, the timer channel is able to count.
 *                         With the next tick, the timer rolls over to zero.
 * 5- ChannelFrequencyPrescaler: Frequency Presacler of the timer channel .
 * 6- Gpt_Notification_Ptr: Function pointer to callback function.
 */
typedef struct 
{
    Gpt_ChannelTypeID                    ChannelID;
    Gpt_ChannelMode                      ChannelMode;
    Gpt_ChannelClkSrcRef                 ChannelClkSourceRef;
    Gpt_ValueType                        ChannelTickValueMax;
    Gpt_Prescaler                        ChannelFrequencyPrescaler;
    void( *Gpt_Notification_Ptr )(void);
}Gpt_ConfigChannel; 
   
   
/*
 * Description:
 * This is the type of the data structure including the configuration set 
 * required for initializing the GPT timer unit.
 */
typedef struct
{
    Gpt_ConfigChannel      GptChannels[GPT_CONFIGURED_TIMER_CHANNELS];
}Gpt_ConfigType;

   
   
#endif /* GPT_TYPES_H_ */
