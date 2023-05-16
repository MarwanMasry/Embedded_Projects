 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef PORT_H_
#define PORT_H_

/*******************************************************************************
 *                             ID - Version Info                               *
 *******************************************************************************/
/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (3312U)

/* PORT Module Id */
#define PORT_MODULE_ID    (124U)

/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Software Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/  
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


/* Port Types Header file */
#include "Port_Types.h"

/* AUTOSAR Version checking between Port_Types.h and Port.h files */
#if ((PORT_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Types.h does not match the expected version"
#endif

/* Software Version checking between Port_Types.h and Port.h files */
#if ((PORT_TYPES_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_TYPES_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_TYPES_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Types.h does not match the expected version"
#endif
   
   
/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Port Post Build Configuration Header file */
#include "Port_PBCfg.h"

/* AUTOSAR Version checking between Port_PBCfg.h and port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_PBCfg.h does not match the expected version"
#endif

/* Software Version checking between Port_PBCfg.h and port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_PBCfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/*******************************************************************************
 *                          Pre-Processors Definition                          *
 *******************************************************************************/
/* Defines needed to know if the port driver is initialized or not */
#define PORT_INITIALIZED                        (1U)
#define PORT_NOT_INITIALIZED                    (0U)
  
/******************************************************************************
 *                           API Service Id Macros                            *
 ******************************************************************************/
/* service ID for PORT init */
#define PORT_INIT_SID                           (uint8)0x00

/* service ID for PORT set pin direction */
#define PORT_SET_PIN_DIRECTION_SID              (uint8)0x01

/* service ID for PORT refresh pin direction */
#define PORT_REFRESH_PORT_DIRECTION_SID         (uint8)0x02

/* service ID for PORT get version info */
#define PORT_GET_VERSION_INFO_SID               (uint8)0x03

/* service ID for PORT set pin mode */
#define PORT_SET_PIN_MODE_SID                   (uint8)0x04
   
/*******************************************************************************
 *                              DET Error Codes                                *
 *******************************************************************************/ 
/* Invalid Port Pin ID requested */   
#define     PORT_E_PARAM_PIN                    (uint8)0x0A

/* Port Pin not configured as changeable */   
#define     PORT_E_DIRECTION_UNCHANGEABLE       (uint8)0x0B

/* API Port_Init service called with wrong parameter. */   
#define     PORT_E_PARAM_CONFIG                 (uint8)0x0C

/* API Port_SetPinMode service called and Port Pin Mode passed not valid */   
#define     PORT_E_PARAM_INVALID_MODE           (uint8)0x0D

/* API Port_SetPinMode service called when mode is unchangeable */   
#define     PORT_E_MODE_UNCHANGEABLE            (uint8)0x0E

/* API service called without module initialization */   
#define     PORT_E_UNINIT                       (uint8)0x0F

/* APIs called with a Null Pointer */   
#define     PORT_E_PARAM_POINTER                (uint8)0x10
   
/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/   
   
/******************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
*******************************************************************************/
extern void Port_Init
( 
    const Port_ConfigType* ConfigPtr 
); 
   
/******************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number,
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
*******************************************************************************/  
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)

extern void Port_SetPinDirection
(
    Port_PinType Pin, 
    Port_PinDirectionType Direction
);

#endif
/*******************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
*******************************************************************************/   
extern void Port_RefreshPortDirection(void); 

 /******************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module
* Return value: None
* Description: Returns the version information of this module.
*******************************************************************************/   
#if (PORT_VERSION_INFO_API == STD_ON) 
 
extern void Port_GetVersionInfo
( 
    Std_VersionInfoType* versioninfo
); 

#endif
/******************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number,
                   Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
*******************************************************************************/   
#if (PORT_SET_PIN_MODE_API == STD_ON)

extern void Port_SetPinMode
(
    Port_PinType Pin,
    Port_PinModeType Mode
);

#endif

#endif /* PORT_H_ */
