


#include "s3c2440_soc.h"




void delay(unsigned int x)
{

	while(x--);

}

/*
*       按键  EINT0      EINT2    EINT11   EINT19
*               PF0        PF2      PG3     PG11
*/

/*
*       led    D10        D11         D12
*               PF4         PF5         PF6
*/

void key_led_init()
{
	GPFCON &= 0xffffc0cc;		//  PF0 2  为输入
	GPFCON |= 0x00001500;		//配置GPF4 5 6为输出引脚   led配置

	GPGCON &= 0xffffff3f;		//PG3为输入


}



int main(void)		
{
	key_led_init();
	
	while(1)
	{
		if(GPFDAT & 1<<0)
		{
			GPFDAT |=1<<4;

		}else{

			GPFDAT &= ~(1<<4);
		}
		

		if(GPFDAT & 1<<2)
		{
			GPFDAT |=1<<5;

		}else{

			GPFDAT &= ~(1<<5);
		}
		

		if(GPGDAT & 1<<3)
		{
			GPFDAT |=1<<6;

		}else{

			GPFDAT &= ~(1<<6);
		}


	}

	return 0;



}


























































