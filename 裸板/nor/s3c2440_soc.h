
#ifndef _s3c2440_soc_h
#define _s3c2440_soc_h

#define u32 unsigned int
#define u8 unsigned char
#define u16 unsigned short





#define _REG(x) (*(volatile unsigned int *)(x))





/*****************************  GPIO��  *******************************************************/

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

#define    GPJCON                           _REG(0x560000d0)
#define    GPJDAT                           _REG(0x560000d4)
#define    GPJUP                            _REG(0x560000d8)



#define    MISCCR                            _REG(0x56000080)			//������ƼĴ���
#define    DCLKCON                           _REG(0x56000084)			//DCLK ���ƼĴ�����DCLKCON��

#define    EXTINT0                           _REG(0x56000088)			//EXTINTn���ⲿ�жϿ��ƼĴ��� n��
#define    EXTINT1                           _REG(0x5600008c)
#define    EXTINT2                           _REG(0x56000090)

#define    EINTFLT0                          _REG(0x56000094)			//EINTFLTn���ⲿ�ж��˲��Ĵ��� n��
#define    EINTFLT1                          _REG(0x56000098)
#define    EINTFLT2                          _REG(0x5600009c)
#define    EINTFLT3                          _REG(0x560000a0)


#define    EINTMASK                          _REG(0x560000a4)			//EINTMASK���ⲿ�ж����μĴ�����

#define    EINTPEND                          _REG(0x560000a8)			//EINTPEND���ⲿ�жϹ���Ĵ�����


#define    GSTATUS0                          _REG(0x560000ac)			//GSTATUSn��ͨ��״̬�Ĵ�����
#define    GSTATUS1                          _REG(0x560000b0)
#define    GSTATUS2                          _REG(0x560000b4)
#define    GSTATUS3                          _REG(0x560000b8)
#define    GSTATUS4                          _REG(0x560000bc)


#define    DSC0                          	  _REG(0x560000c4)			//DSCn������ǿ�ȿ��ƼĴ�����
#define    DSC1                          	  _REG(0x560000c8)

#define    MSLCON                          	  _REG(0x560000cc)			//MSLCON���洢��˯�߿��ƼĴ�����










/*****************************  ϵͳʱ��  *******************************************************/





#define    LOCKTIME                          _REG(0x4C000000)	//��ַ0x4C000000	����ʱ������Ĵ�����LOCKTIME��
#define    MPLLCON                           _REG(0x4C000004)	//PLL ���ƼĴ�����MPLLCON �� UPLLCON��
#define    UPLLCON                           _REG(0x4C000008)	//PLL ���ƼĴ�����MPLLCON �� UPLLCON��
#define    CLKCON                            _REG(0x4C00000C)		//ʱ�ӿ��ƼĴ�����CLKCON��
#define    CLKSLOW                           _REG(0x4C000010)	//ʱ�����ٿ��ƣ�CLKSLOW���Ĵ���
#define    CLKDIVN                           _REG(0x4C000014)	//ʱ�ӷ�Ƶ���ƣ�CLKDIVN���Ĵ���
#define    CAMDIVN                           _REG(0x4C000018)	//����ͷʱ�ӷ�Ƶ��CAMDIVN���Ĵ���


/*****************************  ����  *******************************************************/


#define    ULCON0                            _REG(0x50000000)	//UART ��·���ƼĴ���
#define    ULCON1                          	  _REG(0x50004000)
#define    ULCON2                            _REG(0x50008000)

#define    UCON0                             _REG(0x50000004)		//UART ���ƼĴ���
#define    UCON1                             _REG(0x50004004)
#define    UCON2                             _REG(0x50008004)


#define    UFCON0                            _REG(0x50000008)	//UART FIFO ���ƼĴ���
#define    UFCON1                            _REG(0x50004008)
#define    UFCON2                            _REG(0x50008008)


#define    UMCON0                            _REG(0x5000000c)	//UART MODEM ���ƼĴ���
#define    UMCON1                            _REG(0x5000400c)


#define    UTRSTAT0                          _REG(0x50000010)	//UART TX/RX ״̬�Ĵ���
#define    UTRSTAT1                          _REG(0x50004010)
#define    UTRSTAT2                          _REG(0x50008010)

#define    UERSTAT0                          _REG(0x50000014)	//UART ����״̬�Ĵ���
#define    UERSTAT1                          _REG(0x50004014)
#define    UERSTAT2                          _REG(0x50008014)


#define    UFSTAT0                           _REG(0x50000018)	//UART FIFO ״̬�Ĵ���
#define    UFSTAT1                           _REG(0x50004018)
#define    UFSTAT2                           _REG(0x50008018)

#define    UMSTAT0                           _REG(0x5000001c)	//UART MODEM ״̬�Ĵ���
#define    UMSTAT1                           _REG(0x5000401c)


#define    UTXH0                            _REG(0x50000020)	//UART ���ͻ���Ĵ��������ּĴ����� FIFO �Ĵ�����
#define    UTXH1                            _REG(0x50004020)	//������С��ģʽ
#define    UTXH2                            _REG(0x50008020)

/*

#define    UTXH0                            _REG(0x50000023)	//UART ���ͻ���Ĵ��������ּĴ����� FIFO �Ĵ�����
#define    UTXH1                            _REG(0x50004023)	//�����ڴ��ģʽ
#define    UTXH2                            _REG(0x50008023)

*/


#define    URXH0                            _REG(0x50000024)	//UART ���ջ���Ĵ��������ּĴ����� FIFO �Ĵ�����
#define    URXH1                            _REG(0x50004024)	//������С��ģʽ
#define    URXH2                            _REG(0x50008024)


/*

#define    URXH0                            _REG(0x50000027)	//UART ���ջ���Ĵ��������ּĴ����� FIFO �Ĵ�����
#define    URXH1                            _REG(0x50004027)	//�����ڴ��ģʽ
#define    URXH2                            _REG(0x50008027)

*/

#define    UBRDIV0                           _REG(0x50000028)	//UART �����ʷ�Ƶ�Ĵ���
#define    UBRDIV1                           _REG(0x50004028)	//
#define    UBRDIV2                           _REG(0x50008028)



/*****************************  �洢������  *******************************************************/


#define    BWSCON                           _REG(0x48000000)			//���߿�Ⱥ͵ȴ����ƼĴ�����BWSCON��

#define    BANKCON0                           _REG(0x48000004)		//BANK ���ƼĴ�����BANKCONn��nGCS0 �� nGCS5��
#define    BANKCON1                           _REG(0x48000008)
#define    BANKCON2                           _REG(0x4800000c)
#define    BANKCON3                           _REG(0x48000010)
#define    BANKCON4                           _REG(0x48000014)
#define    BANKCON5                           _REG(0x48000018)


#define    BANKCON6                           _REG(0x4800001C)		//BANK ���ƼĴ�����BANKCONn��nGCS6 �� nGCS7��
#define    BANKCON7                           _REG(0x48000020)


#define    REFRESH                           _REG(0x48000024)		//ˢ�¿��ƼĴ���
#define    BANKSIZE                          _REG(0x48000028)		//Bank ��С�Ĵ���

#define    MRSRB6                            _REG(0x4800002C)		//SDRAM ģʽ �Ĵ�����Ĵ�����MRSR��
#define    MRSRB7                            _REG(0x48000030)




/*****************************  �жϿ�����  *******************************************************/


#define    SRCPND                            _REG(0X4A000000)		//Դ����SRCPND���Ĵ���
#define    INTMOD                            _REG(0X4A000004)		//�ж�ģʽ��INTMOD���Ĵ���
#define    INTMSK                            _REG(0X4A000008)		//�ж����Σ�INTMSK���Ĵ���
#define    PRIORITY                          _REG(0X4A00000c)		//���ȼ��Ĵ�����PRIORITY��
#define    INTPND                            _REG(0X4A000010)		//�жϹ���INTPND���Ĵ���
#define    INTOFFSET                         _REG(0X4A000014)		//�ж�ƫ�ƣ�INTOFFSET���Ĵ���
#define    SUBSRCPND                         _REG(0X4A000018)		//�μ�Դ����SUBSRCPND���Ĵ���
#define    INTSUBMSK                         _REG(0X4A00001c)		//�жϴμ����Σ�INTSUBMSK���Ĵ���



/*****************************  PWM ��ʱ��  *******************************************************/


#define    TCFG0                            _REG(0x51000000)		//��ʱ�����ƼĴ��� 0��TCFG0��
#define    TCFG1                            _REG(0x51000004)		//��ʱ�����ƼĴ��� 1��TCFG1��
#define    TCON                             _REG(0x51000008)		//��ʱ�����ƼĴ��� 1��TCON��
#define    TCNTB0                           _REG(0x5100000c)		//��ʱ�� 0 ��������Ĵ����ͱȽϻ���Ĵ�����TCNTB0/TCMPB0���
#define    TCMPB0                           _REG(0x51000010)		
#define    TCNTO0                           _REG(0x51000014)		//��ʱ�� 0 �������ӼĴ�����TCNTO0��

#define    TCNTB1                           _REG(0x51000018)		//��ʱ�� 1 ��������Ĵ����ͱȽϻ���Ĵ�����TCNTB1/TCMPB1���
#define    TCMPB1                           _REG(0x5100001c)		
#define    TCNTO1                           _REG(0x51000020)		//��ʱ�� 1 �������ӼĴ�����TCNTO1��

#define    TCNTB2                           _REG(0x51000024)		//��ʱ�� 2 ��������Ĵ����ͱȽϻ���Ĵ�����TCNTB2/TCMPB2���
#define    TCMPB2                           _REG(0x51000028)		
#define    TCNTO2                           _REG(0x5100002c)		//��ʱ�� 2 �������ӼĴ�����TCNTO2��

#define    TCNTB3                           _REG(0x51000030)		//��ʱ�� 3 ��������Ĵ����ͱȽϻ���Ĵ�����TCNTB3/TCMPB3���
#define    TCMPB3                           _REG(0x51000034)		
#define    TCNTO3                           _REG(0x51000038)		//��ʱ�� 3 �������ӼĴ�����TCNTO3��

#define    TCNTB4                           _REG(0x5100003c)		//��ʱ�� 4 ��������Ĵ�����TCNTB4���	
#define    TCNTO4                           _REG(0x51000040)		//��ʱ�� 4 �������ӼĴ�����TCNTO4��



























#endif

































