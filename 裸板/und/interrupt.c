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
	puts("text\n\r");

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

































