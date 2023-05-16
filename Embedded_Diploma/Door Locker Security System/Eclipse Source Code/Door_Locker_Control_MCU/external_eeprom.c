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

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "external_eeprom.h"
#include "twi.h"


/*******************************************************************************
 *                        Public Function Definitions	                       *
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
OperationState_EXTERNAL_EEPROM EXTERNAL_EEPROM_writeByte(uint16 a_memoryAddress , uint8 a_dataWritten)
{
	/*	To write Data in EEPROM we must Follow the following Frame :
	 *
	 * [S] [1010 + 3 memory address + 0] [ACK] [ Reaming 8 bit of memory address] [ACK] [Data] [ACK OR NACK] [P]
     *	M              M			       S                   M 			        S     M	          S       M
	 */

	/*	We will start by  sending	the start condition	*/
	TWI_startCondition();
	/*	Check if the operation[Start condition] is done successfully , if not
	 *  return ERROR
	 */
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}


	/*	Write the constant ID of EEPROM 1010 then add the 8th , 9th ,10th bit in
	 *  the input Address then the LSB is the R/W bit and we are writing to it so
	 *  it will be 0 			 [1010 + 3 memory address + 0]
	 */
	TWI_writeByte((uint8) (0xA0  | ((a_memoryAddress & 0x0700) >> 7) ));
	/*	Check if the operation[Writing writing slave address and receive ACK + write bit]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_SL_ADD_W_ACK)
	{
		return ERROR;
	}


	/*	Write the reaming 8 bit address of Memory address. total address = 11 bit */
	TWI_writeByte((uint8) (a_memoryAddress));
	/*	Check if the operation[Writing writing data and receive ACK from slave]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_DATA_ACK)
	{
		return ERROR;
	}


	/*	Write the Data which will be written in External EEPROM */
	TWI_writeByte((uint8) (a_dataWritten));
	/*	Check if the operation[Writing writing data and receive ACK from slave]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_DATA_ACK)
	{
		return ERROR;
	}


	/*	We will Finish by sending	the Stop condition */
	TWI_stopCondition();


	/*	If all the above code is executed successfully return success	*/
	return SUCCESS;
}


/*
 * Description :
 *
 * This function will return success if the byte is Read successfully from the
 * memory which mean all the TWI operation used is done successfully.
 * It will return Error if any TWI operation has failed to be done.
 * All the function need the address of the place where you want to read from and
 * the Pointer value to save the data which is read form the memory.
 */
OperationState_EXTERNAL_EEPROM EXTERNAL_EEPROM_readByte(uint16 a_memoryAddress , uint8 *a_dataRead_Ptr)
{
	/*	To read Data from EEPROM we must Follow the following Frame :
	 *
	 * 	[S] [1010 + 3 memory address + 0] [ACK] [ Reaming 8 bit of memory address] [ACK]
	 *	 M                M	           		S                     M     			 S
	 *						[S] [1010 + 3 memory address + 1] [ACK] [ Read Data] [NACK] [P]
	 *						 M             M                    S        S         M     M
	 */

	/*	We will start by  sending	the start condition	*/
	TWI_startCondition();
	/*	Check if the operation[Start condition] is done successfully , if not
	 *  return ERROR
	 */
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}


	/*	Write the constant ID of EEPROM 1010 then add the 8th , 9th ,10th bit in
	 *  the input Address then the LSB is the R/W bit and we are writing to it so
	 *   it will be 0 			 [1010 + 3 memory address + 0]
	 */
	TWI_writeByte((uint8) (0xA0  | ((a_memoryAddress & 0x0700) >> 7) ));
	/*	Check if the operation[Writing writing slave address and receive ACK + write bit]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_SL_ADD_W_ACK)
	{
		return ERROR;
	}


	/*	Write the reaming 8 bit address of Memory address. total address = 11 bit */
	TWI_writeByte((uint8) (a_memoryAddress));
		/*	Check if the operation[Writing writing data and receive ACK from slave]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_DATA_ACK)
	{
		return ERROR;
	}

	/*	We will Restart by  sending	the start condition	*/
	TWI_startCondition();
	/*	Check if the operation[Restart condition] is done successfully , if not
	 *  return ERROR
	 */
	if(TWI_getStatus() != TWI_REP_START)
	{
		return ERROR;
	}


	/*	Write the constant ID of EEPROM 1010 then add the 8th , 9th ,10th bit in
	 *  the input Address then the LSB is the R/W bit and we are reading from it
	 *  so it will  be 0 			 [1010 + 3 memory address + 1]
	 */
	TWI_writeByte((uint8) (0xA0  | ((a_memoryAddress & 0x0700) >> 7) | 1 ));
		/*	Check if the operation[Writing writing slave address and receive ACK + read bit]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_SL_ADD_R_ACK)
	{
		return ERROR;
	}


	/*	Save the value read from memory in parameter pointer */
	*a_dataRead_Ptr = TWI_readByteWithNACK();
	/*	Check if the operation[reading from the EEPROM + receive NACK from master]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_R_DATA_NACK)
	{
		return ERROR;
	}


	/*	We will Finish by sending	the Stop condition */
	TWI_stopCondition();


	/*	If all the above code is executed successfully return success	*/
	return SUCCESS;
}



/*
 * This function will return success if the Array is Stored successfully in the
 * memory which mean all the TWI operation used is done successfully.
 * It will return Error if any TWI operation has failed to be done.
 * All the function is need the starting address of Array and the array itself
 * to be stored and the size of the array
 */
OperationState_EXTERNAL_EEPROM EXTERNAL_EEPROM_writeArrayOfBytes(uint16 a_memoryAddress ,const uint8 *a_arr, uint8 a_arrSize)
{
	uint8 i;

	/*	To write Array of bytes in EEPROM we must Follow the following Frame :
	 *
	 * [S] [1010 + 3 memory address + 0] [ACK] [ Reaming 8 bit of memory address] [ACK]
     *	M              M			       S                   M 			        S
     *	looping with the array size on this part of frame: [Data]  [ACK]
     *														  M      S
     *	Then send the Stop bit :  [P]
     *							   M
	 */

	/*	We will start by  sending	the start condition	*/
	TWI_startCondition();
	/*	Check if the operation[Start condition] is done successfully , if not
	 *  return ERROR
	 */
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}


	/*	Write the constant ID of EEPROM 1010 then add the 8th , 9th ,10th bit in
	 *  the input Address then the LSB is the R/W bit and we are writing to it so
	 *  it will be 0 			 [1010 + 3 memory address + 0]
	 */
	TWI_writeByte((uint8) (0xA0  | ((a_memoryAddress & 0x0700) >> 7) ));
	/*	Check if the operation[Writing writing slave address and receive ACK + write bit]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_SL_ADD_W_ACK)
	{
		return ERROR;
	}


	/*	Write the reaming 8 bit address of Memory address. total address = 11 bit */
	TWI_writeByte((uint8) (a_memoryAddress));
	/*	Check if the operation[Writing writing data and receive ACK from slave]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_DATA_ACK)
	{
		return ERROR;
	}

	/*	We will Loop with the array size and save each byte of the input array
	 *  in the EEPROM
	 */
	for(i = 0 ; i<a_arrSize ; i++)
	{
		/*	Write consecutive bytes form the array in External EEPROM */
		TWI_writeByte((uint8) (a_arr[i]));
		/*	Check if the operation[Writing writing data and receive ACK from slave]
		 *  is done successfully , if not  return ERROR
		 */
		if(TWI_getStatus() != TWI_M_T_DATA_ACK)
		{
			return ERROR;
		}
	}

	/*	We will Finish by sending	the Stop condition */
	TWI_stopCondition();


	/*	If all the above code is executed successfully return success	*/
	return SUCCESS;

}



/*
 * This function will return success if the Array is Read successfully in the
 * memory which mean all the TWI operation used is done successfully.
 * It will return Error if any TWI operation has failed to be done.
 * All the function is need the starting address of Array stored in EEPROM and
 *  the array to save in it the array in EEPROM and the size of the array
 */
OperationState_EXTERNAL_EEPROM EXTERNAL_EEPROM_readArrayOfBytes(uint16 a_memoryAddress ,uint8 *a_readArray , uint8 a_arrSize)
{
	uint8 i ;

	/*	To read Array of bytes from EEPROM we must Follow the following Frame :
	 *
	 * 	[S] [1010 + 3 memory address + 0] [ACK] [ Reaming 8 bit of memory address] [ACK]
	 *	 M                M	           		S                     M     			 S
	 *											[S] [1010 + 3 memory address + 1] [ACK]
	 *											 M             M                    S
	 *	Loop with this part with array size - 1       : [ Read Data] [ACK]
	 *												    	 S         M
	 *	Read the last byte alone so we can send NACK :  [ Read Data ] [NACK]
	 *														 S        	M
	 *	Send Stop bit : 	[P]
	 *					     M
	 */

	/*	We will start by  sending	the start condition	*/
	TWI_startCondition();
	/*	Check if the operation[Start condition] is done successfully , if not
	 *  return ERROR
	 */
	if(TWI_getStatus() != TWI_START)
	{
		return ERROR;
	}


	/*	Write the constant ID of EEPROM 1010 then add the 8th , 9th ,10th bit in
	 *  the input Address then the LSB is the R/W bit and we are writing to it so
	 *   it will be 0 			 [1010 + 3 memory address + 0]
	 */
	TWI_writeByte((uint8) (0xA0  | ((a_memoryAddress & 0x0700) >> 7) ));
	/*	Check if the operation[Writing writing slave address and receive ACK + write bit]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_SL_ADD_W_ACK)
	{
		return ERROR;
	}


	/*	Write the reaming 8 bit address of Memory address. total address = 11 bit */
	TWI_writeByte((uint8) (a_memoryAddress));
		/*	Check if the operation[Writing writing data and receive ACK from slave]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_DATA_ACK)
	{
		return ERROR;
	}

	/*	We will Restart by  sending	the start condition	*/
	TWI_startCondition();
	/*	Check if the operation[Restart condition] is done successfully , if not
	 *  return ERROR
	 */
	if(TWI_getStatus() != TWI_REP_START)
	{
		return ERROR;
	}


	/*	Write the constant ID of EEPROM 1010 then add the 8th , 9th ,10th bit in
	 *  the input Address then the LSB is the R/W bit and we are reading from it
	 *  so it will  be 0 			 [1010 + 3 memory address + 1]
	 */
	TWI_writeByte((uint8) (0xA0  | ((a_memoryAddress & 0x0700) >> 7) | 1 ));
		/*	Check if the operation[Writing writing slave address and receive ACK + read bit]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_T_SL_ADD_R_ACK)
	{
		return ERROR;
	}

	/*	We will Loop with the array size -1 and save each byte from EEPROM to the
	 *  input array and each time we will send ACK , The last byte will be send alone.
	 */
	for(i=0 ; i < a_arrSize -1 ; i++)
	{
		/*	Save the value read from memory in input array */
		a_readArray[i] = TWI_readByteWithACK();
		/*	Check if the operation[reading from the EEPROM + receive ACK from master]
		 *  is done successfully , if not  return ERROR
		 */
		if(TWI_getStatus() != TWI_M_R_DATA_ACK)
		{
			return ERROR;
		}
	}

	/*	The last byte of the array will be read alone so that the master will send
	 *  NACK not ACK like all the previous bytes
	 */
	a_readArray[i] = TWI_readByteWithNACK();
	/*	Check if the operation[reading from the EEPROM + receive NACK from master]
	 *  is done successfully , if not  return ERROR
	 */
	if(TWI_getStatus() != TWI_M_R_DATA_NACK)
	{
		return ERROR;
	}


	/*	We will Finish by sending	the Stop condition */
	TWI_stopCondition();


	/*	If all the above code is executed successfully return success	*/
	return SUCCESS;

}

