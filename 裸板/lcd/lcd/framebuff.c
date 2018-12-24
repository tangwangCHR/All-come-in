#include "framebuff.h"
#include "../s3c2440_soc.h"
#include "lcd.h"



extern p_lcd_parameter glb_lcd_parameter;


u16 convert32bppto16bpp(u32 color)
{
	u32 r,g,b;

	r = (color>>16)&0xff;
	g = (color>>8)&0xff;
	b = color & 0xff;


	r >>= 3;
	g >>= 2;
	b >>= 3;

	return ((r<<11) | (g<<5) | (b));



}


//��ɫ��ʽ  00RRGGBB
// mode 0 �ǵ���      1 ��ɫ����
void DrawPoint(int x,int y,unsigned int color)
{

	unsigned char *p;		//8λbpp
	unsigned short *p1;  	//16λbpp
	unsigned int *p2;		//32λbpp

	unsigned int pixel_base = glb_lcd_parameter->fb_base + glb_lcd_parameter->x_pix*y*glb_lcd_parameter->bpp/8 + x*glb_lcd_parameter->bpp/8;


	switch(glb_lcd_parameter->bpp)
	{
		case 8:
			p  = (unsigned char *)pixel_base; 
			*p = color;
			break;

		case 16:
			p1 = (unsigned short *)pixel_base;
			*p1= convert32bppto16bpp(color);
			break;
		case 32:
			p2  = (unsigned int *)pixel_base; 
			*p2 = color;
			break;			


	}
		

}































