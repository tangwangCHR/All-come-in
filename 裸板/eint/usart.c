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


void printHex(unsigned int val)
{
	int i;
	unsigned char arr[8];

	/* ��ȡ��ÿһλ��ֵ */
	for (i = 0; i < 8; i++)
	{
		arr[i] = val & 0xf;
		val >>= 4;   /* arr[0] = 2, arr[1] = 1, arr[2] = 0xF */
	}

	/* ��ӡ */
	puts("0x");
	for (i = 7; i >=0; i--)
	{
		if (arr[i] >= 0 && arr[i] <= 9)
			putchar(arr[i] + '0');
		else if(arr[i] >= 0xA && arr[i] <= 0xF)
			putchar(arr[i] - 0xA + 'A');
	}
}





























