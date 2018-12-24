#include "usart.h"
#include "s3c2440_soc.h"
#include "interrupt.h"




void test()
{
	puts("test\n\r");

}
void next()
{
	
	puts("next\n\r");

}





//  ÖÐ¶Ï×¢²á
void Register_IRQ(int intoffset , func fp)
{
	Register_irq[intoffset] = fp;
	INTMSK &= ~(1<<intoffset);

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




void IRQ_Handler()
{
	u32 val=INTOFFSET;
	Register_irq[val]();
	SRCPND |= (1<<val);
	INTPND |= (1<<val);

}


























