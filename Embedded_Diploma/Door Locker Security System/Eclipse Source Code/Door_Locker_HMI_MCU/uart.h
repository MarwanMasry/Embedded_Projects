/******************************************************************************
 *
 * Module: UART Module
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART driver using Polling technique.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/
#ifndef UART_H_
#define UART_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
/*
 * Description:
 * This Enumeration values is used to configure the UART according to even or
 * odd parity by manipulating UPM 1:0 bit in UCSRC register :
 *
 * UPM1 UPM0	 Parity Mode
 * 0	0		 Disable Parity
 * 1	0		 Even Parity
 * 1	1		 Odd  Parity
 */
typedef enum
{
	DISABLE_PARITY , EVEN_PARITY = 2 , ODD_PARITY
}Parity_UART;

/*
 * Description:
 * This Enumeration values is used to configure the UART according to number of
 * stop bit after the byte by changing the value of USBS  in UCSRC register :
 *
 * USBS		 Stop Bit(s)
 *	0 		 1-bit
 *	1 		 2-bit
 *
 */
typedef enum
{
	 _1_STOP_BIT , _2_STOP_BIT
}NumOfStopBit_UART;


/*
 * Description:
 * This Enumeration values is used to configure the UART according to How many data bits
 * is sent and received by changing the value of UCSZ 2:0 in UCSZ2 and UCSRB register:
 *
 * UCSZ2 UCSZ1 UCSZ0 	Character Size
 * 0 	 0	   0 	 	5-bit
 * 0 	 0	   1 	 	6-bit
 * 0 	 1	   0 	 	7-bit
 * 0 	 1	   1 	 	8-bit
 * 1	 1	   1		9-bit
 */
typedef enum
{
	 _5_DATA_BIT, _6_DATA_BIT,_7_DATA_BIT, _8_DATA_BIT ,_9_DATA_BIT = 7
}NumOfDataBit_UART;

/*
 * Description :
 * This structure has all the dynamic configuration for the UART module to works
 * as the user want. All the user need to do supply number of stop bit and number
 * of data bit and Parity status and the baud rate that he want to work with
 * and the Module will be initialized to that configuration.
 */
typedef struct
{
	Parity_UART			s_parity;
	NumOfDataBit_UART	s_numOfDataBit;
	NumOfStopBit_UART	s_numOfStopBit;
	uint32				s_baudRate;
}DynamicConfiguration_UART;

/*
 * Description:
 * This enumeration is used for synchronization of sending two MSG between two
 * MCU as the MCU won't Transmit data until data until the other MCU told him
 * that he is ready, I will use the Handshake technique during Transmitting/Receiving.
 */
typedef enum
{
	ARE_YOU_READY =1 , I_AM_READY
}SynchronizationStatus_UART;


/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*
 * Description:
 * This function initialize the UART Module Dynamically according to the user
 * configuration : Number of stop bit, Number of data bit ,Parity status
 * and the baud rate.
 */
void UART_init(const DynamicConfiguration_UART *a_configuration_Ptr);


/*
 * Description :
 * This function will send the data -according to the number of data bit used-
 * serially to another UART device.
 */
void UART_sendData(uint8 a_data);


/*
 * Description :
 * This function will Receive the data -according to the number of data bit used-
 * From another UART device.
 */
uint16 UART_receiveData(void);

/*
 * Description :
 * This function will Transmit String[a_str] to another UART device
 * We will choose a symbol[ # ] that is known to both devices the Transmitter will
 * send all the strings ended with specific symbol[#] and the Receiver will receive the
 * string and loop until he found the symbol[#] , when he finds it will stop reading.
 */
void UART_sendString(const uint8 *a_str);

/*
 * Description :
 * This function will Receive String[a_str] from another UART device
 * We will choose a symbol[ # ] that is known to both devices the Transmitter will
 * send all the strings ended with specific symbol[#] and the Receiver will receive the
 * string and loop until he found the symbol[#] , when he finds it will stop reading.
 */
void UART_receiveString(uint8 *a_str);

#endif /* UART_H_ */
