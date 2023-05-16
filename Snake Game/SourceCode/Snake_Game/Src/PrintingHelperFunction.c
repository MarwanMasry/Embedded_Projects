 /******************************************************************************
 *
 * File Name: PrintingHelperFunction.c
 *
 * Description: Source file for Printing Helper Function.
 *
 *******************************************************************************/

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "PrintingHelperFunction.h"
#include "stm32f4xx_hal.h"


/*******************************************************************************
 *                     			 Externs needed       				           *
 *******************************************************************************/
extern UART_HandleTypeDef huart3;

/*******************************************************************************
 *                          Public Function Definitions	                       *
 *******************************************************************************/
void print_Str(char *str)
{
	char *StringToSend= str;
	uint32 StrLen = 0;

/* calculate string length */
	while(*str)
	{
		StrLen++;
		str++;
	}

	/* Print the string */
	HAL_UART_Transmit(&huart3, (uint8*)StringToSend, StrLen,200);
}

void print_Buff(char *Buff,uint32 len)
{
	HAL_UART_Transmit(&huart3, (uint8*)Buff, len,200);
}


void print_Dec(uint32 n)
{
	uint8 buff[ sizeof(sint32)*8+1 ] = {0};

	my_itoa(n,(uint8*)buff,10);

	print_Str((char*)buff);
}

void my_reverse(uint8 *str, uint32 len)
{
	uint32 start, end;
	uint8 temp;
	for(start=0, end=len-1; start < end; start++, end--)
	{
		temp = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = temp;
	}
}

void my_itoa(sint32 num, uint8* str, uint32 base)
{
    uint32 i = 0;
    uint8 isNegative = 0;

    /* A zero is same "0" string in all base */
    if (num == 0)
	{
        str[i] = '0';
        str[i + 1] = '\0';
        return ;
    }

    /* negative numbers are only handled if base is 10  otherwise considered unsigned number */
    if (num < 0 && base == 10)
	{
        isNegative = 1;
        num = -num;
    }

    while (num != 0)
	{
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
        num = num/base;
    }

    /* Append negative sign for negative numbers */
    if (isNegative)
	{
        str[i++] = '-';
    }

    str[i] = '\0';

    my_reverse(str, i);

    return ;
}
