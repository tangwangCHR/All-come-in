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


void printHex(unsigned int val)
{
	int i;
	unsigned char arr[8];

	/* 先取出每一位的值 */
	for (i = 0; i < 8; i++)
	{
		arr[i] = val & 0xf;
		val >>= 4;   /* arr[0] = 2, arr[1] = 1, arr[2] = 0xF */
	}

	/* 打印 */
	puts("0x");
	for (i = 7; i >=0; i--)
	{
		if (arr[i] >= 0 && arr[i] <= 9)
			putchar(arr[i] + '0');
		else if(arr[i] >= 0xA && arr[i] <= 0xF)
			putchar(arr[i] - 0xA + 'A');
	}
}





























