/******************************************************************************
 *
 * Module: TWI Module
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI driver using Polling technique.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef TWI_H_
#define TWI_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                          Definition - Configurations                        *
 *******************************************************************************/
/*	I2C Status Bits Values in TWSR register */

#define TWI_START             0x08     /* start has been sent */
#define TWI_REP_START         0x10	   /* repeated start */
#define TWI_M_T_SL_ADD_W_ACK  0x18     /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_M_T_SL_ADD_R_ACK  0x40     /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_M_T_DATA_ACK      0x28     /* Master transmit data and ACK has been received from Slave. */
#define TWI_M_R_DATA_ACK      0x50     /* Master received data and send ACK to slave. */
#define TWI_M_R_DATA_NACK     0x58     /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/

/*
 * Description :
 * This structure has all the dynamic configuration for the TWI module to works
 * as the user want. All the user need to do supply the Bit rate of the CLK
 * in which the Bits will be transfered with and Specify and address for the
 * MCU as it will be needed in communication with other MCUs .
 */
typedef struct
{
	uint32		s_frequencyOfSCL;
	uint32		s_myAddress;
}DynamicConfiguration_TWI;


/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
/*
 * Description :
 * This function will initialize the TWI module :
 * 1) Enable the TWI module
 * 2) Set the Frequency of the the SCL Clock
 * 3) Set a Specific address for the MCU
 *
 * NOTE :
 * TWBR can't have negative values. if it has, overflow will be the result So to
 * prevent any error make sure that the supplied frequency is more than
 * or equal F_CPU / 16
 */
void TWI_init(const DynamicConfiguration_TWI *a_configuration_Ptr);

/*
 * Description:
 * This function will Make The First TWI operation for every TWI frame which
 * is the Start Condition
 */
void TWI_startCondition(void);

/*
 * Description:
 * This function will Make The Last TWI operation for every TWI frame which
 * is the Stop Condition
 */
void TWI_stopCondition(void);

/*
 * Description:
 * This function will write the the input data in TWDR if it has access to TWI bus
 */
void TWI_writeByte(uint8 a_data);

/*
 * Description :
 * This function supposed to read the data if it send either by Master or Slave
 * and will respond with ACK if data is read and reached to its destination successfully
 *
 * It will return the data read if there is no errors happens  in TWI operations
 */
uint8 TWI_readByteWithACK(void);

/*
 * Description :
 * This function supposed to read the data if it send either by Master or Slave
 * and won't respond with ACK -which mean it send NACK-
 *
 * It will return the data read if there is no errors happens  in TWI operations
 */
uint8 TWI_readByteWithNACK(void);


/*
 * Description :
 * This function will return the 5 status bit in TWSR register.
 * These 5 bit changes according to the actions happens[Start,restart,send byte,...]
 * It gives you more information than TWINT flag If you want more information
 * about the action see the Status table at the Data sheet.
 */
uint8 TWI_getStatus(void);

#endif /* TWI_H_ */
