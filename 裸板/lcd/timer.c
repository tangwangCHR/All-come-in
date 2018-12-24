#include "timer.h"
#include "s3c2440_soc.h"
#include "interrupt.h"





void timer0_handler()
{
	static u8 t=3;
	static u8 m=0;
	m++;
	if(m==100)
	{
		GPFDAT &= ~(7<<4);
		GPFDAT |= t<<4;
		t++;
		if(t==4)
			t=5;
		if(t>6)
			t=3;
		m=0;

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
	TCON |= 1<<3;					//ʹ���Զ���װ��
	TCON &= ~(1<<2);				//�رձ���
	TCON |=1<<1;					//�����ֶ�����TCNTB0
	TCON |=1<<0;					//������ʱ��0
	TCON &= ~(1<<1);				//�ر��ֶ�����


	Register_IRQ(10,timer0_handler);
	
}






















