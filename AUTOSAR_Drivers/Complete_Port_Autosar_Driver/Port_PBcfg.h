 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.h
 *
 * Description: Post Build Configuration Header file for TM4C123GH6PM Microcontroller
 *              - Port Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef PORT_PBCFG_H_
#define PORT_PBCFG_H_

/*******************************************************************************
 *                              Version Info                                   *
 *******************************************************************************/
/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/  
#include "Port_Types.h"

/* AUTOSAR Version checking between Port_PBcfg.h and Port_Types.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Types.h does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.h and Port_Types.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_TYPES_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_TYPES_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_TYPES_SW_PATCH_VERSION))
  #error "The SW version of Port_Types.h does not match the expected version"
#endif

/*******************************************************************************
 *                    Public Global Variables Decelerations                    *
 *******************************************************************************/
/* PB structure used with Port_Init API  and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_PBCFG_H_ */
