#include "lcd.h"
#include "../s3c2440_soc.h"
#include "lcd_controller.h"


/*
 *		�����²�lcd�Ĵ���    ���ϲ��ṩ�ӿں���
*/




#define lcd_num 10									//֧��10��lcd

p_lcd_parameter lcd_par[lcd_num];
p_lcd_parameter glb_lcd_parameter;

extern p_lcd_con_opr glb_lcd_con;


//һ������1   ���߷���0
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



//�ṩע�ắ�� ע��lcd�ĸ��ֲ���
/*
 *	����-1����ע��ʧ��  >=0�ɹ�
 *
 */

int lcd_regesiter(p_lcd_parameter p)
{
    u8 i=0;
	for(i=0;i<lcd_num;i++)
	{
		if(!(lcd_par[i]))				//�������ڴ�û���õĻ�    ��ע������ڴ�
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
	//ע��lcd

	lcd_regesiter(&lcd_4_3_par);

	//ע��lcd������

	lcd_controller_regesiter(&s3c2440_lcd_con);

	//ѡ��lcd

	select_lcd("lcd_4.3");

	//ѡ��lcd������

	select_lcd_controller("s3c2440");

	//��ʼ��lcd������
	lcd_controller_init(glb_lcd_parameter);


	lcd_enable();

}










