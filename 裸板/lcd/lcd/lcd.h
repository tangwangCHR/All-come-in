#ifndef _lcd_h
#define _lcd_h
#include "../s3c2440_soc.h"







enum 
{
	normal=0,								//正常模式					
	inverted=1								//反转

};



typedef struct lcd_opr				//向下层lcd提供统一的初始化接口
{
	void (*lcd_init)(void);				


}lcd_opr,*p_lcd_opr;


typedef struct lcd_Polarity						//LCD引脚的一些极性
{
	u8 lcd_DE;										//数据使能引脚的极性     Data Enable
	u8 lcd_pixel_vclk;								//像素时钟的极性			
	u8 lcd_Hsync;									//水平同步信号的极性
	u8 lcd_Vsync;									//垂直同步信号的极性
	u8 lcd_rgb;										//视频数据脉冲极性
	u8 lcd_pwr;										//电源信号极性

}lcd_Polarity,*p_lcd_Polarity;


typedef struct lcd_lcd_sequential
{
	u32 tvclk;										//像素时钟频率		Clock cycle
	u32 thb;										//左边黑框			Horizontal Back porch		
	u32 thp;										//水平脉冲宽度		Horizontal Pulse width
	u32 thf;										//右边黑框			Horizontal Front porch			再过thf时间 hsync才会到来
	u32 tvb;										//上边黑框			Vertical Back porch
	u32 tvp;										//垂直脉冲宽度		Vertical Pulse width
	u32 tvf;										//下边黑框			Vertical Front porch

}lcd_sequential,*p_lcd_sequential;


typedef struct lcd_parameter					//LCD的一些参数
{
	u8 *name;										//LCD的名字    选择那一款LCD

	lcd_Polarity lcd_Pol;							//LCD的引脚极性
	lcd_sequential lcd_seq;							//LCD时序

	u32 x_pix;										//水平方向的像素个数
	u32 y_pix;										//垂直方向像素个数
	u32  bpp;										//像素深度
	
	u32	fb_base;									// framebuffer的地址
	




}lcd_parameter,*p_lcd_parameter;











int lcd_regesiter(p_lcd_parameter p);
int strcmp(u8 *str1,u8 *str2);
void lcd_enable(void );
void lcd_disable(void );
void lcd_init(void );
void get_lcd_par(u32 *x_pix,u32 *y_pix,u32 *bpp,u32 *fb_base);







#endif














