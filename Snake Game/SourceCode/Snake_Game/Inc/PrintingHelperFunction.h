 /******************************************************************************
 *
 * File Name: PrintingHelperFunction.h
 *
 * Description: Source file for Printing Helper Function.
 *
 *******************************************************************************/

#ifndef INC_PRINTINGHELPERFUNCTION_H_
#define INC_PRINTINGHELPERFUNCTION_H_


/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/
void print_Str(char *str);

void print_Buff(char *Buff,uint32 len);

void print_Dec(uint32 n);

void my_reverse(uint8 *str, uint32 len);

void my_itoa(sint32 num, uint8* str, uint32 base);


#endif /* INC_PRINTINGHELPERFUNCTION_H_ */
