#include "led.h"
#include "s3c2440_soc.h"
#include "usart.h"




//  *++p			���ƶ�ָ��  ��ȡֵ
//	 *p++  		��ȡֵ�����ƶ�ָ��

u32 i=0;
char g_A = 'A';
char g_a = 'a';
unsigned int bb=0;
unsigned int cc;

int main(void)
{


	led_init();



	while(1)
	{
		i=500000;
		putchar(g_A);
		putchar(g_a);

		g_A++;
		g_a++;
		while(i--);
		


	}


	return 0;

}





























