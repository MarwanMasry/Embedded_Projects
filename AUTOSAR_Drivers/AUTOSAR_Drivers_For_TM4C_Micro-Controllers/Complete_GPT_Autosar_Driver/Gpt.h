 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Gpt Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef GPT_H_
#define GPT_H_

/*******************************************************************************
 *                             ID - Version Info                               *
 *******************************************************************************/
/* Id for the company in the AUTOSAR */
#define GPT_VENDOR_ID    (3312U)

/* GPT Module Id */
#define GPT_MODULE_ID    (100U)

/* GPT Instance Id */
#define GPT_INSTANCE_ID  (0U)

/*
 * Module Software Version 1.0.0
 */
#define GPT_SW_MAJOR_VERSION           (1U)
#define GPT_SW_MINOR_VERSION           (0U)
#define GPT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_AR_RELEASE_MAJOR_VERSION   (4U)
#define GPT_AR_RELEASE_MINOR_VERSION   (0U)
#define GPT_AR_RELEASE_PATCH_VERSION   (3U)

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/  
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and GPT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* GPT Types Header file */
#include "Gpt_Types.h"

/* AUTOSAR Version checking between Gpt_Types.h and Gpt.h files */
#if ((GPT_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_TYPES_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_Types.h does not match the expected version"
#endif

/* Software Version checking between Gpt_Types.h and Gpt.h files */
#if ((GPT_TYPES_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_TYPES_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_TYPES_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of Gpt_Types.h does not match the expected version"
#endif


/* GPT Pre-Compile Configuration Header file */
#include "Gpt_cfg.h"

/* AUTOSAR Version checking between Gpt_Cfg.h and Gpt.h files */
#if ((GPT_CFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_Cfg.h and Gpt.h files */
#if ((GPT_CFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_CFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_CFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of Gpt_Cfg.h does not match the expected version"
#endif

/* GPT Post Build Configuration Header file */
#include "Gpt_PBcfg.h"

/* AUTOSAR Version checking between Gpt_PBCfg.h and Gpt.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_PBCfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_PBCfg.h and Gpt.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of Gpt_PBCfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/*******************************************************************************
 *                                  Macros                                     *
 *******************************************************************************/     

/* Go to low power mode(Sleep Mode) while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("WFI")


/*******************************************************************************
 *                              Pre-Processors                                 *
 *******************************************************************************/    
/* Defines Needed*/
#define GPT_INITIALIZED                (1U)
#define GPT_NOT_INITIALIZED            (0U)   
#define GPT_ENABLE_BIT_POSITION        (0U)
#define GPT_INTEN_BIT_POSITION         (1U)
#define GPT_CLK_SOURCE_BIT_POSITION    (2U)   
#define ONE                            (1U)   

/*******************************************************************************
 *                              DET Error Codes                                *
 *******************************************************************************/  
   
/* DET code to report API service called without module initialization. */
#define GPT_E_UNINIT                        (uint8)0x0A

/* DET code to report API service called when timer channel is still busy. */
#define GPT_E_BUSY                          (uint8)0x0B

/* DET code to report API service for initialization called when already initialized. */
#define GPT_E_ALREADY_INITIALIZED           (uint8)0x0D

/* DET code to report API parameter checking: invalid channel. */
#define GPT_E_PARAM_CHANNEL                 (uint8)0x14

/* DET code to report API parameter checking: invalid value. */
#define GPT_E_PARAM_VALUE                   (uint8)0x15

/* DET code to report API parameter checking: invalid pointer. */
#define GPT_E_PARAM_POINTER                 (uint8)0x16
   
/* DET code to report API parameter checking: invalid mode. */
#define GPT_E_PARAM_MODE                    (uint8)0x1F
   
/******************************************************************************
 *                           API Service Id Macros                            *
 ******************************************************************************/   
   
/* Service ID for Gpt_GetVersionInfo function. */
#define GPT_GET_VERSION_INFO_SID                   (uint8)0x00

/* Service ID for Gpt_Init function. */
#define GPT_INIT_SID                               (uint8)0x01

/* Service ID for Gpt_DeInit function. */
#define GPT_DEINIT_SID                             (uint8)0x02

/* Service ID for Gpt_GetTimeElapsed function. */
#define GPT_GET_TIME_ELAPSED_SID                   (uint8)0x03

/* Service ID for Gpt_GetTimeRemaining function. */
#define GPT_GET_TIME_REMAINING_SID                 (uint8)0x04

/* Service ID for Gpt_StartTimer function. */
#define GPT_START_TIMER_SID                        (uint8)0x05

/* Service ID for Gpt_StopTimer function. */
#define GPT_STOP_TIMER_SID                         (uint8)0x06
    
/* Service ID for Gpt_EnableNotification function. */
#define GPT_ENABLE_NOTIFICATION_SID                (uint8)0x07

/* Service ID for Gpt_DisableNotification function. */
#define GPT_DISABLE_NOTIFICATION_SID               (uint8)0x08
   
/* Service ID for Gpt_SetMode function. */
#define GPT_SET_MODE_SID                           (uint8)0x09
   
/* Service ID for Gpt_DisableWakeup function. */
#define GPT_DISABLE_WAKE_UP_SID                    (uint8)0x0A
   
/* Service ID for Gpt_EnableWakeup function. */
#define GPT_ENABLE_WAKE_UP_SID                     (uint8)0x0B
   
/* Service ID for Gpt_CheckWakeup function. */
#define GPT_CHECK_WAKE_UP_SID                      (uint8)0x0C
      
/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/   

/*******************************************************************************
* Service Name: Gpt_GetVersionInfo
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): VersionInfo - Pointer to where to store the version
* 				    information of this module.
* Return value: None
* Description: Function to get the version information of this module.
*******************************************************************************/
#if (GPT_VERSION_INFO_API == STD_ON)

extern void Gpt_GetVersionInfo
(
    Std_VersionInfoType *versioninfo
);

#endif

/*******************************************************************************
* Service Name: Gpt_Init
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr | Pointer to a selected configuration structure
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the hardware timer module.
*******************************************************************************/
extern void Gpt_Init
(
    const Gpt_ConfigType* ConfigPtr 
);

/*******************************************************************************
* Service Name: Gpt_DeInit
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Deinitializes all hardware timer channels.
*******************************************************************************/
#if (GPT_DEINIT_API == STD_ON)

extern void Gpt_DeInit( void );

#endif

/*******************************************************************************
* Service Name: Gpt_GetTimeElapsed
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Gpt_ValueType | Elapsed timer value (in number of ticks)
* Description: Returns the time already elapsed.
*******************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON) 

extern Gpt_ValueType Gpt_GetTimeElapsed
(
    Gpt_ChannelType Channel 
);

#endif

/*******************************************************************************
* Service Name: Gpt_GetTimeRemaining
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: Gpt_ValueType | Remaining timer value (in number of ticks)
* Description: Returns the time remaining until the target time is reached.
*******************************************************************************/
#if (GPT_TIME_REMAINING_API == STD_ON) 

extern Gpt_ValueType Gpt_GetTimeRemaining
(
    Gpt_ChannelType Channel
);

#endif

/*******************************************************************************
* Service Name: Gpt_StartTimer
* Service ID[hex]: 0x05
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel ,
*                  Value   | Target time in number of ticks.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Starts a timer channel.
*******************************************************************************/
extern void Gpt_StartTimer
( 
    Gpt_ChannelType Channel,
    Gpt_ValueType Value 
);

/*******************************************************************************
* Service Name: Gpt_StopTimer
* Service ID[hex]: 0x06
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Stops a timer channel.
*******************************************************************************/
extern void Gpt_StopTimer
(
    Gpt_ChannelType Channel
);

/*******************************************************************************
* Service Name: Gpt_EnableNotification
* Service ID[hex]: 0x07
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Enables the interrupt notification for a channel 
*             (relevant in normal mode).
*******************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) 

extern void Gpt_EnableNotification
(
    Gpt_ChannelType Channel
);

#endif 

/*******************************************************************************
* Service Name: Gpt_DisableNotification
* Service ID[hex]: 0x08
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Channel | Numeric identifier of the GPT channel.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Disables the interrupt notification for a channel 
*             (relevant in normal mode).
*******************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) 


extern void Gpt_DisableNotification
( 
    Gpt_ChannelType Channel 
);

#endif 


/*******************************************************************************
* Service Name: Gpt_CalledBySystickISR
* Sync/Async: Synchronous
* Reentrancy: Non-Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: This function is called when Systick interrupt is fired becasue 
*              we can't have our private resources to be accessed by other .c 
*              files so outside we call this function and here we access what is 
*              is needed
*******************************************************************************/
extern void Gpt_CalledBySystickISR(void);

#endif /* GPT_H_ */
