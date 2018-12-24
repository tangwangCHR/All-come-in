#include "exti.h"
#include "s3c2440_soc.h"
#include "interrupt.h"


/*		按键		外部中断
**		EINT0		EINT2		EINT11		EINT19
**		PF0			PF2			PG3			PG11
**		S2			S3			S4			S5
**		
**/










void Exti0_handler()
{
	if(GPFDAT & (1<<0)) //没按下
	{
		GPFDAT |= 1<<4; 	//关闭led灯
	}else{
	
		GPFDAT &= ~(1<<4);
	
	}

}


void Exti2_handler()
{
	if(GPFDAT & (1<<2)) //没按下
	{
		GPFDAT |= 1<<5; 	//关闭led灯
	}else{
	
		GPFDAT &= ~(1<<5);
	
	}

}


void Exti8_23_handler()
{
	if(EINTPEND & (1<<11))					//EINT11	
	{
		if(GPGDAT & (1<<3))
		{
			
			GPFDAT |= 1<<6;
		}else{
	
			GPFDAT &= ~(1<<6);
	
		}
		EINTPEND |=(1<<11);
		
	}

	
	if(EINTPEND & (1<<19))
	{
		if(GPGDAT & (1<<11))
		{
			
			GPFDAT |= 7<<4;
		}else{
	
			GPFDAT &= ~(7<<4);
	
		}
		EINTPEND |=(1<<19);
	}
	

}





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

	 
	Register_IRQ(0,Exti0_handler);				//注册中断
	Register_IRQ(2,Exti2_handler);
	Register_IRQ(5,Exti8_23_handler);

}















