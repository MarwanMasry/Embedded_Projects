 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.c
 *
 * Description:  Det stores the development errors reported by other modules.
 *               This source file is a STUB for the Det Module
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "Det.h"

/*******************************************************************************
 *                      Public Global Variables Definitions                    *
 *******************************************************************************/

/* Variables to store last DET error */
uint16 Det_ModuleId = 0;       /* DET module ID */
uint8 Det_InstanceId = 0;      /* DET instance ID */
uint8 Det_ApiId = 0;           /* DET API ID */
uint8 Det_ErrorId = 0;         /* DET Error ID */

/*******************************************************************************
 *                          Public Function Definitions	                       *
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
*              that is reported in the Global Variables.
*******************************************************************************/
Std_ReturnType Det_ReportError
(
    uint16 ModuleId,
    uint8 InstanceId,
    uint8 ApiId,
    uint8 ErrorId 
)
{
    Det_ModuleId = ModuleId; 
    Det_InstanceId = InstanceId;
    Det_ApiId = ApiId; 
    Det_ErrorId = ErrorId;
    return E_OK;
}

