
#ifndef _s3c2440_soc_h
#define _s3c2440_soc_h

#define u32 unsigned int
#define u8 unsigned char





#define _REG(x) (*(volatile unsigned int *)(x))





/*****************************  GPIO口  *******************************************************/

#define    GPACON                           _REG(0x56000000)
#define    GPADAT                           _REG(0x56000004)

#define    GPBCON                           _REG(0x56000010)
#define    GPBDAT                           _REG(0x56000014)
#define    GPBUP                            _REG(0x56000018)

#define    GPCCON                           _REG(0x56000020)
#define    GPCDAT                           _REG(0x56000024)
#define    GPCUP                            _REG(0x56000028)

#define    GPDCON                           _REG(0x56000030)
#define    GPDDAT                           _REG(0x56000034)
#define    GPDUP                            _REG(0x56000038)

#define    GPECON                           _REG(0x56000040)
#define    GPEDAT                           _REG(0x56000044)
#define    GPEUP                            _REG(0x56000048)


#define    GPFCON                           _REG(0x56000050)
#define    GPFDAT                           _REG(0x56000054)
#define    GPFUP                            _REG(0x56000058)

#define    GPGCON                           _REG(0x56000060)
#define    GPGDAT                           _REG(0x56000064)
#define    GPGUP                            _REG(0x56000068)

#define    GPHCON                           _REG(0x56000070)
#define    GPHDAT                           _REG(0x56000074)
#define    GPHUP                            _REG(0x56000078)

#define    GPJCON                           _REG(0x56000080)
#define    GPJDAT                           _REG(0x56000084)
#define    GPJUP                            _REG(0x56000088)





/*****************************  系统时钟  *******************************************************/





#define    LOCKTIME                          _REG(0x4C000000)	//地址0x4C000000	锁定时间计数寄存器（LOCKTIME）
#define    MPLLCON                           _REG(0x4C000004)	//PLL 控制寄存器（MPLLCON 和 UPLLCON）
#define    UPLLCON                           _REG(0x4C000008)	//PLL 控制寄存器（MPLLCON 和 UPLLCON）
#define    CLKCON                            _REG(0x4C00000C)		//时钟控制寄存器（CLKCON）
#define    CLKSLOW                           _REG(0x4C000010)	//时钟慢速控制（CLKSLOW）寄存器
#define    CLKDIVN                           _REG(0x4C000014)	//时钟分频控制（CLKDIVN）寄存器
#define    CAMDIVN                           _REG(0x4C000018)	//摄像头时钟分频（CAMDIVN）寄存器


/*****************************  串口  *******************************************************/


#define    ULCON0                            _REG(0x50000000)	//UART 线路控制寄存器
#define    ULCON1                          	  _REG(0x50004000)
#define    ULCON2                            _REG(0x50008000)

#define    UCON0                             _REG(0x50000004)		//UART 控制寄存器
#define    UCON1                             _REG(0x50004004)
#define    UCON2                             _REG(0x50008004)


#define    UFCON0                            _REG(0x50000008)	//UART FIFO 控制寄存器
#define    UFCON1                            _REG(0x50004008)
#define    UFCON2                            _REG(0x50008008)


#define    UMCON0                            _REG(0x5000000c)	//UART MODEM 控制寄存器
#define    UMCON1                            _REG(0x5000400c)


#define    UTRSTAT0                          _REG(0x50000010)	//UART TX/RX 状态寄存器
#define    UTRSTAT1                          _REG(0x50004010)
#define    UTRSTAT2                          _REG(0x50008010)

#define    UERSTAT0                          _REG(0x50000014)	//UART 错误状态寄存器
#define    UERSTAT1                          _REG(0x50004014)
#define    UERSTAT2                          _REG(0x50008014)


#define    UFSTAT0                           _REG(0x50000018)	//UART FIFO 状态寄存器
#define    UFSTAT1                           _REG(0x50004018)
#define    UFSTAT2                           _REG(0x50008018)

#define    UMSTAT0                           _REG(0x5000001c)	//UART MODEM 状态寄存器
#define    UMSTAT1                           _REG(0x5000401c)


#define    UTXH0                            _REG(0x50000020)	//UART 发送缓冲寄存器（保持寄存器和 FIFO 寄存器）
#define    UTXH1                            _REG(0x50004020)	//工作在小端模式
#define    UTXH2                            _REG(0x50008020)

/*

#define    UTXH0                            _REG(0x50000023)	//UART 发送缓冲寄存器（保持寄存器和 FIFO 寄存器）
#define    UTXH1                            _REG(0x50004023)	//工作在大端模式
#define    UTXH2                            _REG(0x50008023)

*/


#define    URXH0                            _REG(0x50000024)	//UART 接收缓冲寄存器（保持寄存器和 FIFO 寄存器）
#define    URXH1                            _REG(0x50004024)	//工作在小端模式
#define    URXH2                            _REG(0x50008024)


/*

#define    URXH0                            _REG(0x50000027)	//UART 接收缓冲寄存器（保持寄存器和 FIFO 寄存器）
#define    URXH1                            _REG(0x50004027)	//工作在大端模式
#define    URXH2                            _REG(0x50008027)

*/

#define    UBRDIV0                           _REG(0x50000028)	//UART 波特率分频寄存器
#define    UBRDIV1                           _REG(0x50004028)	//
#define    UBRDIV2                           _REG(0x50008028)
























#endif

































