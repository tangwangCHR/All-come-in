#include "led.h"
#include "s3c2440_soc.h"
#include "usart.h"
#include  "my_printf.h"
#include "nand_flash.h"
#include "nor_flash.h"





int main(void)
{


	led_init();
	exti_init();
	nand_init();
	while(1)
	{

		nand_flash_test();


	}


	return 0;

}





























