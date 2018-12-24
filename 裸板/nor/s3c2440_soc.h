
#ifndef _s3c2440_soc_h
#define _s3c2440_soc_h

#define u32 unsigned int
#define u8 unsigned char
#define u16 unsigned short





#define _REG(x) (*(volatile unsigned int *)(x))





/*****************************  GPIO¿Ú  *******************************************************/

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



#define    MISCCR                            _REG(0x56000080)			//ÔÓÏî¿ØÖÆ¼Ä´æÆ÷
#define    DCLKCON                           _REG(0x56000084)			//DCLK ¿ØÖÆ¼Ä´æÆ÷£¨DCLKCON£©

#define    EXTINT0                           _REG(0x56000088)			//EXTINTn£¨Íâ²¿ÖÐ¶Ï¿ØÖÆ¼Ä´æÆ÷ n£©
#define    EXTINT1                           _REG(0x5600008c)
#define    EXTINT2                           _REG(0x56000090)

#define    EINTFLT0                          _REG(0x56000094)			//EINTFLTn£¨Íâ²¿ÖÐ¶ÏÂË²¨¼Ä´æÆ÷ n£©
#define    EINTFLT1                          _REG(0x56000098)
#define    EINTFLT2                          _REG(0x5600009c)
#define    EINTFLT3                          _REG(0x560000a0)


#define    EINTMASK                          _REG(0x560000a4)			//EINTMASK£¨Íâ²¿ÖÐ¶ÏÆÁ±Î¼Ä´æÆ÷£©

#define    EINTPEND                          _REG(0x560000a8)			//EINTPEND£¨Íâ²¿ÖÐ¶Ï¹ÒÆð¼Ä´æÆ÷£©


#define    GSTATUS0                          _REG(0x560000ac)			//GSTATUSn£¨Í¨ÓÃ×´Ì¬¼Ä´æÆ÷£©
#define    GSTATUS1                          _REG(0x560000b0)
#define    GSTATUS2                          _REG(0x560000b4)
#define    GSTATUS3                          _REG(0x560000b8)
#define    GSTATUS4                          _REG(0x560000bc)


#define    DSC0                          	  _REG(0x560000c4)			//DSCn£¨Çý¶¯Ç¿¶È¿ØÖÆ¼Ä´æÆ÷£©
#define    DSC1                          	  _REG(0x560000c8)

#define    MSLCON                          	  _REG(0x560000cc)			//MSLCON£¨´æ´¢Æ÷Ë¯Ãß¿ØÖÆ¼Ä´æÆ÷£©










/*****************************  ÏµÍ³Ê±ÖÓ  *******************************************************/





#define    LOCKTIME                          _REG(0x4C000000)	//µØÖ·0x4C000000	Ëø¶¨Ê±¼ä¼ÆÊý¼Ä´æÆ÷£¨LOCKTIME£©
#define    MPLLCON                           _REG(0x4C000004)	//PLL ¿ØÖÆ¼Ä´æÆ÷£¨MPLLCON ºÍ UPLLCON£©
#define    UPLLCON                           _REG(0x4C000008)	//PLL ¿ØÖÆ¼Ä´æÆ÷£¨MPLLCON ºÍ UPLLCON£©
#define    CLKCON                            _REG(0x4C00000C)		//Ê±ÖÓ¿ØÖÆ¼Ä´æÆ÷£¨CLKCON£©
#define    CLKSLOW                           _REG(0x4C000010)	//Ê±ÖÓÂýËÙ¿ØÖÆ£¨CLKSLOW£©¼Ä´æÆ÷
#define    CLKDIVN                           _REG(0x4C000014)	//Ê±ÖÓ·ÖÆµ¿ØÖÆ£¨CLKDIVN£©¼Ä´æÆ÷
#define    CAMDIVN                           _REG(0x4C000018)	//ÉãÏñÍ·Ê±ÖÓ·ÖÆµ£¨CAMDIVN£©¼Ä´æÆ÷


/*****************************  ´®¿Ú  *******************************************************/


#define    ULCON0                            _REG(0x50000000)	//UART ÏßÂ·¿ØÖÆ¼Ä´æÆ÷
#define    ULCON1                          	  _REG(0x50004000)
#define    ULCON2                            _REG(0x50008000)

#define    UCON0                             _REG(0x50000004)		//UART ¿ØÖÆ¼Ä´æÆ÷
#define    UCON1                             _REG(0x50004004)
#define    UCON2                             _REG(0x50008004)


#define    UFCON0                            _REG(0x50000008)	//UART FIFO ¿ØÖÆ¼Ä´æÆ÷
#define    UFCON1                            _REG(0x50004008)
#define    UFCON2                            _REG(0x50008008)


#define    UMCON0                            _REG(0x5000000c)	//UART MODEM ¿ØÖÆ¼Ä´æÆ÷
#define    UMCON1                            _REG(0x5000400c)


#define    UTRSTAT0                          _REG(0x50000010)	//UART TX/RX ×´Ì¬¼Ä´æÆ÷
#define    UTRSTAT1                          _REG(0x50004010)
#define    UTRSTAT2                          _REG(0x50008010)

#define    UERSTAT0                          _REG(0x50000014)	//UART ´íÎó×´Ì¬¼Ä´æÆ÷
#define    UERSTAT1                          _REG(0x50004014)
#define    UERSTAT2                          _REG(0x50008014)


#define    UFSTAT0                           _REG(0x50000018)	//UART FIFO ×´Ì¬¼Ä´æÆ÷
#define    UFSTAT1                           _REG(0x50004018)
#define    UFSTAT2                           _REG(0x50008018)

#define    UMSTAT0                           _REG(0x5000001c)	//UART MODEM ×´Ì¬¼Ä´æÆ÷
#define    UMSTAT1                           _REG(0x5000401c)


#define    UTXH0                            _REG(0x50000020)	//UART ·¢ËÍ»º³å¼Ä´æÆ÷£¨±£³Ö¼Ä´æÆ÷ºÍ FIFO ¼Ä´æÆ÷£©
#define    UTXH1                            _REG(0x50004020)	//¹¤×÷ÔÚÐ¡¶ËÄ£Ê½
#define    UTXH2                            _REG(0x50008020)

/*

#define    UTXH0                            _REG(0x50000023)	//UART ·¢ËÍ»º³å¼Ä´æÆ÷£¨±£³Ö¼Ä´æÆ÷ºÍ FIFO ¼Ä´æÆ÷£©
#define    UTXH1                            _REG(0x50004023)	//¹¤×÷ÔÚ´ó¶ËÄ£Ê½
#define    UTXH2                            _REG(0x50008023)

*/


#define    URXH0                            _REG(0x50000024)	//UART ½ÓÊÕ»º³å¼Ä´æÆ÷£¨±£³Ö¼Ä´æÆ÷ºÍ FIFO ¼Ä´æÆ÷£©
#define    URXH1                            _REG(0x50004024)	//¹¤×÷ÔÚÐ¡¶ËÄ£Ê½
#define    URXH2                            _REG(0x50008024)


/*

#define    URXH0                            _REG(0x50000027)	//UART ½ÓÊÕ»º³å¼Ä´æÆ÷£¨±£³Ö¼Ä´æÆ÷ºÍ FIFO ¼Ä´æÆ÷£©
#define    URXH1                            _REG(0x50004027)	//¹¤×÷ÔÚ´ó¶ËÄ£Ê½
#define    URXH2                            _REG(0x50008027)

*/

#define    UBRDIV0                           _REG(0x50000028)	//UART ²¨ÌØÂÊ·ÖÆµ¼Ä´æÆ÷
#define    UBRDIV1                           _REG(0x50004028)	//
#define    UBRDIV2                           _REG(0x50008028)



/*****************************  ´æ´¢¿ØÖÆÆ÷  *******************************************************/


#define    BWSCON                           _REG(0x48000000)			//×ÜÏß¿í¶ÈºÍµÈ´ý¿ØÖÆ¼Ä´æÆ÷£¨BWSCON£©

#define    BANKCON0                           _REG(0x48000004)		//BANK ¿ØÖÆ¼Ä´æÆ÷£¨BANKCONn£ºnGCS0 ÖÁ nGCS5£©
#define    BANKCON1                           _REG(0x48000008)
#define    BANKCON2                           _REG(0x4800000c)
#define    BANKCON3                           _REG(0x48000010)
#define    BANKCON4                           _REG(0x48000014)
#define    BANKCON5                           _REG(0x48000018)


#define    BANKCON6                           _REG(0x4800001C)		//BANK ¿ØÖÆ¼Ä´æÆ÷£¨BANKCONn£ºnGCS6 ÖÁ nGCS7£©
#define    BANKCON7                           _REG(0x48000020)


#define    REFRESH                           _REG(0x48000024)		//Ë¢ÐÂ¿ØÖÆ¼Ä´æÆ÷
#define    BANKSIZE                          _REG(0x48000028)		//Bank ´óÐ¡¼Ä´æÆ÷

#define    MRSRB6                            _REG(0x4800002C)		//SDRAM Ä£Ê½ ¼Ä´æÆ÷×é¼Ä´æÆ÷£¨MRSR£©
#define    MRSRB7                            _REG(0x48000030)




/*****************************  ÖÐ¶Ï¿ØÖÆÆ÷  *******************************************************/


#define    SRCPND                            _REG(0X4A000000)		//Ô´¹ÒÆð£¨SRCPND£©¼Ä´æÆ÷
#define    INTMOD                            _REG(0X4A000004)		//ÖÐ¶ÏÄ£Ê½£¨INTMOD£©¼Ä´æÆ÷
#define    INTMSK                            _REG(0X4A000008)		//ÖÐ¶ÏÆÁ±Î£¨INTMSK£©¼Ä´æÆ÷
#define    PRIORITY                          _REG(0X4A00000c)		//ÓÅÏÈ¼¶¼Ä´æÆ÷£¨PRIORITY£©
#define    INTPND                            _REG(0X4A000010)		//ÖÐ¶Ï¹ÒÆð£¨INTPND£©¼Ä´æÆ÷
#define    INTOFFSET                         _REG(0X4A000014)		//ÖÐ¶ÏÆ«ÒÆ£¨INTOFFSET£©¼Ä´æÆ÷
#define    SUBSRCPND                         _REG(0X4A000018)		//´Î¼¶Ô´¹ÒÆð£¨SUBSRCPND£©¼Ä´æÆ÷
#define    INTSUBMSK                         _REG(0X4A00001c)		//ÖÐ¶Ï´Î¼¶ÆÁ±Î£¨INTSUBMSK£©¼Ä´æÆ÷



/*****************************  PWM ¶¨Ê±Æ÷  *******************************************************/


#define    TCFG0                            _REG(0x51000000)		//¶¨Ê±Æ÷ÅäÖÆ¼Ä´æÆ÷ 0£¨TCFG0£©
#define    TCFG1                            _REG(0x51000004)		//¶¨Ê±Æ÷ÅäÖÆ¼Ä´æÆ÷ 1£¨TCFG1£©
#define    TCON                             _REG(0x51000008)		//¶¨Ê±Æ÷¿ØÖÆ¼Ä´æÆ÷ 1£¨TCON£©
#define    TCNTB0                           _REG(0x5100000c)		//¶¨Ê±Æ÷ 0 ¼ÆÊý»º³å¼Ä´æÆ÷ºÍ±È½Ï»º³å¼Ä´æÆ÷£¨TCNTB0/TCMPB0£©©
#define    TCMPB0                           _REG(0x51000010)		
#define    TCNTO0                           _REG(0x51000014)		//¶¨Ê±Æ÷ 0 ¼ÆÊý¼àÊÓ¼Ä´æÆ÷£¨TCNTO0£©

#define    TCNTB1                           _REG(0x51000018)		//¶¨Ê±Æ÷ 1 ¼ÆÊý»º³å¼Ä´æÆ÷ºÍ±È½Ï»º³å¼Ä´æÆ÷£¨TCNTB1/TCMPB1£©©
#define    TCMPB1                           _REG(0x5100001c)		
#define    TCNTO1                           _REG(0x51000020)		//¶¨Ê±Æ÷ 1 ¼ÆÊý¼àÊÓ¼Ä´æÆ÷£¨TCNTO1£©

#define    TCNTB2                           _REG(0x51000024)		//¶¨Ê±Æ÷ 2 ¼ÆÊý»º³å¼Ä´æÆ÷ºÍ±È½Ï»º³å¼Ä´æÆ÷£¨TCNTB2/TCMPB2£©©
#define    TCMPB2                           _REG(0x51000028)		
#define    TCNTO2                           _REG(0x5100002c)		//¶¨Ê±Æ÷ 2 ¼ÆÊý¼àÊÓ¼Ä´æÆ÷£¨TCNTO2£©

#define    TCNTB3                           _REG(0x51000030)		//¶¨Ê±Æ÷ 3 ¼ÆÊý»º³å¼Ä´æÆ÷ºÍ±È½Ï»º³å¼Ä´æÆ÷£¨TCNTB3/TCMPB3£©©
#define    TCMPB3                           _REG(0x51000034)		
#define    TCNTO3                           _REG(0x51000038)		//¶¨Ê±Æ÷ 3 ¼ÆÊý¼àÊÓ¼Ä´æÆ÷£¨TCNTO3£©

#define    TCNTB4                           _REG(0x5100003c)		//¶¨Ê±Æ÷ 4 ¼ÆÊý»º³å¼Ä´æÆ÷£¨TCNTB4£©©	
#define    TCNTO4                           _REG(0x51000040)		//¶¨Ê±Æ÷ 4 ¼ÆÊý¼àÊÓ¼Ä´æÆ÷£¨TCNTO4£©



























#endif

































