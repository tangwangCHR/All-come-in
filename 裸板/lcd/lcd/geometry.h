#ifndef _geometry_h
#define _geometry_h
#include "../s3c2440_soc.h"




void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u32 color);

void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u32 color);

void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u32 color);










#endif


