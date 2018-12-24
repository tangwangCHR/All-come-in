#include "led.h"
#include "s3c2440_soc.h"




/*
*       led    D10        D11         D12
*               PF4         PF5         PF6
*/


void led_time0_handler()
{
	static u8 t=3;
	static u8 m=0;
	m++;
	if(m==50)
	{
		GPFDAT &= ~(7<<4);
		GPFDAT |= t<<4;
		t++;
		if(t==4)
			t=5;
		if(t>6)
			t=3;
		m=0;

	}


}





void led_init()
{

	GPFCON &= ~((3<<10)|(3<<8)|(3<<12));		//复位全部为0
	GPFCON |=  ((1<<10)|(1<<8)|(1<<12));		//设置为输出模式
	time0_regeister("led_test",led_time0_handler);


}

















