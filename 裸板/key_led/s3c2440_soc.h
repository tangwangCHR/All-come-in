
#ifndef _s3c2440_soc_h
#define _s3c2440_soc_h

#define u32 unsigned int
#define u8 unsigned char





#define _REG(x) (*(volatile unsigned int *)(x))



/*****************************  GPIO¿Ú  *******************************************************/



#define    GPFCON                           _REG(0x56000050)
#define    GPFDAT                           _REG(0x56000054)
#define    GPFUP                            _REG(0x56000058)

#define    GPGCON                           _REG(0x56000060)
#define    GPGDAT                           _REG(0x56000064)
#define    GPGUP                            _REG(0x56000068)












#endif

































