/*
 ============================================================================
 Name        : main.c
 Author      : Marwan Abdelhakim Elmasry
 Description : Test Dio Driver.
 Date        : 24/4/2022
 ============================================================================
 */

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/ 
#include "Dio.h"
#include "Dio_ModuleTest.h"

/*******************************************************************************
 *                              Main Function                                  *
 *******************************************************************************/ 
int main(void)
{
    /* Initailize PF0, PF1, PF2 and PF4 as GPIO pins */
    GPIO_Pins_Init();

    /* Run the First Test Case */
    TestCase1();

    /* Initialize the Dio Driver */
    Dio_Init(&Dio_Configuration);

    /* Run the Second Test Case */
    TestCase2();
    
    /* Run the Third Test Case */
    TestCase3();

#if (DIO_VERSION_INFO_API == STD_ON)
    /* Run the Forth Test Case */
    TestCase4();
#endif

    /* Run the Fifth Test Case */
    TestCase5();

#if (DIO_FLIP_CHANNEL_API == STD_ON)
    /* Run the Sixth Test Case */
    TestCase6();
#endif

    /* Run the Seventh Test Case */
    TestCase7();
    
    /* Run the Eighth Test Case */
    TestCase8();    
    
  return 0;
}
