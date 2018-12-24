#ifndef _tslib_h
#define _tslib_h
#include "../s3c2440_soc.h"



/*  -------------------------------------------
	|	   [1]								   [2]		|
	|		A									B		|
	|													|
	|													|
	|												|
	|						E							|
	|						[XC,YC]					|
	|													|
	|													|
	|		D									C		|
	|		[4]									[3]		|
	--------------------------------------------
*/



/*		�߼��������ɵ��败����ת��������ADֵ
 *
 *		������������ʾ��������ֵ
 *
 */
typedef struct _touch_para_init
{
	u16 flag;		//1 ��ʾ��������Ҫ����   0��ʾ����Ҫ����
	u16 x[4];		//��㶨λx�������������
	u16 y[4];		//��㶨λy�������������
	u16 x1[4];		//��㶨λx������߼�����
	u16 y1[4];		//��㶨λy������߼�����

	double kx;		//���������ı���ϵ��
	double ky;		//���������ı���ϵ��

	u16 xc;			//���Ļ���x������������    xc yc������ʾ�������ĵ�
	u16 yc;			//���Ļ���y������������

	u16 xlc;		//����x������߼�����
	u16 ylc;		//����y������߼�����



}_touch_para_init,p_touch_para_init;










void touch_data_init();



void is_ts_updat();

void read_ts_xy(u16 *x, u16 *y);

void get_ts_ADC_dat1(u16 *x, u16 *y,u8 *pre);


void get_ts_ADC_dat(u16 *x, u16 *y,u8 *pre);




#endif




