#include "touch.h"
#include "../interrupt.h"
#include "../s3c2440_soc.h"
#include "../lcd/font.h"
#include "../timer.h"
#include "../lcd/lcd.h"
#include "../lcd/geometry.h"
#include "tslib.h"

static u8 flag=0;

static volatile u8 press=0;
static u16 th_x,th_y;

static u8 data_val=0;






static void enable_timer()
{

	flag=1;
}

static void disable_timer()
{
	flag=0;

}

static u8 get_timer_sta()
{
	return flag;

}

void adc_init()
{

	ADCCON |= 1<<14;			//A/D 转换器预分频器使能
	ADCCON |= (49<<6);			//AD预分频值     AD转换时间为5us
	
	ADCCON &= ~(1<<2);			//正常工作模式
	ADCDLY = 60000;				//启动延时   默认时间
	
}

void report(u16 x, u16 y,u8 pre)
{
	if(data_val == 0)
	{
		press = pre;
		th_x = x;
		th_y =y;
		data_val = 1;
	}
}



void wait_up_irq()
{
	ADCTSC = 0x1d3;

}

void wait_down_irq()
{
	ADCTSC = 0xd3;

}


void timer_adc()
{

	if(get_timer_sta())
	{
		ADCTSC = 0;
		ADCTSC |= 1<<2;
		ADCCON |= 1;
	}

}




void get_ts_ADC_dat1(u16 *x, u16 *y,u8 *pre)
{
	u16 i = 50000;
		
	while(!data_val && i)
	{
		i--;
	}
	if(press)
	{
		*x = th_x;
		*y = th_y;
		
	}
	*pre = press;
	data_val = 0;


}

void get_ts_ADC_dat(u16 *x, u16 *y,u8 *pre)
{
		
	while(!data_val);
	if(press)
	{
		*x = th_x;
		*y = th_y;
		
	}
	*pre = press;
	data_val = 0;


}





void delay_m(u32 x)
{
	while(x--);

}




void Touch_ADC_Handler()
{

	static u16 x1,y1,x2,y2;
	int x3,y3;
	static u32 num_x=0,num_y=0;
	static u16 cnt=0;
	static u8 af = 1;

	if(SUBSRCPND & 1<<9)			//触摸中断
	{
		
		if(ADCDAT0 & 1<<15)				//笔尖抬起状态
		{
			disable_timer();			
			wait_down_irq();
			report(0,0,0);
			af = 1;
			num_x=0;
			num_y=0;
			cnt=0;
	
		}
		else			//笔尖落下状态
		{
			ADCTSC = 0;
			ADCTSC |= 1<<2;
			ADCCON |= 1;
			
			
			
		}
		


	
	}


	
	if(SUBSRCPND & 1<<10)		//ADC 中断
	{
		wait_down_irq();
		x1= ADCDAT1&0x3ff;
		y1= ADCDAT0&0x3ff;
		if(af)
		{
			x2= ADCDAT1&0x3ff;
			y2= ADCDAT0&0x3ff;
			af=0;
		}
		
		if(ADCDAT0 & 1<<15)				//笔尖抬起状态
		{
			wait_down_irq();
			disable_timer();
			report(0,0,0);
			af = 1;
			num_x=0;
			num_y=0;
			cnt=0;


		}
		else
		{		
				
				x3 = x1-x2;
				y3 = y1-y2;
				if(x3 < 0 )
					x3=-x3;
				if(y3 < 0 )
					y3 = -y3;
				if(x3 > 100 || y3>100)
				{
					x1 =x2;
					y1 =y2;
				}

#if speed

				report(x1,y1,1);
				enable_timer();
				wait_up_irq();
//				printf("adcx= %d   adcy=%d\n\r",x1,y1);
				
#else
				num_x+=x1;
				num_y+=y1;
				cnt++;
				if(cnt == 8)
				{
					x1 = num_x>>3;
					y1 = num_y>>3;
					num_x=0;
					num_y=0;
					cnt=0;
					report(x1,y1,1);
					enable_timer();
					wait_up_irq();
//					printf("adcx= %d   adcy=%d\n\r",x1,y1);

				}
				else
				{
					delay_m(5000);
					disable_timer();

					ADCTSC = 0;
					ADCTSC |= 1<<2;
					ADCCON |= 1;

				}

#endif

				x2=x1;
				y2=y1;

		}


	}

	SUBSRCPND |= 1<<9;			//清除触摸中断
	SUBSRCPND |= 1<<10;			//清除次级ADC中断
	
	
	
}




void touch_init()
{

	adc_init();
	INTMOD = 0;
	INTSUBMSK &=  ~((1<<9)  |  (1<<10));			//开启TC 和 ADC中断
	Register_IRQ(31,Touch_ADC_Handler);
	ADCDAT0 &= ~(1<<14);			
	ADCDAT1 &= ~(1<<14);

	time0_regeister("touch",timer_adc);
	wait_down_irq();
	
}





















