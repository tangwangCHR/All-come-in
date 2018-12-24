#include "nand_flash.h"
#include "my_printf.h"
#include "string_utils.h"
#include "s3c2440_soc.h"
#include <string.h>




void nand_init()
{
	NFCONF &= ~(1<<12);
	NFCONF |= ((1<<8) | (0<<4));			//这个和以上是nand时序设置

	/*使能NAND FLASH控制器,初始化ECC，禁止片选*/
	NFCONT = (1<<4) | (1<<1) | (1<<0);


}
void nand_cmd(unsigned char cmd)
{
	volatile int i;
	NFCMMD = cmd;
	for(i=0; i<10; i++);
}

void nand_addr_byte(unsigned char addr)
{
	volatile int i;
	NFADDR = addr;
	for(i=0; i<10; i++);
}



//ENABLE 使能nandflash控制器
//DISABLE  不使能nandflash控制器
void nand_state(u8 sta)
{
	if(sta==ENABLE)
		NFCONT &= ~(1<<1);
	else
		NFCONT |= 1<<1;
}



void Read_id()
{
	u8 str[8];
	u8 i;

	nand_state(ENABLE);
	NFCMMD = 0x90;				
	NFADDR = 0X00;
	str[0] =  NFDATA;
	str[1] =  NFDATA;
	str[2] =  NFDATA;
	str[3] =  NFDATA;
	str[4] =  NFDATA;
	nand_state(DISABLE);



	printf("maker ID: 0x%x  Device Code: 0x%x  \n\r",str[0],str[1]);
	printf("page size :%dKB  block size: %dKB\n\r",1<<(str[3]&0x03),64<<((str[3]>>4)&0x03));
	if(((str[4]>>4)&0x07)>3)
	{
		printf("Plane Size:%dGB\n\r",(64<<((str[4]>>4)&0x07))/1024);

	}else{

		printf("Plane Size:%dMB\n\r",64<<((str[4]>>4)&0x07));

	}


	printf("\n\r");



}


//等待数据是否就位
void nand_ready()
{

	while(!(NFSTAT&1));



}




//行地址是页   列地址是0-2047个byte

void nand_read(u32 addr,u8 *buff,u32 len)
{

	u32 col,row;						//列地址     行地址
	u32 i=0;
	nand_state(ENABLE);
	
	row=addr/2048;
	col=addr%2048;

	while(i<len)
	{
		/* 发出00h命令 */
		NFCMMD = 0x00;

		/* 发出地址 */
		/* col addr */
		NFADDR = (col & 0xff);
		NFADDR = ((col>>8) & 0xff);

		/* row/page addr */
		NFADDR = (row & 0xff);
		NFADDR = ((row>>8) & 0xff);
		NFADDR = ((row>>16) & 0xff);

		/* 发出30h命令 */
		NFCMMD = 0x30;

		nand_ready();
		for (; (col < 2048) && (i < len); col++)			//break只能跳出第一层循环  跳不出第二层循环  for循环里的break能跳出for循环不能跳出while循环
		{
			buff[i++] = NFDATA;
		

		}
		if(i==len);
			break;

		col = 0;
		row++;

		

	}
	
	nand_state(DISABLE);


}



//一次檫除一个扇区
// addr  地址 必须为扇区首地址
//返回   -1代表檫除失败   0檫除成功
char nand_erase(u32 addr,u32 len)
{

	u32 row;						//列地址     行地址
	u8 dat;
	nand_state(ENABLE);
	if(addr%0X20000)
	{
		printf("nand_erase err, addr is not block align\n\r");
		return -1;

	}



	while(len--)
	{
		row = addr/2048;
		NFCMMD = 0x60;
		NFADDR = row&0xff;
		NFADDR = (row>>8)&0xff;
		NFADDR = (row>>16)&0xff;
		NFCMMD = 0xd0;
		nand_ready();
		NFCMMD = 0X70;
		dat = NFDATA;
		if(dat&1)
		{
			printf("nand_erase err");
			return -1;

		}
		else
			addr+=(128*1024);




		
			
	}
	nand_state(DISABLE);

}


void nand_write(u32 addr,u8 *buf,u32 len)
{
	u32 col,row;						//列地址     行地址
	u32 i=0;
	nand_state(ENABLE);
	
	row=addr/2048;
	col=addr%2048;




	/* 发出80h命令 */
	NFCMMD = 0x80;

	/* 发出地址 */
	/* col addr */
	NFADDR = (col & 0xff);
	NFADDR = ((col>>8) & 0xff);

	/* row/page addr */
	NFADDR = (row & 0xff);
	NFADDR = ((row>>8) & 0xff);
	NFADDR = ((row>>16) & 0xff);

	for(;i<len;)
	{

		NFDATA = buf[i++];
		
	}

	NFCMMD = 0x10;
	printf("writing ...\n\r");
	nand_ready();

	NFCMMD = 0x70;
	if(NFDATA&1)
		printf("write error\n\r");
	else
		printf("writing successfully\n\r");



}




void do_read()
{
	u32 addr;
	u8 str[200];
	u8 i,j,t=0,c,m=0;
	volatile unsigned char *p;

	printf("Please enter the address to be read: ");
	addr=get_uint();

	nand_read(addr,str,64);

	for(i=0;i<4;i++)
	{
	
		for(j=0;j<16;j++)
		{
			c=str[t];
			printf("%02x ",c);
			t++;


		}
		printf("   ; ");

		for (j = 0; j < 16; j++)
		{
			/* 后打印字符 */
			if (str[m] < 0x20 || str[m] > 0x7e)  /* 不可视字符 */
				putchar('.');
			else
				putchar(str[m]);
			m++;
			
		}
		printf("\n\r");

	}
	




}


void do_erase()
{
	u32 addr,len;
	
	printf("Please enter the block address to be deleted: ");
	addr=get_uint();

	printf("Please enter the len: ");
	len=get_uint();
	nand_erase(addr,len);
	


}

u32 strslen(u8 *buf)
{
	u32 num=0;
	while('\0' != buf[num++]);

	return num;


}



void do_write()
{
	u8 buf[100];
	u32 addr;

	printf("Please enter the address to write: ");
	addr=get_uint();



	printf("Enter the string to write: ");
	gets(buf);
	printf("\n\r");
	nand_write(addr,buf,strslen(buf)-1);



}


void nand_flash_test()
{
	char c;
	while(1)
	{
		/* 打印菜单, 供我们选择测试内容 */
		printf("[s] Scan  nand flash\n\r");
		printf("[e] Erase nand flash\n\r");
		printf("[w] Write nand flash\n\r");
		printf("[r] Read  nand flash\n\r");
		printf("[q] quit\n\r");
		printf("Enter selection: ");

		c = getchar();
		printf("%c\n\r", c);
		printf("\n\r");
		switch(c)
		{

			case 's':
			case 'S':
			Read_id();
			break;

			case 'e':
			case 'E':
			do_erase();
			break;

			case 'w':
			case 'W':
			do_write();
			break;			

			case 'r':
			case 'R':
			do_read();
			break;	

			case 'q':
			case 'Q':
			return;
			break;


		}










	}










}






