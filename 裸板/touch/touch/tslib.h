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



/*		逻辑坐标是由电阻触摸屏转换出来的AD值
 *
 *		物理坐标是显示屏的坐标值
 *
 */
typedef struct _touch_para_init
{
	u16 flag;		//1 表示触摸屏需要更新   0表示不需要更新
	u16 x[4];		//五点定位x方向的物理坐标
	u16 y[4];		//五点定位y方向的物理坐标
	u16 x1[4];		//五点定位x方向的逻辑坐标
	u16 y1[4];		//五点定位y方向的逻辑坐标

	double kx;		//横向伸缩的比例系数
	double ky;		//纵向伸缩的比例系数

	u16 xc;			//中心基点x方向物理坐标    xc yc就是显示屏的中心点
	u16 yc;			//中心基点y方向物理坐标

	u16 xlc;		//中心x方向的逻辑坐标
	u16 ylc;		//中心y方向的逻辑坐标



}_touch_para_init,p_touch_para_init;










void touch_data_init();



void is_ts_updat();

void read_ts_xy(u16 *x, u16 *y);

void get_ts_ADC_dat1(u16 *x, u16 *y,u8 *pre);


void get_ts_ADC_dat(u16 *x, u16 *y,u8 *pre);




#endif




