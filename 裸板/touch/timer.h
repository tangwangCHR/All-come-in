#ifndef _timer_h
#define _timer_h

#define timer0_num  10
typedef void(*timer0_func)(void);



typedef struct timer0
{
	char *name;							//Ҫʵ�ֵĹ��ܵ�����
	timer0_func p_time0_func;			//��ʱ��0ע�ắ����ָ��

}timer0,*p_timer0;



int time0_regeister(char *name , timer0_func p);
void time0_unregesiter(char *name);







void timer0_init(void);




#endif





















