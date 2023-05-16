/******************************************************************************
 *
 * Module: ModuleTest
 *
 * File Name: Dio_ModuleTest.h
 *
 * Description: Header file for the DIO Test Cases.
 *
 * Marwan Abdelhakim Elmasry
 ******************************************************************************/
#ifndef DIO_MODULETEST_H_
#define DIO_MODULETEST_H_



/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/  
#include "Std_Types.h"

/*******************************************************************************
 *                              Pre-Processors                                 *
 *******************************************************************************/ 
#define DIO_INVALIDE_CHANNEL_NUM 	50

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/************************************************************************************
* Test ID :TestCase1
* Description: Test for Write, Read and Flip Channel API's report a DIO_E_UNINIT DET
*              error in case the Dio_Init is not called yet.
* Pre-requisits: Dio Module is not initialized before Run this test case.
* Test Procedure : 1. Call Dio_WriteChannel DET error DIO_E_UNINIT should be reported.
*                  2. Call Dio_ReadChannel DET error DIO_E_UNINIT should be reported.
*                  3. Call Dio_FlipChannel DET error DIO_E_UNINIT should be reported.
*************************************************************************************/
void TestCase1(void);

/************************************************************************************
* Test ID :TestCase2
* Description: Test for Dio_Init and Dio_GetVersionInfo API's report the correct DET
*              error in case the API called with NULL pointer.
* Pre-requisits: No Need
* Test Procedure : 1. Call Dio_Init DET error DIO_E_PARAM_CONFIG should be reported.
*                  2. Call Dio_GetVersionInfo DET error DIO_E_PARAM_POINTER should be reported.
*************************************************************************************/
void TestCase2(void);

/************************************************************************************
* Test ID :TestCase3
* Description: Test for Write, Read and Flip Channel API's report a
*              DIO_E_PARAM_INVALID_CHANNEL_ID DET error in case invalid Channel ID.
* Pre-requisits: Dio Module is initialized before Run this test case.
* Test Procedure : 1. Call Dio_WriteChannel DET error DIO_E_PARAM_INVALID_CHANNEL_ID
*                     should be reported.
*                  2. Call Dio_ReadChannel DET error DIO_E_PARAM_INVALID_CHANNEL_ID
*                     should be reported.
*                  3. Call Dio_FlipChannel DET error DIO_E_PARAM_INVALID_CHANNEL_ID
*                     should be reported.
*************************************************************************************/
void TestCase3(void);

/************************************************************************************
* Test ID :TestCase4
* Description: Test for GetVersionInfo API functionality.
* Pre-requisits: No Need
* Test Procedure : Call Dio_GetVersionInfo and get the required information.
*************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)

void TestCase4(void);

#endif

/************************************************************************************
* Test ID :TestCase5
* Description: Test for Write and Read Channel API's functionality.
* Pre-requisits: Dio Module is initialized before Run this test case.
* Test Procedure : 1. Press SW1(PF4) then the Red led(PF1) shall be turned on.
*                  2. Press SW2(PF0) then the Red led(PF1) shall be turned off.
*************************************************************************************/
void TestCase5(void);

/************************************************************************************
* Test ID :TestCase6
* Description: Test for Flip and Read Channel API's functionality.
* Pre-requisits: Dio Module is initialized before Run this test case.
* Test Procedure : 1. Press SW1(PF4) then the blue led(PF2) shall be flipped (OFF --> ON).
*                  2. Press SW2(PF0) then the blue led(PF2) shall be flipped (ON --> OFF).
*************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)

void TestCase6(void);

#endif

/************************************************************************************
* Test ID :TestCase7
* Description: Test for Write and Read Port API's functionality.
* Pre-requisits: Dio Module is initialized before Run this test case.
* Test Procedure : 1. Press SW1(PF4) then you will see white light 
*                  2. Press SW2(PF0) then The white light will be turnned off.
*************************************************************************************/
void TestCase7(void);


/************************************************************************************
* Test ID :TestCase8
* Description: Test for Write and Read Group API's functionality.
* Pre-requisits: Dio Module is initialized before Run this test case.
* Test Procedure : 1. Press SW1(PF4) then you will see white light 
*                  2. Press SW2(PF0) then The white light will be turnned off.
*************************************************************************************/
void TestCase8(void);


/* Description: Initializing the GPIO Pins */
void GPIO_Pins_Init(void);

/* Description: Return true if the inputs matches what is reported */
boolean Det_TestLastReportError
(
		uint16 ModuleId,
		uint8 InstanceId,
		uint8 ApiId,
		uint8 ErrorId
);






#endif /* DIO_MODULETEST_H_ */
