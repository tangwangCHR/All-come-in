

.text
.global _start
_start:


/*
*		关闭看门狗
*
*/

ldr r1,= 0x53000000
mov r0,#0
str r0,[r1]

/*
*			设置时钟    Fclk 400M    AHB 100M    APB 50M
*		
*/



//LOCKTIME =0xFFFFFFFF;

	ldr r0,=0xffffffff
	ldr r1,=0x4c000000
	str r0,[r1]	

	/*/CLKDIVN  =0x5;										主频率400M  AHB 100M   APB 50M  */
	ldr r0,=0x5
	ldr r1,=0x4c000014
	str r0,[r1]	



	mrc p15,0,r0,c1,c0,0
	orr r0,r0,#0xc0000000
	mcr p15,0,r0,c1,c0,0


	//MPLLCON	=(92<<12)|(1<<4)|(1<<0);					输出400Mhz的频率

	ldr r0,=(92<<12)|(1<<4)|(1<<0)
	ldr r1,=0x4c000004
	str r0,[r1] 




/*
*	判断是nor启动还是nand启动
*
*	向0地址写0  返回0   就是nand启动否者就是nor启动
*/

	mov r0,#0
	ldr r1,[r0]			//保存0地址的内容
	str r0,[r0]			//向0地址写0
	ldr r2,[r0]			//读取0地址的内容
	cmp r0,r2
	ldr sp,=0x40000000+4096		//写入栈地址
	moveq sp,#4096
	streq r1,[r0]

	bl usart0_init

	bl SDRAM_init

	bl Copy_text_R_data

	bl Copy_bss


	ldr pc,=main


halt:
	b halt































