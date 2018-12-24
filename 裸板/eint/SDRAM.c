#include "SDRAM.h"
#include "s3c2440_soc.h"





//bank6

void SDRAM_init()
{

	BWSCON =0x02000000;		//32位宽 不等待  不适用 UB LB  
	BANKCON6 =0x00018001;		//sdram TRCD 2CLK 9位数据列宽
	REFRESH =0x008004f5;
	BANKSIZE =0xb1;
	MRSRB6 =0x20;




}

/*
void SDRAM_init(void)
{
		BWSCON = 0x22000000;
	
		BANKCON6 = 0x18001;
		BANKCON7 = 0x18001;
	
		REFRESH  = 0x8404f5;
	
		BANKSIZE = 0xb1;
	
		MRSRB6	 = 0x20;
		MRSRB7	 = 0x20;
}

*/



























