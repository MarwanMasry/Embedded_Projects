 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Registers.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Gpt Driver Registers
 *
 * Author: Marwan Abdelhakim Elmasry
 ******************************************************************************/
#ifndef GPT_REGISTERS_H_
#define GPT_REGISTERS_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/      
#include "Std_Types.h"

/*******************************************************************************
 *                          Pre-Processors Definition                          *
 *******************************************************************************/
/* Systick  Registers base addresses */
#define SYSTICK_CTRL_REG          (*((volatile uint32 *)0xE000E010))
#define SYSTICK_RELOAD_REG        (*((volatile uint32 *)0xE000E014))
#define SYSTICK_CURRENT_REG       (*((volatile uint32 *)0xE000E018))



#endif /* GPT_REGISTERS_H_ */
