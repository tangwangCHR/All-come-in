#include "exti.h"
#include "s3c2440_soc.h"


/*		����		�ⲿ�ж�
**		EINT0		EINT2		EINT11		EINT19
**		PF0			PF2			PG3			PG11
**		S2			S3			S4			S5
**		
**/




void exti_init()
{
	//��ʼ��IO��
	GPFCON |= ((2<<0)|(2<<4));			//PF0 PF2  ����Ϊ�ⲿ�ж�ģʽ
	GPGCON |= ((2<<6)|(2<<22));		//PG3 PG11  ����Ϊ�ⲿ�ж�ģʽ

	EXTINT0 |= (7<<0)|(7<<8);			//PF0 PF2    ˫���ش���
	EXTINT1 |= (7<<12);					//PG3 ˫���ش���
	EXTINT2 |= (7<<12);					//PG11 ˫���ش���

	EINTMASK &=~((1<<19)|(1<<11));		//ʹ��EINT11 EINT19�ж�

	//INTMOD  Ĭ��Ϊ0    ��Ϊirq

	INTMSK &= ~((1<<0) | (1<<2) | (1<<5));		//ʹ��EINT0 EINT2 EINT8_23
	//PRIORITY Ĭ��Ϊ0x7F  �ֻ����ȼ�
	 
	

}


void deal_h(u32 val)
{
	if(val==0)
	{
		if(GPFDAT & (1<<0))	//û����
		{
			GPFDAT |= 1<<4;		//�ر�led��
		}else{
	
			GPFDAT &= ~(1<<4);

		}

	}


	if(val==2)
	{
		if(GPFDAT & (1<<2))	//û����
		{
			GPFDAT |= 1<<5;		//�ر�led��
		}else{
	
			GPFDAT &= ~(1<<5);

		}

	}


	if(val==5)
	{
		if(EINTPEND & (1<<11))					//EINT11	
		{
			if(GPGDAT & (1<<3))
			{
				
				GPFDAT |= 1<<6;
			}else{

				GPFDAT &= ~(1<<6);
	
			}
			
		}

		if(EINTPEND & (1<<19))
		{
			if(GPGDAT & (1<<11))
			{
				
				GPFDAT |= 7<<4;
			}else{

				GPFDAT &= ~(7<<4);
	
			}

		}
		EINTPEND |=(1<<val);
	}

	
}




void Exti_handler()
{
	u32 val=INTOFFSET;
	if((val==0) || (val==2) || (val==5) )   
		deal_h(val);
	SRCPND |= (1<<val);
	INTPND |= (1<<val);


}
























