#include "font.h"
#include "../s3c2440_soc.h"
#include "framebuff.h"
#include "lcd.h"


#define   font16x16_base	0x100000				//16*16的字库存在norflash 1M的空间
#define   size				16						//默认是16*16字体   size是字体大小

//采用8*16的asc码 显示字符串
extern const unsigned char fontdata_8x16[];
extern p_lcd_parameter glb_lcd_parameter;


//mode 0 颜色非叠加      1	颜色叠加


void lcd_show_char(u16 x,u16 y,char buf,u32 color,u8 mode)
{
	u16 i,j,st=0;
	u8 point;
	st =buf*16;

	
	for(j=y;j<y+16;j++)
	{
		point=fontdata_8x16[st++];
		for(i=x;i<x+8;i++)
		{
			if(mode)
			{
				if(point&0x80)
				{
					DrawPoint(i,j,color);
				}

			}else
			{
				if(point&0x80)
				{
					DrawPoint(i,j,color);
				}else
				{

					DrawPoint(i,j,0);
				}

			}
			point<<=1;
			
		}	

	}
}


//字库基地址是1M


// 根据汉字GBK内码   根据内码获得字库偏移的地址
/*
 *	每个GBK码由2个字节组成，第一个字节为0X81~0XFE
 *	第二个字节分为两部分，一是0X40~0X7E，二是0X80~0XFE
 *
 *	我们把第一个字节代表的意义称为区，那么GBK里面总共有126个区（0XFE-0X81+1）
 *	每个区内有190个汉字（0XFE-0X80+0X7E-0X40+2），总共就有126*190=23940个汉字
 *
 */


u32 lcd_get_hz_offset(u16 addr)
{
	u8 GBKH,GBKL;
	u32 HP;

	GBKH = (addr>>8)&0xff;
	GBKL = addr & 0xff;

	if(GBKL > 0x7f)
	{
		HP=((GBKH-0x81)*190+GBKL-0X41)*(size*2);


	}else if(GBKL < 0x7f)
	{

		HP=((GBKH-0x81)*190+GBKL-0X40)*(size*2);


	}
	HP += font16x16_base;
	return HP;


}




void lcd_show_hz(u16 x,u16 y,u8 *buf,u32 color)
{
	u16 i=0,j=0;
	u16 data=0;
	

	for(j=y;j<y+16;j++)
	{
		data= (*buf<<8) | (*++buf);
		buf++;
		for(i=x;i<x+16;i++)
		{
			if(data&0x8000)
			{
				DrawPoint(i,j,color);

			}
			data<<=1;



		}

	}

}








void lcd_show_str(u16 x,u16 y,u8 *buf,u32 color)
{
	u16 i,j;
	u16 data=0;
	u8 *p;
	if(y>glb_lcd_parameter->y_pix - 10)	return;
	while(*buf)								//根据首地址的数据即可判断是字符串还是汉字
	{
		if(*buf<128)							//显示的是字符串
		{

			if(*buf == '\n')
				y+=16;
			else if(*buf == '\r')
				x=0;
			else
			{
				if(x>glb_lcd_parameter->x_pix)
				{
					x=0;
					y+=16;
				}
				lcd_show_char(x,y,*buf,color,1);
				x+=8;
			}
			buf++;
		}
		else if(*buf>128)					//显示的是汉字   汉字占据两个字节
		{
			data= (*buf<<8) | (*++buf);				//把汉字两个字节的内码拼接成一个半字		作为偏移地址
			buf++;
			p=(u8 *)lcd_get_hz_offset(data);			
			if(x>glb_lcd_parameter->x_pix)
			{
					x=0;
					y+=16;
			}
			lcd_show_hz(x,y,p,color);
			x+=16;

		}
		

	}


}

void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color)
{  

	u16 height,width;
	u16 i,j;	
 	for(j=sy;j<ey;j++)
	{
		for(i=sx;i<ex;i++)
			DrawPoint(i,j,color);
	}		  
}





// 打印32位的hex文件   没有的补0
// 0 颜色非叠加		1颜色叠加
void lcd_printf_hex(u16 x,u16 y,u32 num,u32 color,u8 mode)
{
	u8 i=0;
	u8 data=0;
	lcd_show_str(x,y,"0X",color);
	for(i=x+16;i<x+80;i+=8)
	{
		data = (num&0xf0000000)>>28;
		num<<=4;
		if(data>=10)
		{
			data-=10;
			lcd_show_char(i,y,data+'A',color,mode);

		}else{

			lcd_show_char(i,y,data+'0',color,mode);


		}

	}

}



// 返回m^n次方
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

u8 num_len(u32 x)
{
	u32 i=0;
	while(x>9)
	{
		x/=10;
		i++;
		
	}
	i++;
	return i;	
	
}


void LCD_ShowNum(u16 x,u16 y,u32 num,u32 color)
{         	
	u8 t,temp;
	u8 enshow=0;
	u8 len;
	len =  num_len(num);
	
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				lcd_show_char(x+(size/2)*t,y,' ',color,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	lcd_show_char(x+(size/2)*t,y,temp+'0',color,0); 
	}
} 

extern p_lcd_parameter glb_lcd_parameter;
void lcd_clear()
{
	u32 x,y;
	if(glb_lcd_parameter->bpp == 8)
	{
		unsigned char *p = (unsigned char *)glb_lcd_parameter->fb_base;
		for (x = 0; x < glb_lcd_parameter->x_pix; x++)
			for (y = 0; y <  glb_lcd_parameter->y_pix; y++)
				*p++ = 0;


	}else if(glb_lcd_parameter->bpp == 16)
	{
		unsigned short *p = (unsigned short *)glb_lcd_parameter->fb_base;
		for (x = 0; x < glb_lcd_parameter->x_pix; x++)
			for (y = 0; y <  glb_lcd_parameter->y_pix; y++)
				*p++ = 0;


	}else     //32位bpp
	{
		unsigned int *p = (unsigned int *)glb_lcd_parameter->fb_base;
		for (x = 0; x < glb_lcd_parameter->x_pix; x++)
			for (y = 0; y <  glb_lcd_parameter->y_pix; y++)
				*p++ = 0;


	}


}


















