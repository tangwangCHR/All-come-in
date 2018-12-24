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
































