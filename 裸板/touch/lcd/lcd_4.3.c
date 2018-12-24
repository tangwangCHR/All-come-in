#include "lcd.h"



#define LCD_FB_BASE 0x33200000

/*
 *	存放lcd的各类参数
*/


lcd_parameter lcd_4_3_par={

			.name 	   = "lcd_4.3",
			.lcd_Pol   = {
						.lcd_DE			=	normal	,			
						.lcd_pixel_vclk =	normal	,
						.lcd_Hsync		=	inverted,
						.lcd_Vsync		=	inverted,
						.lcd_rgb		=	normal	,
						.lcd_pwr		=	normal	,
			},

			.lcd_seq   ={
						.tvclk			=	9,				//单位9MHZ
						.thb			=	2,
						.thp			=	41,
						.thf			=	2,
						.tvb			=	2,
						.tvp			=	10,
						.tvf			=	2,


			},

			.x_pix		= 480			,
			.y_pix		= 272			,
			.bpp		= 16			,
			.fb_base	= LCD_FB_BASE	,

};






