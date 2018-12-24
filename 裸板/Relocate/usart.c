#include "usart.h"
#include "s3c2440_soc.h"


/*
*	TXD0	RXD0		TXD1	RXD1		TXD2	RXD2
*	PH2		PH3			PH4		PH5			PH6		PH7
*/







void usart0_init()
{

	GPHCON &= ~((3<<4)|(3<<6));	//设置PH2 PH3 工作在串口模式
	GPHCON |=  ((2<<4)|(2<<6));
	GPHUP  &= ~((1<<2)|(1<<3));	//使能上拉功能

	ULCON0 |= 0x3;					//8n1
	UCON0  |=5<<0;					//PCLK作为串口时钟	50Mhz
	UBRDIV0 =26;					//波特率115200


}



int putchar(int c)			//输出一个字符	发送
{
	while(!(UTRSTAT0&(1<<2)));		//等待发送完成
	
	UTXH0=(unsigned char)c;



}


int getchar(void)			//得到一个字符    接收
{


	while (!(UTRSTAT0 & (1<<0)));		// 缓冲寄存器接收到有效数据
	return	URXH0;
		


}


int puts(const char *s)
{


	while(*s)
	{
		putchar(*s);
		s++;

	}



}































