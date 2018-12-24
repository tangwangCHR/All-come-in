#include "tslib.h"
#include "touch.h"
#include "../lcd/framebuff.h"
#include "../lcd/geometry.h"
#include "../lcd/font.h"
#include "../lcd/lcd.h"
#include "../nor_flash.h"


static _touch_para_init touch_para_init;

extern p_lcd_parameter glb_lcd_parameter;


static volatile u16 x,y;









void read_ts_xy(u16 *x, u16 *y)
{
	u8 pre;
	u16 xl,yl;


	if(touch_para_init.flag)
	{
		get_ts_ADC_dat(&xl,&yl,&pre);
	}
	else
	{
		get_ts_ADC_dat1(&xl,&yl,&pre);
	}
	if(pre)
	{
		*x = touch_para_init.kx * (xl - touch_para_init.xlc) + touch_para_init.xc;
		*y = touch_para_init.ky * (yl - touch_para_init.ylc) + touch_para_init.yc;
	}
	
}


void touch_data_init()
{
	u8 pre=0,i=0;
	int s1,s2,s3,s4,ts1,ts2;
	u16 ax,ay,bx,by,cx,cy,dx,dy,ex,ey;
	touch_para_init.flag=1;

	touch_para_init.x[0] = 50;
	touch_para_init.x[1] = glb_lcd_parameter->x_pix - 50;
	touch_para_init.x[2] = glb_lcd_parameter->x_pix - 50;
	touch_para_init.x[3] = 50;


	touch_para_init.y[0] = 50;
	touch_para_init.y[1] = 50;
	touch_para_init.y[2] = glb_lcd_parameter->y_pix - 50;
	touch_para_init.y[3] = glb_lcd_parameter->y_pix - 50;

	touch_para_init.yc	= glb_lcd_parameter->y_pix/2;
	touch_para_init.xc   = glb_lcd_parameter->x_pix/2;

	
	lcd_clear();

	lcd_show_str(70,70,"请顺序的点击十字",0xff0000);
	draw_cross(50,50,0xff0000);

	do
	{
		get_ts_ADC_dat(&touch_para_init.x1[0],&touch_para_init.y1[0],&pre);

	}while(pre);
	draw_cross(50,50,0);


	draw_cross(glb_lcd_parameter->x_pix - 50,50,0xff0000);
	do
	{
		get_ts_ADC_dat(&touch_para_init.x1[1],&touch_para_init.y1[1],&pre);
	}while(pre);
	draw_cross(glb_lcd_parameter->x_pix - 50,50,0);


	draw_cross(glb_lcd_parameter->x_pix - 50,glb_lcd_parameter->y_pix - 50,0xff0000);
	do
	{
		get_ts_ADC_dat(&touch_para_init.x1[2],&touch_para_init.y1[2],&pre);
	}while(pre);
	draw_cross(glb_lcd_parameter->x_pix - 50,glb_lcd_parameter->y_pix - 50,0);


	draw_cross(50,glb_lcd_parameter->y_pix - 50,0xff0000);
	do
	{
		get_ts_ADC_dat(&touch_para_init.x1[3],&touch_para_init.y1[3],&pre);
	}while(pre);
	draw_cross(50,glb_lcd_parameter->y_pix - 50,0);	



	draw_cross(glb_lcd_parameter->x_pix/2,glb_lcd_parameter->y_pix/2,0xff0000);
	do
	{
		get_ts_ADC_dat(&(touch_para_init.xlc),&(touch_para_init.ylc),&pre);
	}while(pre);
	draw_cross(glb_lcd_parameter->x_pix/2,glb_lcd_parameter->y_pix/2,0);


/*	if(is_swap_xy())
	{
		swap(&(touch_para_init.x1[0]) , &(touch_para_init.y1[0]));
		swap(&(touch_para_init.x1[1]) , &(touch_para_init.y1[1]));
		swap(&(touch_para_init.x1[2]) , &(touch_para_init.y1[2]));
		swap(&(touch_para_init.x1[3]) , &(touch_para_init.y1[3]));
		swap(&(touch_para_init.xc) 	, &(touch_para_init.yc)	);

	}*/

	s1 = touch_para_init.x1[1] - touch_para_init.x1[0];
	s3 = touch_para_init.x1[2] - touch_para_init.x1[3];
	s2 = touch_para_init.y1[2] - touch_para_init.y1[1];
	s4 = touch_para_init.y1[3] - touch_para_init.y1[0];

	ts1 = touch_para_init.x[1] - touch_para_init.x[0];
	ts2 = touch_para_init.y[2] - touch_para_init.y[1];


	touch_para_init.kx = ((double)(2*ts1)) / (s1+s3);
	touch_para_init.ky = ((double)(2*ts2)) / (s2+s4);


//	printf("kx =%f   ky=%f\n\r ",touch_para_init.kx,touch_para_init.ky);
	
/*	Read_nor_flash(0x1ffc00,sizeof(_touch_para_init),((u8 *)(&touch_para_init)));
	read_ts_xy_test(&ax,&ay,touch_para_init.x1[0],touch_para_init.y1[0]);
	read_ts_xy_test(&bx,&by,touch_para_init.x1[1],touch_para_init.y1[1]);
	read_ts_xy_test(&cx,&cy,touch_para_init.x1[2],touch_para_init.y1[2]);
	read_ts_xy_test(&dx,&dy,touch_para_init.x1[3],touch_para_init.y1[3]);
	read_ts_xy_test(&ex,&ey,touch_para_init.xlc,touch_para_init.ylc);
	printf("A: ax = %d  adcx=%d   ay= %d adcy=%d\n\r",ax,touch_para_init.x1[0],ay,touch_para_init.y1[0]);
	printf("B: bx = %d  adcx=%d   by= %d adcy=%d\n\r",bx,touch_para_init.x1[1],by,touch_para_init.y1[1]);
	printf("C: cx = %d  adcx=%d   cy= %d adcy=%d\n\r",cx,touch_para_init.x1[2],cy,touch_para_init.y1[2]);
	printf("D: dx = %d  adcx=%d   dy= %d adcy=%d\n\r",dx,touch_para_init.x1[3],dy,touch_para_init.y1[3]);
	printf("E: ex = %d  adcx=%d   ey= %d adcy=%d\n\r",ex,touch_para_init.xlc,ey,touch_para_init.ylc);*/

	TCON &= ~1;
	touch_para_init.flag = 0;
	nand_erase(0x3200000,1);

	nand_write(0x3200000,((u8 *)(&touch_para_init)),sizeof(_touch_para_init));
	lcd_show_str(70,90,"校准完毕",0xff0000);
					
	lcd_clear();
	TCON |=1<<0;

	 

}




//数据存在nandflash的50M的地方
void is_ts_updat()
{
	
    u32 c;
    touch_init();
	nand_init();
	TCON &= ~1;
	printf("size = %d",sizeof(_touch_para_init));
	nand_read(0x3200000,((u8 *)(&touch_para_init)),sizeof(_touch_para_init));

	TCON |=1<<0;
	if(touch_para_init.flag)
	{
	
		touch_data_init();

	}

	

}














