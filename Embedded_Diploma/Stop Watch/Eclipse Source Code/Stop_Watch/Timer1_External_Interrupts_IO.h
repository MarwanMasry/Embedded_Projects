/*
 * Timer1_External_Interrupts.h
 *
 *  Created on: Sep 21, 2021
 *      Author: marwan
 */

#ifndef TIMER1_EXTERNAL_INTERRUPTS_IO_H_
#define TIMER1_EXTERNAL_INTERRUPTS_IO_H_



/*	I\O ProtoType	*/
void PORTC_PORTA_Init(void);


/*	Timer1 Prototype	*/
void Timer1_Init(void);

/*	External interrupts Prototype	*/
void INT0_Init(void);

void INT1_Init(void);

void INT2_Init(void);


#endif /* TIMER1_EXTERNAL_INTERRUPTS_IO_H_ */
