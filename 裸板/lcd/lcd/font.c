#include "font.h"
#include "../s3c2440_soc.h"
#include "framebuff.h"
#include "lcd.h"


#define   font16x16_base	0x100000				//16*16���ֿ����norflash 1M�Ŀռ�
#define   size				16						//Ĭ����16*16����   size�������С

//����8*16��asc�� ��ʾ�ַ���
extern const unsigned char fontdata_8x16[];
extern p_lcd_parameter glb_lcd_parameter;


//mode 0 ��ɫ�ǵ���      1	��ɫ����


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


//�ֿ����ַ��1M


// ���ݺ���GBK����   �����������ֿ�ƫ�Ƶĵ�ַ
/*
 *	ÿ��GBK����2���ֽ���ɣ���һ���ֽ�Ϊ0X81~0XFE
 *	�ڶ����ֽڷ�Ϊ�����֣�һ��0X40~0X7E������0X80~0XFE
 *
 *	���ǰѵ�һ���ֽڴ���������Ϊ������ôGBK�����ܹ���126������0XFE-0X81+1��
 *	ÿ��������190�����֣�0XFE-0X80+0X7E-0X40+2�����ܹ�����126*190=23940������
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
	while(*buf)								//�����׵�ַ�����ݼ����ж����ַ������Ǻ���
	{
		if(*buf<128)							//��ʾ�����ַ���
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
		else if(*buf>128)					//��ʾ���Ǻ���   ����ռ�������ֽ�
		{
			data= (*buf<<8) | (*++buf);				//�Ѻ��������ֽڵ�����ƴ�ӳ�һ������		��Ϊƫ�Ƶ�ַ
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





// ��ӡ32λ��hex�ļ�   û�еĲ�0
// 0 ��ɫ�ǵ���		1��ɫ����
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



// ����m^n�η�
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


	}else     //32λbpp
	{
		unsigned int *p = (unsigned int *)glb_lcd_parameter->fb_base;
		for (x = 0; x < glb_lcd_parameter->x_pix; x++)
			for (y = 0; y <  glb_lcd_parameter->y_pix; y++)
				*p++ = 0;


	}


}


















