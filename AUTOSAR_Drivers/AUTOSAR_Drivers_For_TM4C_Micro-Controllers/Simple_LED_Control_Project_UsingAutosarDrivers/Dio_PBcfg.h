 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_PBcfg.h
 *
 * Description: Post Build Configuration Header file for TM4C123GH6PM Microcontroller
 *              - Dio Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef DIO_PBCFG_H_
#define DIO_PBCFG_H_

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define DIO_PBCFG_SW_MAJOR_VERSION              (1U)
#define DIO_PBCFG_SW_MINOR_VERSION              (0U)
#define DIO_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define DIO_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/  
#include "Dio_Types.h"

/* AUTOSAR Version checking between Dio_PBcfg.h and Dio_Types.h files */
#if ((DIO_PBCFG_AR_RELEASE_MAJOR_VERSION != DIO_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_MINOR_VERSION != DIO_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_PATCH_VERSION != DIO_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Types.h does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.h and Port_Types.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_TYPES_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_TYPES_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_TYPES_SW_PATCH_VERSION))
  #error "The SW version of Dio_Types.h does not match the expected version"
#endif


/*******************************************************************************
 *                    Public Global Variables Decelerations                    *
 *******************************************************************************/
/* Extern PB structures to be used by Dio and other modules */
extern const Dio_ConfigType Dio_Configuration;

#endif /* DIO_PBCFG_H_ */
