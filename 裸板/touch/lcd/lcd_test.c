#include "lcd.h"
#include "lcd_test.h"
#include "../s3c2440_soc.h"
#include "geometry.h"
#include "font.h"



void lcd_test()
{
	unsigned int fb_base;
	int xres, yres, bpp;
	int x, y;
	unsigned short *p;
	unsigned int *p2;
	


	get_lcd_par(&xres,&yres,&bpp,&fb_base);
	

	
	
	p = (unsigned short *)fb_base;
	for (x = 0; x < xres; x++)
		for (y = 0; y < yres; y++)
			*p++ = 0xf800;
	
	lcd_clear();






	
	
	LCD_DrawRectangle(0,0,479,271,0xf800);
	lcd_show_str(30,30,"明天会更好\n\r Www.xiaomeidv",0xff0000);
	


}



















