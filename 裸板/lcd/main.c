#include "led.h"
#include "s3c2440_soc.h"
#include "usart.h"
#include  "my_printf.h"
#include "nand_flash.h"
#include "nor_flash.h"
#include "lcd/font.h"


void delay(u32 x)
{

	while(x--);

}

int main(void)
{
	u32 i;
	u8 str[2];
	led_init();
	exti_init();
	nand_init();
	lcd_init();
	lcd_test();
	while(1)
	{
		for(i=0x8140;i<0xf7fe;i++)
		{
			str[1]=i&0xff;
			str[0]=(i>>8)&0xff;

			lcd_printf_hex(120,110,i,0xf800,0);
			LCD_ShowNum(230,110,i,0xf800);
			lcd_show_str(240,130,str,0xff00);
			
			delay(500000);
			LCD_Color_Fill(240,130,256,146,0);
		}

		

	}


	return 0;

}





























