#include "usart.h"

void putt(void)
{
	puts("test\n\r");
}
void putt1(void)
{
	puts("test1\n\r");
}
void putt2(void)
{
	puts("test2\n\r");
}
void putt3(void)
{
	puts("test3\n\r");
}



void Copy_text_R_data(void)
{
	extern int _code_start,_end;
	volatile unsigned int *code_start = (volatile unsigned int *)&_code_start;
	volatile unsigned int *end = (volatile unsigned int *)&_end;
	volatile unsigned int *src = (volatile unsigned int *)0;
	puts("10\n\r");
	while(code_start < end)
	{
		*code_start++ = *src++ ;

	}
	puts("11\n\r");


}


void Copy_bss()
{
	extern int _bss_start,_end;
	volatile unsigned int *bss_start = (volatile unsigned int *)&_bss_start;
	volatile unsigned int *end = (volatile unsigned int *)&_end;
	

	puts("12\n\r");
	while(bss_start <= end)
	{
		*bss_start++=0;

	}
	puts("13\n\r");


}

























