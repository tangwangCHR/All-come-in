#include "geometry.h"
#include "framebuff.h"
#include "../s3c2440_soc.h"








void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u32 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x;
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )
	{  
		DrawPoint(uRow,uCol,color);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}  






//»­¾ØÐÎ
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u32 color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}




void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,u32 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             
	while(a<=b)
	{
		DrawPoint(x0+a,y0-b,color);           
 		DrawPoint(x0+b,y0-a,color);                       
		DrawPoint(x0+b,y0+a,color);                          
		DrawPoint(x0+a,y0+b,color);            
		DrawPoint(x0-a,y0+b,color);                 
 		DrawPoint(x0-b,y0+a,color);             
		DrawPoint(x0-a,y0-b,color);                        
  		DrawPoint(x0-b,y0-a,color);                	         
		a++;
		 
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}
















