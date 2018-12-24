#include "led.h"
#include "s3c2440_soc.h"
#include "usart.h"
#include  "my_printf.h"
#include "nand_flash.h"
#include "nor_flash.h"
#include "lcd/font.h"
#include "touch/touch.h"
#include "touch/tslib.h"
#include "exti.h"


void delay(u32 x)
{

	while(x--);

}

int main(void)
{
	u16 x,y;
	led_init();
	timer0_init();
	exti_init();
	nand_init();
	lcd_init();
	lcd_clear();
	is_ts_updat();
	while(1)
	{
		read_ts_xy(&x,&y);
		DrawPoint(x,y,0xffffff);

		if(report_key_sta())
		{
			reset_key_sta();
			touch_data_init();
			
			
		}

	}

	return 0;

}





























