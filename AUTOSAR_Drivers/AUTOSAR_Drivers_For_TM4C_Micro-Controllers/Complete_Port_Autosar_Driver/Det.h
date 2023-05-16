 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.h
 *
 * Description:  Det stores the development errors reported by other modules.
 *               This header file is a STUB for the Det Module
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

#ifndef DET_H
#define DET_H

/*******************************************************************************
 *                             ID - Version Info                               *
 *******************************************************************************/
/* Id for the company in the AUTOSAR */
#define DET_VENDOR_ID                 (3312U)

/* Det Module Id */
#define DET_MODULE_ID                 (15U)

/* Instance Id */
#define DET_INSTANCE_ID               (0U)

/*
 * Det Software Module Version 1.0.0
 */
#define DET_SW_MAJOR_VERSION          (1U)
#define DET_SW_MINOR_VERSION          (0U)
#define DET_SW_PATCH_VERSION          (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DET_AR_MAJOR_VERSION          (4U)
#define DET_AR_MINOR_VERSION          (0U)
#define DET_AR_PATCH_VERSION          (3U)


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/      
/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Det Modules */
#if ((DET_AR_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/*******************************************************************************
 *                    Public Global Variables Decelerations                    *
 *******************************************************************************/ 
extern uint16 Det_ModuleId;       /* DET module ID */
extern uint8 Det_InstanceId;      /* DET instance ID */
extern uint8 Det_ApiId;           /* DET API ID */
extern uint8 Det_ErrorId;         /* DET Error ID */

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/******************************************************************************
* Service Name: Det_ReportError
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ModuleId - DET module ID
*                  InstanceId - DET instance ID
*                  ApiId - DET API ID
*                  ErrorId - DET Error ID
* Parameters (inout): None
* Parameters (out): Std_ReturnType
* Return value: None
* Description: Function to Store the information of Development Error that is 
*              that is reported.
*******************************************************************************/
Std_ReturnType Det_ReportError
(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId 
);

#endif /* DET_H */
