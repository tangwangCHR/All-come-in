#ifndef _interrupt_h
#define _interrupt_h


/*	������		Register_IRQ
**	����		ע��IRQ�ж�
**
*/

typedef void(*func)(void);
func Register_irq[32];




void Register_IRQ(int intoffset , func fp);










#endif






















