#include "nand_flash.h"




//�ж���nor��������nand�������������Ƴ���
//1 nand����      0  nor����
unsigned char ISUBOOTCOPY()
{
	volatile unsigned int *p = (volatile unsigned int *)0;
	*p=0x12345678;
	if(*p==0x12345678)			//����nand����
		return 1;
	else
		return 0;



}





void Copy_text_R_data(void)
{
	extern int __code_start,_end;
	volatile unsigned int *code_start = (volatile unsigned int *)&__code_start;
	volatile unsigned int *end = (volatile unsigned int *)&_end;
	volatile unsigned int *src = (volatile unsigned int *)0;


	if(ISUBOOTCOPY())		//nand  ����
	{
		nand_init();
		nand_read((unsigned int)src,*((unsigned char *)code_start),end-code_start);

	}else{
			while(code_start < end)
			{
				*code_start++ = *src++ ;

			}


	}



}


void Copy_bss()
{
	extern int __bss_start,_end;
	volatile unsigned int *bss_start = (volatile unsigned int *)&__bss_start;
	volatile unsigned int *end = (volatile unsigned int *)&_end;
	


	while(bss_start <= end)
	{
		*bss_start++=0;

	}



}

























