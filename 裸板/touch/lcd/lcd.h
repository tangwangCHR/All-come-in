#ifndef _lcd_h
#define _lcd_h
#include "../s3c2440_soc.h"







enum 
{
	normal=0,								//����ģʽ					
	inverted=1								//��ת

};



typedef struct lcd_opr				//���²�lcd�ṩͳһ�ĳ�ʼ���ӿ�
{
	void (*lcd_init)(void);				


}lcd_opr,*p_lcd_opr;


typedef struct lcd_Polarity						//LCD���ŵ�һЩ����
{
	u8 lcd_DE;										//����ʹ�����ŵļ���     Data Enable
	u8 lcd_pixel_vclk;								//����ʱ�ӵļ���			
	u8 lcd_Hsync;									//ˮƽͬ���źŵļ���
	u8 lcd_Vsync;									//��ֱͬ���źŵļ���
	u8 lcd_rgb;										//��Ƶ�������弫��
	u8 lcd_pwr;										//��Դ�źż���

}lcd_Polarity,*p_lcd_Polarity;


typedef struct lcd_lcd_sequential
{
	u32 tvclk;										//����ʱ��Ƶ��		Clock cycle
	u32 thb;										//��ߺڿ�			Horizontal Back porch		
	u32 thp;										//ˮƽ������		Horizontal Pulse width
	u32 thf;										//�ұߺڿ�			Horizontal Front porch			�ٹ�thfʱ�� hsync�Żᵽ��
	u32 tvb;										//�ϱߺڿ�			Vertical Back porch
	u32 tvp;										//��ֱ������		Vertical Pulse width
	u32 tvf;										//�±ߺڿ�			Vertical Front porch

}lcd_sequential,*p_lcd_sequential;


typedef struct lcd_parameter					//LCD��һЩ����
{
	u8 *name;										//LCD������    ѡ����һ��LCD

	lcd_Polarity lcd_Pol;							//LCD�����ż���
	lcd_sequential lcd_seq;							//LCDʱ��

	u32 x_pix;										//ˮƽ��������ظ���
	u32 y_pix;										//��ֱ�������ظ���
	u32  bpp;										//�������
	
	u32	fb_base;									// framebuffer�ĵ�ַ
	




}lcd_parameter,*p_lcd_parameter;











int lcd_regesiter(p_lcd_parameter p);
int strcmp(u8 *str1,u8 *str2);
void lcd_enable(void );
void lcd_disable(void );
void lcd_init(void );
void get_lcd_par(u32 *x_pix,u32 *y_pix,u32 *bpp,u32 *fb_base);







#endif














