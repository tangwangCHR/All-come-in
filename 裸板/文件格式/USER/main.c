#include "led.h"
#include "s3c2440_soc.h"
#include "usart.h"
#include  "my_printf.h"



//  *++p			先移动指针  后取值
//	 *p++  		先取值，后移动指针

u32 i=0;
char g_A = 'A';
char g_a = 'a';
unsigned int bb=0;

int main(void)
{


	led_init();
	printf("bb = %d\r\n",bb);

	while(1)
	{
		i=500000;
		printf("g_A = %c\r\n",g_A);
		printf("g_a = %c\r\n",g_a);
		g_A++;
		g_a++;
		while(i--);
		


	}


	return 0;

}





























