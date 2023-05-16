 /******************************************************************************
 *
 * Module: UART Module
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART driver using Polling technique.
 *
 * Author: Marwan Abdelhakim Elmasry
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "uart.h"
#include "common_macros.h"
#include <avr/io.h>

/*******************************************************************************
 *                        Public Function Definitions	                       *
 *******************************************************************************/

/*
 * Description:
 * This function initialize the UART Module Dynamically according to the user
 * configuration : Number of stop bit, Number of data bit ,Parity status
 * and the baud rate.
 */
void UART_init(const DynamicConfiguration_UART *a_configuration_Ptr)
{
	uint16 L_ubrrValue = 0;

	/*
	 * Always work in Double speed mode to decrease the change that UBRR register
	 * will have a negative value which we don't want to happen.
	 */
	UCSRA |= (1<< U2X);

	/* USCRB register Description:
	 *
 	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = Bit2 from the structure variable  s_noOfDataBit [Decided Dynamically]
	 * RXB8 & TXB8 = 0  : It doesn't matter if we put them in zero because if
	 * 					  you use 9 bit mode this data will be set or read in
	 * 					  another function after calling the initialization function
 	 */
	UCSRB = (1<<RXEN) | (1<<TXEN) |  (a_configuration_Ptr->s_numOfDataBit  & 0x04);

   /* UCSRC register Description :
	*
	* URSEL   = 1 The URSEL must be one when writing the UCSRC
	* UMSEL   = 0 Asynchronous Operation
	* UPM1:0  = Bit 1:0 in the structure variable s_parity [Decided Dynamically]
	* USBS    = Bit 0  in the structure variable s_noOfStopBit [Decided Dynamically]
	* UCSZ1:0 = Bit1:0 from the structure variable  s_noOfDataBit [Decided Dynamically]
	* UCPOL   = 0 We don't care about it as we work with Asynchronous mode
	* 			not Synchronous
	*/

	UCSRC = (1<<URSEL) | ( ( a_configuration_Ptr->s_numOfStopBit  &0x01)   << USBS ) \
					   | ( ( a_configuration_Ptr->s_numOfDataBit  & 0x03)  << UCSZ0 )  \
					   | ( (  a_configuration_Ptr->s_parity       & 0x03 ) << UPM0 ) ;


	/* Calculate the UBRR register value  but take care that the baud rate you
	 * entered won't make a negative value to be stored UBRR.
	 *
	 * To avoid negative UBRR:
	 *  ( F_CPU / (a_configuration_Ptr->s_baudRate * 8) ) >= 1
	 *
	 * If a negative value is the result Overflow will happen and the data stored
	 * in UBRR will be rubbish to take care of baud rate calculations
	 */
	L_ubrrValue = (uint16)( ( F_CPU / (a_configuration_Ptr->s_baudRate * 8) ) - 1 );

	/* Set the the last 4 bits in L_ubrrValue in UBRRH and URSEL = 0 to write
	 * in UBRRH register not USCRC register;
	 */
	UBRRH = L_ubrrValue >> 8 ;

	/* Set the the first 8 bits in L_ubrrValue in UBRRH	*/
	UBRRL = (uint8)L_ubrrValue;
}


/*
 * Description :
 * This function will send the data -according to the number of data bit used-
 * serially to another UART device.
 */
void UART_sendData(uint8 a_data)
{

	/* Polling until UDRE flag is Set where the UDR will be empty and ready to take
	 * new data to transmit it
	 */
	while( BIT_IS_CLEAR(UCSRA,UDRE) );

	/*
	 * In case of 9 bit mode we put the 9th bit in UCSRB register to be transmitted
	 * if any mode other than 9 mode is chosen the 9th bit will be ignored.
	 */
	UCSRB = (UCSRB & 0xFE) | ( (a_data & 0x0100) >>8 );

	/* Send the 8 bit of the argument and according to the mode the needed bits
	 * will be taken and other will be ignored
	 */
	UDR = a_data;
}


/*
 * Description :
 * This function will Receive the data -according to the number of data bit used-
 * From another UART device.
 */
uint16 UART_receiveData(void)
{
	uint8 L_numOfDataBit=0;

	/* Loop until RXC will be set to 1 when the byte Which indicates
	 * that the incoming data has been received
	 */
	while( BIT_IS_CLEAR(UCSRA ,RXC )) ;

	/*	Get the Configuration which tells me what is the number of data bit used  */
	L_numOfDataBit = (UCSRB & 0x04) | ( (UCSRC & 0x06) >> UCSZ0 ) ;


	if(L_numOfDataBit == _9_DATA_BIT )
	{
		/*If the number of data send is 9 bit so return the 8 bit in UDR and teh
		 * 9th bit in RXB8 in UCSRB register
		 */
		return ( UDR | ((UCSRB & 0x02) << 7) ) ;
	}
	else
	{
		/*	If the number of data send is anything other than 9 bit mode return
		 *	the bits received in UDR register
		 */
		return UDR;
	}
}

/*
 * Description :
 * This function will Transmit String[a_str] to another UART device
 * We will choose a symbol[ # ] that is known to both devices the Transmitter will
 * send all the strings ended with specific symbol[#] and the Receiver will receive the
 * string and loop until he found the symbol[#] , when he finds it will stop reading.
 */
void UART_sendString(const uint8 *a_str)
{
	/*	Counter to loop upon the coming String */
	uint8 i = 0 ;

	/* By using the counter the loop with iterate the string characters
	 * and each time we will compare each character with the null character if
	 * it found -String has ended- break out of the loop
	 */
	while( a_str[i] != '\0')
	{
		/*	Send the whole string character by character  */
		UART_sendData(a_str[i]);
		i++;
	}

	/* Always Send the symbol that we agree on as the last character so that in
	 * receive function we will stop taking input when the this symbol is detected
	 */
	UART_sendData('#');
}

/*
 * Description :
 * This function will Receive String[a_str] from another UART device
 * We will choose a symbol[ # ] that is known to both devices the Transmitter will
 * send all the strings ended with specific symbol[#] and the Receiver will receive the
 * string and loop until he found the symbol[#] , when he finds it will stop reading.
 */
void UART_receiveString(uint8 *a_str)
{
	/*	Counter to loop upon the coming String */
	uint8 i = 0 ;

	/* Receive the first byte only so that we can have a value to be compared
	 * with the symbol
	 */
	a_str[i] = UART_receiveData();

	/* Receive the whole string until the symbol '#' is found	*/
	while( a_str[i] != '#')
	{
		i++;
		a_str[i] = UART_receiveData();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	a_str[i] = '\0' ;

}
