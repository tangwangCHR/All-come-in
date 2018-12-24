#ifndef _nand_flash_h
#define _nand_flash_h
#include "s3c2440_soc.h"






void nand_init(void);


void nand_flash_test(void);


void nand_read(u32 addr,u8 *buff,u32 len);

void nand_write(u32 addr,u8 *buf,u32 len);










#endif














