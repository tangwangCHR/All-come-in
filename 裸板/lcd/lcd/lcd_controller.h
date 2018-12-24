#ifndef _lcd_controller_h
#define _lcd_controller_h
#include "../s3c2440_soc.h"
#include "lcd.h"


typedef struct lcd_con_opr
{
	char *name;																//ѡ���Ŀ������
	void (*lcd_con_init)(p_lcd_parameter p);								//��ʼ��LCD������
	void (*lcd_con_enable)(void );											//ʹ��lcd
	void (*lcd_con_disable)(void );										//�ر�lcd
	void (*lcd_con_palette_init)(void);									//��ʼ����ɫ��



}lcd_con_opr,*p_lcd_con_opr;










int lcd_controller_regesiter(p_lcd_con_opr p);

int select_lcd_controller(u8 *name);

int lcd_controller_init(p_lcd_parameter p);




#endif













