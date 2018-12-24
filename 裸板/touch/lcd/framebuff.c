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


//颜色格式  00RRGGBB
// mode 0 非叠加      1 颜色叠加
void DrawPoint(int x,int y,unsigned int color)
{

	unsigned char *p;		//8位bpp
	unsigned short *p1;  	//16位bpp
	unsigned int *p2;		//32位bpp

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































