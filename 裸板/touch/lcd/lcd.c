#include "lcd.h"
#include "../s3c2440_soc.h"
#include "lcd_controller.h"


/*
 *		屏蔽下层lcd的代码    向上层提供接口函数
*/




#define lcd_num 10									//支持10种lcd

p_lcd_parameter lcd_par[lcd_num];
p_lcd_parameter glb_lcd_parameter;

extern p_lcd_con_opr glb_lcd_con;


//一样返回1   否者返回0
int strcmp(u8 *str1,u8 *str2)
{
	int i=0;
	while(*str1++ != '\0')
	{
		str2 ++;
		if(*str1 != *str2)
			return 0;  


	}
	return 1;

}



void get_lcd_par(u32 *x_pix,u32 *y_pix,u32 *bpp,u32 *fb_base)
{
	*x_pix 		= glb_lcd_parameter->x_pix;
	*y_pix 		= glb_lcd_parameter->y_pix;
	*bpp   		= glb_lcd_parameter->bpp;
	*fb_base	= glb_lcd_parameter->fb_base;



}



//提供注册函数 注册lcd的各种参数
/*
 *	返回-1代表注册失败  >=0成功
 *
 */

int lcd_regesiter(p_lcd_parameter p)
{
    u8 i=0;
	for(i=0;i<lcd_num;i++)
	{
		if(!(lcd_par[i]))				//如果这个内存没被用的话    则注册这个内存
		{

			lcd_par[i]=p;
			return i;

		}

	}
	return -1;
}


int select_lcd(u8 *name)
{
	u8 i;
	for(i=0;i<lcd_num;i++)
	{

		if((lcd_par[i]) && strcmp(lcd_par[i]->name,name))
		{
			glb_lcd_parameter = lcd_par[i];
			return i;

		}


	}
	return -1;

}


void lcd_enable()
{
	if(glb_lcd_con)
	{
		glb_lcd_con->lcd_con_enable();

	}


}

void lcd_disable()
{
	if(glb_lcd_con)
	{
		glb_lcd_con->lcd_con_disable();

	}

}

extern lcd_parameter lcd_4_3_par;
extern lcd_con_opr s3c2440_lcd_con;
void lcd_init()
{
	//注册lcd

	lcd_regesiter(&lcd_4_3_par);

	//注册lcd控制器

	lcd_controller_regesiter(&s3c2440_lcd_con);

	//选择lcd

	select_lcd("lcd_4.3");

	//选择lcd控制器

	select_lcd_controller("s3c2440");

	//初始化lcd控制器
	lcd_controller_init(glb_lcd_parameter);


	lcd_enable();

}










