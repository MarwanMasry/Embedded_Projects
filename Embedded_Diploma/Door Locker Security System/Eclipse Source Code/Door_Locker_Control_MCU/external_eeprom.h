/******************************************************************************
 *
 * Module: External EEPROM Module  [24Cxx EEPROM Family]
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for the External EEPROM driver  [24Cxx EEPROM Family]
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
/*
 * Description:
 * This enumeration is used as indication if the result of External EEPROM operations
 * which is done , Is it successful or Not
 */
typedef enum
{
	 SUCCESS = 1 , ERROR = -1
}OperationState_EXTERNAL_EEPROM;


/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*
 * Description :
 *
 * This function will return success if the byte is written successfully in the
 * memory which mean all the TWI operation used is done successfully.
 * It will return Error if any TWI operation has failed to be done.
 * All the function need the address of the place where you want to write in and
 * the data to be stored there.
 */
OperationState_EXTERNAL_EEPROM EXTERNAL_EEPROM_writeByte(uint16 a_memoryAddress , uint8 a_dataWritten);


/*
 * Description :
 *
 * This function will return success if the byte is Read successfully from the
 * memory which mean all the TWI operation used is done successfully.
 * It will return Error if any TWI operation has failed to be done.
 * All the function need the address of the place where you want to read from and
 * the Pointer value to save the data which is read form the memory.
 */
OperationState_EXTERNAL_EEPROM EXTERNAL_EEPROM_readByte(uint16 a_memoryAddress , uint8 *a_dataRead_Ptr);


/*
 * This function will return success if the Array is Stored successfully in the
 * memory which mean all the TWI operation used is done successfully.
 * It will return Error if any TWI operation has failed to be done.
 * All the function is need the starting address of Array and the array itself
 * to be stored and the size of the array
 */
OperationState_EXTERNAL_EEPROM EXTERNAL_EEPROM_writeArrayOfBytes(uint16 a_memoryAddress ,const uint8 *a_arr, uint8 a_arrSize);


/*
 * This function will return success if the Array is Read successfully in the
 * memory which mean all the TWI operation used is done successfully.
 * It will return Error if any TWI operation has failed to be done.
 * All the function is need the starting address of Array stored in EEPROM and
 *  the array to save in it the array in EEPROM and the size of the array
 */
OperationState_EXTERNAL_EEPROM EXTERNAL_EEPROM_readArrayOfBytes(uint16 a_memoryAddress , uint8 *a_readArray , uint8 a_arrSize);


#endif /* EXTERNAL_EEPROM_H_ */
