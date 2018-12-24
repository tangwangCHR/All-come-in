#include "led.h"
#include "s3c2440_soc.h"
#include "usart.h"








int main(void)
{
	unsigned char c;
	
	usart0_init();
	puts("Hello, world!\n\r");
	
	while(1)
	{
		c = getchar();
		if (c == '\r')
		{
			putchar('\n');
		}

		if (c == '\n')
		{
			putchar('\r');
		}

		putchar(c);
	}
	return 0;
}






























