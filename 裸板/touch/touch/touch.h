#ifndef _touch_h
#define _touch_h
#include "../s3c2440_soc.h"


#define speed 1					// 1ʶ���ٶȿ쵫����ô׼ȷ    0ʶ���ٶ�����׼ȷ��




void touch_init(void);

void delay_m(u32 x);



void get_ts_ADC_dat(u16 *x, u16 *y,u8 *pre);













#endif
















