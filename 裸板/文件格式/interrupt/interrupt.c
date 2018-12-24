#include "usart.h"

void test1()
{
	puts("10\n\r");

}

void test2()
{
	puts("11\n\r");

}
void test()
{
	puts("test\n\r");

}
void next()
{
	
	puts("next\n\r");

}


void Undefined_Handler(unsigned int cpsr,char *str)
{
	puts("cpsr =");
	printHex(cpsr);
	puts("\n\r");
	puts(str);
	puts("\n\r");


}



void Printf_Swi_num(unsigned int *swi_num)
{
	puts("swi_num =");
	printHex((*swi_num)&0x00ffffff);
	puts("\n\r");


}





























