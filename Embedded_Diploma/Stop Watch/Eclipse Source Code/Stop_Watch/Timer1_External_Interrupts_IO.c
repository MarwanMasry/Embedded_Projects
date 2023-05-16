/*
 * Timer1_External_Interrupts.c
 *
 *  Created on: Sep 21, 2021
 *      Author: marwan
 */


/*	Includes Needed	*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Global_variables.h"



/*	#defines Needed	*/
#define	PORTC_OUTPUT_DIRECTON_MUSK		0X0F
#define PORTC_ZERO_INITIAL_VALUE_MUSK	0XF0

#define	PORTA_OUTPUT_DIRECTON_MUSK		0X3F
#define PORTA_ZERO_INITIAL_VALUE_MUSK	0XC0




/*	I\O Configuration	*/

void PORTC_PORTA_Init(void)
{
	/*	Make PC0...3 as Output and make initial values zero for SSD	 */
	DDRC |= PORTC_OUTPUT_DIRECTON_MUSK ;
	PORTC &= PORTC_ZERO_INITIAL_VALUE_MUSK ;

	/*	Make PA0...5 as Output and make initial values zero for BJT	 */
	DDRA |= PORTA_OUTPUT_DIRECTON_MUSK ;
	PORTA &= PORTA_ZERO_INITIAL_VALUE_MUSK ;

}



/*	Timer1 Configuration	*/

/*
 * For clock = 1Mhz and prescale F_CPU/1024 ,The frequency of the timer is 976.56 HZ
 * every count will take 1.024ms, so we just need 977 counts  to get 1s period
 */
void Timer1_Init(void)
{
	TCNT1 = 0;		/* Set timer1 initial count to zero */

	OCR1A = 977;    /* Set the Compare value to 977 (to get 1 sec) */

	TIMSK |= (1<<OCIE1A); /* Enable Timer1 Compare A Interrupt */

	/* Configure timer control register TCCR1A
	* 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	* 2. FOC1A=1 FOC1B=0
	* 3. CTC Mode WGM10=0 WGM11=0
	*/
	TCCR1A = (1<<FOC1A);

	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0
	 * 2. Prescaler = F_CPU/1024 CS10=1 CS11=0 CS12=1
	 */
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12);

}



ISR(TIMER1_COMPA_vect)
{
	/*Every second the Timer calculates just increments the sec1 variable in
	 * the Global array Stop_watch at position 0
	 */
	stop_watch[0]++;
}



/*	External Interrupts Configuration */

/*		INT0	*/
void INT0_Init(void)
{
	/*Disable any Interrupts because the initialization
	 *  is critical code section it is important	*/
	SREG  &= ~(1<<7);


	/* Make PD2 as Input for the button	and Activate internal Pull up resistance*/
	DDRD &= ~(1<<DD2);
	PORTD |= (1<<PD2);

	/*	Trigger INT0 to falling edge	*/
	MCUCR |= (1<<ISC01);
	MCUCR &= ~(1<<ISC00);


	/*	 Enable MIE for INT0	*/
	GICR |= (1<<INT0);


	/*	End of Critical code	*/
	SREG  |= (1<<7);
}

ISR(INT0_vect)
{
	unsigned char i ;

	for(i=0 ; i<6 ; i++)
	{
		stop_watch[i] = 0;
	}
}



/*	INT1	*/
void INT1_Init(void)
{
	/*Disable any Interrupts because the initialization
	 *  is critical code section it is important	*/
	SREG &= ~(1<<7);

	/* Make PD3 as input  and Activate internal up resistor	*/
	DDRD &= ~(1<<DD3);
	PORTD |= (1<<PD3);

	/* Trigger INT1 with the rising edge	*/
	MCUCR |= (1<<ISC11) | (1<<ISC10);

	/* Enable MIE for INT1	*/
	GICR |= (1<<INT1);



	/*	End of Critical code	*/
	SREG |= (1<<7);
}

ISR(INT1_vect)
{
	/*	Turn off the Clock of the Timer so it stop Counting	*/
	TCCR1B &=  ~(1<<CS10) & ~(1<<CS12);
}


/*	INT2	*/
void INT2_Init(void)
{
	/*Disable any Interrupts because the initialization
	 *  is critical code section it is important	*/
	SREG   &= ~(1<<7);

	/* Configure INT2/PB2 as input pin and Activate internal Pull up resistor */
	DDRB   &= ~(1<<PB2);
	PORTB  |= (1<<PB2);

	/* Enable MIE for INT2	*/
	GICR   |= (1<<INT2);

	/*	Trigger INT0 to falling edge	*/
	MCUCSR &= ~(1<<ISC2);

	/*	End of Critical code	*/
	SREG   |= (1<<7);
}

ISR(INT2_vect)
{
	/*	Re-supply the Clock of the Timer so it resume Counting	*/
	TCCR1B |= (1<<CS10) | (1<<CS12);
}
