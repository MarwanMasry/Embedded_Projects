 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_PBcfg.h
 *
 * Description: Post Build Configuration Header file for TM4C123GH6PM Microcontroller
 *              - Gpt Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef GPT_PBCFG_H_
#define GPT_PBCFG_H_

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define GPT_PBCFG_SW_MAJOR_VERSION              (1U)
#define GPT_PBCFG_SW_MINOR_VERSION              (0U)
#define GPT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/  
#include "Gpt_Types.h"

/* AUTOSAR Version checking between Gpt_PBcfg.h and Gpt_Types.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_Types.h does not match the expected version"
#endif

/* Software Version checking between Gpt_PBcfg.h and Gpt_Types.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_TYPES_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_TYPES_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_TYPES_SW_PATCH_VERSION))
  #error "The SW version of Gpt_Types.h does not match the expected version"
#endif


/*******************************************************************************
 *                    Public Global Variables Decelerations                    *
 *******************************************************************************/
   
/* GPT configuration structure, that hold the configurations of all Timers. */
extern const Gpt_ConfigType Gpt_Configuration;

#endif /* GPT_PBCFG_H_ */
