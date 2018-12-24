#ifndef _interrupt_h
#define _interrupt_h


/*	函数名		Register_IRQ
**	功能		注册IRQ中断
**
*/

typedef void(*func)(void);
func Register_irq[32];




void Register_IRQ(int intoffset , func fp);










#endif






















