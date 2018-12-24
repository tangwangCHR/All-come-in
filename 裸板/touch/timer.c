#include "timer.h"
#include "s3c2440_soc.h"
#include "interrupt.h"
#include "lcd/lcd.h"

static timer0 timer0_reg[timer0_num];


void timer0_handler()
{
	u8 i;
	for(i=0;i<timer0_num;i++)
	{
		if(timer0_reg[i].p_time0_func)
			timer0_reg[i].p_time0_func();


	}


}



int time0_regeister(char *name , timer0_func p)
{
	u8 i;
	
	for(i=0;i<timer0_num;i++)
	{
		if(!timer0_reg[i].p_time0_func)					//timer0_reg�ĵ�ַ���ǽṹ�����ֵ��׵�ַ
		{
			timer0_reg[i].name 		 = name;
			timer0_reg[i].p_time0_func  = p;
			return 1;

		}

	}
	return -1;
}

void time0_unregesiter(char *name)
{
	u8 i;
	for(i=0;i<timer0_num;i++)
	{
		if(strcmp(timer0_reg[i].name , name))
		{
			timer0_reg[i].name		    = 0;
			timer0_reg[i].p_time0_func = 0;

		}


	}


}



/*		��ʱ��0������ʱ��Ϊ1M   ��1us��һ����
**		����Ϊ10000
**		10ms �ж�һ��
*/

void timer0_init()
{
	//��ʱ������ʱ��Ƶ�� = PCLK / {Ԥ��Ƶֵ+1} / {��Ƶֵ}   ����ʱ��Ϊ1M
	TCFG0 |=24;						//��ʱ�� 0 �� 1 ��Ԥ��ƵֵΪ99
	TCFG1 &= ~(15<<0);				//��ʱ��0��ƵֵΪ2

	TCNTB0 = 9999;					//����10000
	
	TCON &= ~(1<<2);				//�رձ���
	TCON |=1<<1;					//�����ֶ�����TCNTB0
	TCON &= ~(1<<1);				//�ر��ֶ�����
	TCON |=1<<0;					//������ʱ��0
	TCON |= 1<<3;					//ʹ���Զ���װ��
	

	Register_IRQ(10,timer0_handler);
	
}






















