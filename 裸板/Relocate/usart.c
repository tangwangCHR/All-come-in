#include "usart.h"
#include "s3c2440_soc.h"


/*
*	TXD0	RXD0		TXD1	RXD1		TXD2	RXD2
*	PH2		PH3			PH4		PH5			PH6		PH7
*/







void usart0_init()
{

	GPHCON &= ~((3<<4)|(3<<6));	//����PH2 PH3 �����ڴ���ģʽ
	GPHCON |=  ((2<<4)|(2<<6));
	GPHUP  &= ~((1<<2)|(1<<3));	//ʹ����������

	ULCON0 |= 0x3;					//8n1
	UCON0  |=5<<0;					//PCLK��Ϊ����ʱ��	50Mhz
	UBRDIV0 =26;					//������115200


}



int putchar(int c)			//���һ���ַ�	����
{
	while(!(UTRSTAT0&(1<<2)));		//�ȴ��������
	
	UTXH0=(unsigned char)c;



}


int getchar(void)			//�õ�һ���ַ�    ����
{


	while (!(UTRSTAT0 & (1<<0)));		// ����Ĵ������յ���Ч����
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































