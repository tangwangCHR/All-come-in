#include "exti.h"
#include "s3c2440_soc.h"


/*		按键		外部中断
**		EINT0		EINT2		EINT11		EINT19
**		PF0			PF2			PG3			PG11
**		S2			S3			S4			S5
**		
**/




void exti_init()
{
	//初始化IO口
	GPFCON |= ((2<<0)|(2<<4));			//PF0 PF2  设置为外部中断模式
	GPGCON |= ((2<<6)|(2<<22));		//PG3 PG11  设置为外部中断模式

	EXTINT0 |= (7<<0)|(7<<8);			//PF0 PF2    双边沿触发
	EXTINT1 |= (7<<12);					//PG3 双边沿触发
	EXTINT2 |= (7<<12);					//PG11 双边沿触发

	EINTMASK &=~((1<<19)|(1<<11));		//使能EINT11 EINT19中断

	//INTMOD  默认为0    即为irq

	INTMSK &= ~((1<<0) | (1<<2) | (1<<5));		//使能EINT0 EINT2 EINT8_23
	//PRIORITY 默认为0x7F  轮换优先级
	 
	

}


void deal_h(u32 val)
{
	if(val==0)
	{
		if(GPFDAT & (1<<0))	//没按下
		{
			GPFDAT |= 1<<4;		//关闭led灯
		}else{
	
			GPFDAT &= ~(1<<4);

		}

	}


	if(val==2)
	{
		if(GPFDAT & (1<<2))	//没按下
		{
			GPFDAT |= 1<<5;		//关闭led灯
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
























