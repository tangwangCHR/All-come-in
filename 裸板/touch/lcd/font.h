#ifndef _font_h
#define _font_h
#include "../s3c2440_soc.h"






void lcd_show_char(u16 x,u16 y,char buf,u32 color,u8 mode);


void lcd_show_str(u16 x,u16 y,u8 *buf,u32 color);


void lcd_show_hz(u16 x,u16 y,u8 *buf,u32 color);



void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color);

void lcd_printf_hex(u16 x,u16 y,u32 num,u32 color,u8 mode);

void LCD_ShowNum(u16 x,u16 y,u32 num,u8 num_lenth,u32 color);


void lcd_clear();



#endif








