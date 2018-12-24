#include "timer.h"
#include "s3c2440_soc.h"
#include "interrupt.h"





void timer0_handler()
{
	static u8 t=3;
	static u8 m=0;
	m++;
	if(m==100)
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





/*		定时器0的输入时钟为1M   即1us计一次数
**		计数为10000
**		10ms 中断一次
*/

void timer0_init()
{
	//定时器输入时钟频率 = PCLK / {预分频值+1} / {分频值}   输入时钟为1M
	TCFG0 |=24;						//定时器 0 和 1 的预分频值为99
	TCFG1 &= ~(15<<0);				//定时器0分频值为2

	TCNTB0 = 9999;					//计数10000
	TCON |= 1<<3;					//使能自动重装载
	TCON &= ~(1<<2);				//关闭变相
	TCON |=1<<1;					//开启手动更新TCNTB0
	TCON |=1<<0;					//开启定时器0
	TCON &= ~(1<<1);				//关闭手动更新


	Register_IRQ(10,timer0_handler);
	
}






















