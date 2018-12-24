#include "led.h"
#include "s3c2440_soc.h"
#include "usart.h"
#include  "my_printf.h"



//  *++p			���ƶ�ָ��  ��ȡֵ
//	 *p++  		��ȡֵ�����ƶ�ָ��


int main(void)
{
	u8 flag=0;
	u32 i=0;
	volatile u32 *p =(volatile u32 *)(0x30000000);
	SDRAM_init();
	led_init();
	usart0_init();
	GPFDAT |=7<<4;

	for(i=0;i<10;i++)
	{
		*p++=5;

	}
	p--;											//��Ϊ�ϴε�ַ�����1   ����Ҫ��ȥ
	for(i=0;i<10;i++)
	{
		if(*p-- !=5)
		{
			flag=0;
			break;
		}
		else
			flag =1;
	
	}




	if(flag)
		GPFDAT &= ~(1<<5);
	while(1);

	return 0;

}





























