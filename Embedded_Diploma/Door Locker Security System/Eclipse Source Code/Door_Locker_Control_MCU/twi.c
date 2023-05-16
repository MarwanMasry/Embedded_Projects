/******************************************************************************
 *
 * Module: TWI Module
 *
 * File Name: twi.c
 *
 * Description: Source file for the TWI driver using Polling technique.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "twi.h"
#include "common_macros.h"
#include <avr/io.h>


/*******************************************************************************
 *                        Public Function Definitions	                       *
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
void TWI_init(const DynamicConfiguration_TWI *a_configuration_Ptr)
{

	/* TWCR register Description:
	 *
 	 * TWIE  = 0 : We won't write this driver using Interrupt we will use Polling
	 * TWEN  = 1 : Enable The TWI operation and Activates the TWI interface(override I/O functionality)
	 * TWWC      : Has no effect as this flag is set by hardware and cleared by 0
	 * TWSTO = 0 : We won't generate stop condition yet
	 * TWSTA = 0 : We won't generate start condition
	 * TWEA  = 0 : Disable Acknowledge bit , will be activated when needed
 	 * TWINT     : Has no effect on it as is set by hardware and cleared by setting it
 	 */
	TWCR = (1<<TWEN);

	/*
	 * TWSR register Description :
	 *
	 * TWPS 1:0 = 0 : We set the prescaler which is used in the formula to calculate
	 * 				  SCL frequency to zero to have a Prescaler value = 1
	 */
	TWSR &= ~(1<<TWPS1) & ~(1<<TWPS0) ;

	/*
	 *  TWAR register Description:
	 *
	 *  TWGCE = 0 : Disable the Recognition of General calls over the bus
	 *  TWA 7:0   : They are set Dynamically according to the structure variable s_myAddress
	 */
	TWAR = (a_configuration_Ptr->s_myAddress) << 1 ;

	/*
	 * We set the value of TWBR with a value accoridng to the target Bit rate of
	 * the TWI bus.
	 *
	 * 1 in the equation is the result of prescaler as the we choose the result of
	 * TWPS 1:0 = 0  which gives us  a Prescaler value = 1
	 *
	 * NOTE :
	 * 	- TWBR register value must result in a Positive or zero value it can't
	 *    take a negative values or Overflow will be the result.
	 *
	 *  - TWBR will be negative only if the Input frequency F_SCL < (F_CPU / 16)
	 *
	 * So to prevent any error make sure that the supplied frequency is more than
	 * or equal F_CPU / 16
	 *
	 */
	TWBR = ( (F_CPU / a_configuration_Ptr->s_frequencyOfSCL) - 16  ) / (2 * 1) ;

}

/*
 * Description:
 * This function will Make The First TWI operation for every TWI frame which
 * is the Start Condition
 */
void TWI_startCondition(void)
{

	/* TWCR register Description:
	 *
 	 * TWIE  = 0 : We won't write this driver using Interrupt we will use Polling
	 * TWEN  = 1 : Enable The TWI operation and Activates the TWI interface(override I/O functionality)
	 * TWWC      : Has no effect as this flag is set by hardware and cleared by 0
	 * TWSTO = 0 : We won't generate stop condition yet
	 * TWSTA = 1 : Generate start condition
	 * TWEA  = 0 : Disable Acknowledge bit , will be activated when needed
 	 * TWINT = 0 : It will be cleared to prevent CLK stretch because when it is
 	 *  		   set it cause Clock Stretch , We need the CLK  for TWI
 	 *  		   operation (start) to take place
 	 */
	 TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ;

	 /*
	  * Polling until TWINT is set as when it is set it is indication that TWI
	  * has finished the current job which is sending the Start condition
	  */
	 while( BIT_IS_CLEAR(TWCR , TWINT) );
}

/*
 * Description:
 * This function will Make The Last TWI operation for every TWI frame which
 * is the Stop Condition
 */
void TWI_stopCondition(void)
{

	/* TWCR register Description:
	 *
 	 * TWIE  = 0 : We won't write this driver using Interrupt we will use Polling
	 * TWEN  = 1 : Enable The TWI operation and Activates the TWI interface(override I/O functionality)
	 * TWWC      : Has no effect as this flag is set by hardware and cleared by 0
	 * TWSTO = 1 : Generate stop condition yet
	 * TWSTA = 0 : we won't generate start condition
	 * TWEA  = 0 : Disable Acknowledge bit , will be activated when needed
 	 * TWINT = 0 : It will be cleared to prevent CLK stretch because when it is
 	 *  		   set it cause Clock Stretch , We need the CLK for TWI
 	 *  		   operation (Stop) to take place
 	 */
	 TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN) ;

}

/*
 * Description:
 * This function will write the the input data in TWDR if it has access to TWI bus
 */
void TWI_writeByte(uint8 a_data)
{
	/*
	 * Put the data need to be written in TWDR and it supposed to be sent in the
	 * bus as soon as TWBR is assigned with the data value
	 * Here it won't sent because the TWINT is set which result in Clock Stretch
	 */
	TWDR = a_data;

	/* TWCR register Description:
	 *
 	 * TWIE  = 0 : We won't write this driver using Interrupt we will use Polling
	 * TWEN  = 1 : Enable The TWI operation and Activates the TWI interface(override I/O functionality)
	 * TWWC      : Has no effect as this flag is set by hardware and cleared by 0
	 * TWSTO = 0 : we won't generate stop condition yet
	 * TWSTA = 0 : we won't generate start condition
	 * TWEA  = 0 : Disable Acknowledge bit , will be activated when needed
 	 * TWINT = 0 : It will be cleared to prevent CLK stretch because when it is
 	 *  		   set it cause Clock Stretch , We need the CLK for TWI
 	 *  		   operation (write data) to take place
 	 */
	 TWCR = (1<<TWINT) | (1<<TWEN) ;

	 /*
	  * Polling until TWINT is set as when it is set it is indication that TWI
	  * has finished the current job which is Writing data in the bus
	  */
	 while( BIT_IS_CLEAR(TWCR , TWINT) );

}

/*
 * Description :
 * This function supposed to read the data if it send either by Master or Slave
 * and will respond with ACK if data is read and reached to its destination successfully
 *
 * It will return the data read if there is no errors happens  in TWI operations
 */
uint8 TWI_readByteWithACK(void)
{

	/* TWCR register Description:
	 *
 	 * TWIE  = 0 : We won't write this driver using Interrupt we will use Polling
	 * TWEN  = 1 : Enable The TWI operation and Activates the TWI interface(override I/O functionality)
	 * TWWC      : Has no effect as this flag is set by hardware and cleared by 0
	 * TWSTO = 0 : we won't generate stop condition yet
	 * TWSTA = 0 : we won't generate start condition
	 * TWEA  = 1 : Enable the ACK so that after reading the data an ACK is sent to data sender
 	 * TWINT = 0 : It will be cleared to prevent CLK stretch because when it is
 	 *  		   set it cause Clock Stretch , We need the CLK for TWI
 	 *  		   operation (Reading data) to take place
 	 */
	 TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

	 /*
	  * Polling until TWINT is set as when it is set it is indication that TWI
	  * has finished the current job which is Reading the data from the bus and
	  * save it TWDR
	  */
	 while( BIT_IS_CLEAR(TWCR , TWINT) );

	 /*	When data is received successfully we return it	*/
	 return TWDR;
}

/*
 * Description :
 * This function supposed to read the data if it send either by Master or Slave
 * and won't respond with ACK -which mean it send NACK-
 *
 * It will return the data read if there is no errors happens  in TWI operations
 */
uint8 TWI_readByteWithNACK(void)
{

	/* TWCR register Description:
	 *
 	 * TWIE  = 0 : We won't write this driver using Interrupt we will use Polling
	 * TWEN  = 1 : Enable The TWI operation and Activates the TWI interface(override I/O functionality)
	 * TWWC      : Has no effect as this flag is set by hardware and cleared by 0
	 * TWSTO = 0 : we won't generate stop condition yet
	 * TWSTA = 0 : we won't generate start condition
	 * TWEA  = 0 : Disable the ACK so that after reading the data an NACK is sent to data sender
 	 * TWINT = 0 : It will be cleared to prevent CLK stretch because when it is
 	 *  		   set it cause Clock Stretch , We need the CLK for TWI
 	 *  		   operation (Reading data) to take place
 	 */
	 TWCR = (1<<TWINT) | (1<<TWEN);

	 /*
	  * Polling until TWINT is set as when it is set it is indication that TWI
	  * has finished the current job which is Reading the data from the bus and
	  * save it TWDR
	  */
	 while( BIT_IS_CLEAR(TWCR , TWINT) );

	 /*	When data is received successfully we return it	*/
	 return TWDR;

}


/*
 * Description :
 * This function will return the 5 status bit in TWSR register.
 * These 5 bit changes according to the actions happens[Start,restart,send byte,...]
 * It gives you more information than TWINT flag If you want more information
 * about the action see the Status table at the Data sheet.
 */
uint8 TWI_getStatus(void)
{
	/*
	 * Return the 5 bit of TWSR which are on the righ as they are the status bit
	 * for every TWI operation happens
	 *
	 * We don't shift them Left because the default value of these status bits
	 * on the data sheet is already shifted to right , What is mean is the first
	 * 3 bits of all status values are always zeros
	 */
	return (TWSR & 0xF8);
}
