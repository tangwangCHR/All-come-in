#include "led.h"
#include "s3c2440_soc.h"




/*
*       led    D10        D11         D12
*               PF4         PF5         PF6
*/


void led_init()
{

	GPFCON &= ~((3<<10)|(3<<8)|(3<<12));		//复位全部为0
	GPFCON |=  ((1<<10)|(1<<8)|(1<<12));		//设置为输出模式



}















