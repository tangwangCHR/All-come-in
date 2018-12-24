#ifndef _lcd_controller_h
#define _lcd_controller_h
#include "../s3c2440_soc.h"
#include "lcd.h"


typedef struct lcd_con_opr
{
	char *name;																//选择哪款控制器
	void (*lcd_con_init)(p_lcd_parameter p);								//初始化LCD控制器
	void (*lcd_con_enable)(void );											//使能lcd
	void (*lcd_con_disable)(void );										//关闭lcd
	void (*lcd_con_palette_init)(void);									//初始化调色板



}lcd_con_opr,*p_lcd_con_opr;










int lcd_controller_regesiter(p_lcd_con_opr p);

int select_lcd_controller(u8 *name);

int lcd_controller_init(p_lcd_parameter p);




#endif













