#include "timer.h"
#include "s3c2440_soc.h"
#include "interrupt.h"
#include "lcd/lcd.h"

static timer0 timer0_reg[timer0_num];


void timer0_handler()
{
	u8 i;
	for(i=0;i<timer0_num;i++)
	{
		if(timer0_reg[i].p_time0_func)
			timer0_reg[i].p_time0_func();


	}


}



int time0_regeister(char *name , timer0_func p)
{
	u8 i;
	
	for(i=0;i<timer0_num;i++)
	{
		if(!timer0_reg[i].p_time0_func)					//timer0_reg的地址就是结构体名字的首地址
		{
			timer0_reg[i].name 		 = name;
			timer0_reg[i].p_time0_func  = p;
			return 1;

		}

	}
	return -1;
}

void time0_unregesiter(char *name)
{
	u8 i;
	for(i=0;i<timer0_num;i++)
	{
		if(strcmp(timer0_reg[i].name , name))
		{
			timer0_reg[i].name		    = 0;
			timer0_reg[i].p_time0_func = 0;

		}


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
	
	TCON &= ~(1<<2);				//关闭变相
	TCON |=1<<1;					//开启手动更新TCNTB0
	TCON &= ~(1<<1);				//关闭手动更新
	TCON |=1<<0;					//开启定时器0
	TCON |= 1<<3;					//使能自动重装载
	

	Register_IRQ(10,timer0_handler);
	
}






















