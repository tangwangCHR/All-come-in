#include "s3c2440_lcd_controller.h"
#include "../s3c2440_soc.h"
#include "lcd_controller.h"



/*
 *	��ʼ��lcd������
*/

#define HCLK 		100				//��λMHZ



void s3c2440_soc_lcd_init(p_lcd_parameter p)
{

		u32 clkval;
		u32 bpp;
		u32 pix_adp;			//���ݴ洢��ʽ
		u32 addr;
		s3c2440_soc_lcd_con_pin_init();

		/*	LCDCON1						 
		 *							9MHZ	  100MHZ		
		 *[17:8]  CLKVAL   TFT��VCLK = HCLK / [(CLKVAL + 1) �� 2] ��CLKVAL��0��	
		 *			CLKVAl=HCLK/2VCLK-1  =	4.55    
		 *
		 *[6:5]	PNRMODE		11 = TFT LCD ���
		 *
		 *
		 *[4:1]   BPPMODE		1000 = TFT �� 1 bpp		1001 = TFT �� 2 bpp		1010 = TFT �� 4 bpp
		 *							1011 = TFT �� 8 bpp		1100 = TFT �� 16 bpp	1101 = TFT �� 24 bpp
		 *
		 *[0]		ENVID			0 = ��ֹ��Ƶ����� LCD �����ź�    1 = ������Ƶ����� LCD �����ź�
		 *
		 */

		clkval = (float)(((float)HCLK/(2*p->lcd_seq.tvclk)-1)+0.5);
//		clkval	=5;

		bpp=p->bpp ==8 ? (0xb) : p->bpp ==16 ? (0xc) : 0xd ;



		LCDCON1 = (clkval<<8) | (3<<5 ) | (bpp<<1 );


		/*  LCDCON2
		 *[31:24] VBPD  				tvb
		 *
		 *[23:14] LINEVAL			y�������ش�С
		 *
		 *[13:6] 	VFPD				TFT: Vertical front porch
		 *
		 *[5:0]	VSPW				TFT: Vertical sync pulse width 
		 *
		 */


		LCDCON2 =	((p->lcd_seq.tvb-1) <<24) | ((p->y_pix-1)<<14) | ((p->lcd_seq.tvf-1)  <<6) |  ((p->lcd_seq.tvp-1) <<0);

		/*	LCDCON3
		 *[25:19]		HBPD (TFT)		TFT: Horizontal back porch
		 *
		 *[18:8]		HOZVAL				LCD ����ˮƽ�ߴ�
		 *
		 *[7:0]		HFPD��TFT��		TFT: Horizontal front porch
		 *
		 */


		LCDCON3 |= ((p->lcd_seq.thb-1) << 19) | ((p->x_pix-1)<<8) | ((p->lcd_seq.thf-1) <<0 );
		
		/*	LCDCON4
		 *[7:0]			HSPW��TFT��	TFT: Horizontal sync pulse width
		 *
		 */


		 LCDCON4 |= ((p->lcd_seq.thp-1) <<0);


		 /*		LCDCON5
		  *
		  *	[11]	FRM565		TFT����λѡ�� 16 bpp �����Ƶ���ݵĸ�ʽ		0 = 5:5:5:1��ʽ 		1 = 5:6:5 ��ʽ
		  *
		  *[10]	INVVCLK	0 = VCLK �½���ȡ��Ƶ����     1 = VCLK ������ȡ��Ƶ����
		  *
		  *[9]		INVVLINE  This bit indicates the VLINE/HSYNC pulse polarity   0 = Normal 1 = Inverted
		  *
		  *[8]		INVVFRAME	 STN/TFT: This bit indicates the VFRAME/VSYNC pulse polarity 	0 = Normal 1 = Inverted
		  *
		  *	[7]		INVVD		����Ƶ���ݣ����弫��	0 = Normal 1 = VD is inverted.
		  *
		  *[6]		NVVDEN		TFT: This bit indicates the VDEN signal polarity		0 = normal 1 = inverted
		  *
		  *[5]		INVPWREN	This bit indicates the PWREN signal polarity	0 = normal 1 = inverted
		  *
		  *[1]		BSWP
		  *
		  *	[0]		HWSWP
		  */
			
			pix_adp = 	 p->bpp == 32 ? (0) : \
			             p->bpp == 16 ? (1) : \
			             (1<<1);  /* 8bpp */

		  
			LCDCON5 |= (1<<11) | (p->lcd_Pol.lcd_pixel_vclk <<10) | (p->lcd_Pol.lcd_Hsync <<9) | (p->lcd_Pol.lcd_Vsync <<8) |  \
					   (p->lcd_Pol.lcd_rgb << 7) | (p->lcd_Pol.lcd_DE << 6) | (p->lcd_Pol.lcd_pwr <<5) | (pix_adp <<0);


		/*LCDSADDR1
		 *
		 *[29:21]    LCDBANK	These bits indicate A[30:22] of the bank location for the video buffer in the system memory
		 *
		 *
		 *[20:0]		LCDBASEU	For single-scan LCD : These bits indicate A[21:1] of the start address of the LCD frame buffer
		 *
		 */
			addr = p->fb_base & ~(1<<31);
			
		 
			LCDSADDR1 = (addr >> 1);


		/*LCDSADDR2
		 *
		 *
		 *
		 */

		 addr = p->fb_base + p->x_pix*p->y_pix*p->bpp/8;
		 addr >>=1;
		 addr &= 0x1fffff;

		 LCDSADDR2 =addr;									


}






void s3c2440_soc_lcd_enable()
{

	GPBDAT  |= (1<<0);							 //����lcd����
	LCDCON5 |= 1<<3;							//���� PWREN �ź�
	LCDCON1 |= 1<<0;							//������Ƶ����
	



}

void s3c2440_soc_lcd_disable()
{
	GPBDAT  &= ~(1<<0);							 //�ر�lcd����
	LCDCON5 &= ~(1<<3);							//��ֹPWREN �ź�
	LCDCON1 &= ~(1<<0);							//��ֹ��Ƶ����

}



void s3c2440_soc_lcd_con_pin_init()
{
	/* ��ʼ������ : �������� */
	GPBCON &= ~0x3;
	GPBCON |= 0x01;

	/* LCDר������ */
	GPCCON = 0xaaaaaaaa;
	GPDCON = 0xaaaaaaaa;

	/* PWREN */
	GPGCON |= (3<<8);


}


void s3c2440_soc_palette_init()
{
	u16 i;
	u8 bit = LCDCON1 & 1;
	volatile u32 *p = (volatile u32 *)0X4D000400;
	if(bit)
		LCDCON1 &= ~(1<<0);	
	for(i=0;i<256;i++)
	{

		*p++ = i*10;



	}
	if(bit)
		LCDCON1 |= 1;		

}


lcd_con_opr s3c2440_lcd_con ={

		.name 					= "s3c2440",
		.lcd_con_init 			= s3c2440_soc_lcd_init,
		.lcd_con_enable  		= s3c2440_soc_lcd_enable,
		.lcd_con_disable  		= s3c2440_soc_lcd_disable,
		.lcd_con_palette_init   = s3c2440_soc_palette_init,

};













