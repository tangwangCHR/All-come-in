

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
*		判读是nor启动还是nand启动
*	如果向0地址写0 返回0  那么就是nand启动否则就是nor启动
*
*
*/
mov r0,#0
ldr r1,[r0]			//先把0地址的内容读出来保存   留待以后恢复0地址的内容
str r0,[r0]			//向0地址写0
ldr r2,[r0]			//读出0地址的内容
cmp r2,r0
ldr sp,=0x40000000+4096
moveq sp,#4096		//nand启动
streq r1,[r0]		//恢复原先的值


bl main



halt:
	b halt




























































