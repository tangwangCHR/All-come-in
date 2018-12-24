#include "nor_flash.h"
#include "my_printf.h"
#include "string_utils.h"
#include "s3c2440_soc.h"





void nor_flash_cmd(u32 addr,u32 dat)
{
	//LADDR1--LADDR20      接到   A0--A19
	//所以按照说明书cpu给norflash发送地址位时要左移一位
	//norflash链接到块0   其地址重0开始
	volatile u16 *p = (volatile u16 *)(addr<<1);
	*p=dat;
	
}

u32 nor_dat(u32 addr)
{
	
	volatile u16 *p = (volatile u16 *)(addr<<1);
	return *p;

}


void wait_ready(u32 addr)				
{
	u32 pre,val;
	pre=nor_dat(addr>>1);				//上次数据
	val=nor_dat(addr>>1);				//本次数据
	while((pre & (1<<6))!=(val & (1<<6)))		//在数据正在写 读 或者删除的过程中DQ6电平状态是来回翻转的
	{

		pre=val;
		val=nor_dat(addr>>1);

	}
}



void Scan_nor_flash()
{
	//打印厂家ID和设备ID
	u32 Manifacture_ID;
	u32 Device_ID;
	u8 str[4];					//查询唯一的ASCII字符串“QRY”
	u32 Device_size;			//驱动内存大小
	u8 region_nums;			//块区域的数量
	u8 i,j;
	u32 start_addrs=0;
	u32 block_nums,block_size;
	u8 region_info_base=0x2d;
	
	nor_flash_cmd(0x555,0xaa);
	nor_flash_cmd(0x2aa,0x55);
	nor_flash_cmd(0x555,0x90);
	Manifacture_ID=nor_dat(0);
	Device_ID=nor_dat(1);
	
	switch(Device_ID)
	{
		case 0x22c4:
			printf("Device ID : MX29LV160DT: 0x22C4\n\r");
			break;
		case 0x2249:
			printf("Device ID : MX29LV160DT: 0x2249\n\r");
			break;
		default:
			break;

	}

	nor_flash_cmd(0,0xf0);			//复位
	//进入CFI模式
	/*   Flash 存储器接口还有两个标准：CFI和JEDEC。CFI为公共Flash接口[Common Flash Interface]，用来帮助程序
	**   从Flash芯片中获取操作方式信息(发送命令，从nor flash的芯片里获取器件的各种参数，换芯片时，不需修改内核代
	**		而不用在程序中硬编码Flash的ID
	*/
	nor_flash_cmd(0x55,0x98);
		
	//查询唯一的ASCII字符串“QRY”
	str[0]=nor_dat(0x10);
	str[1]=nor_dat(0x11);
	str[2]=nor_dat(0x12);
	str[3]='\0';
	printf("str=%s\n\r",str);
	
	Device_size=1<<nor_dat(0x27);				//Device size = 2的n次方 in number of bytes (MX29LV160D)



	
	printf("Manifacture_ID =0x%x,Device_size=%dMB \n\r",Manifacture_ID,Device_size/1024/1024);
	printf("\n\r");

	/* 打印各个扇区的起始地址 */
	/* 名词解释:
	 *    erase block region : 里面含有1个或多个block, 它们的大小一样
	 * 一个nor flash含有1个或多个region
	 * 一个region含有1个或多个block(扇区)

	 * Erase block region information:      由CFI接口协议可知道
	 *    前2字节+1    : 表示该region有多少个block 
	 *    后2字节*256  : 表示block的大小
	 */

	region_nums=nor_dat(0x2c);


	for(i=0;i<region_nums;i++)			
	{
		printf("Region:%d\n\r",i);
		block_nums=1+nor_dat(region_info_base)+(nor_dat(region_info_base+1)<<8);
		block_size=256*(nor_dat(region_info_base+2)+(nor_dat(region_info_base+3)<<8));
		region_info_base+=4;
		for(j=0;j<block_nums;j++)
		{
			printHex(start_addrs);
			start_addrs+=block_size;
			putchar(' ');

		}
		printf("\n\r");


	}
	 
	nor_flash_cmd(0,0xf0);

	printf("\n\r");

}




//在有*的这一句中 为什么移位参考这两篇博客
// http://www.eeworld.com.cn/mcu/article_2016080628260.html
// http://www.eeworld.com.cn/mcu/article_2016080628260.html
void Sector_Erase()
{
	u32 addr;
	
	printf("Please enter the sector address to be deleted: ");
	addr=get_uint();
	
	nor_flash_cmd(0x555,0xaa);			//这是站在norflash角度看的			1位地址是一个半字
	nor_flash_cmd(0x2aa,0x55);
	nor_flash_cmd(0x555,0x80);

	nor_flash_cmd(0x555,0xaa);
	nor_flash_cmd(0x2aa,0x55);
	nor_flash_cmd(addr>>1,0x30);			// *  这是站在ARM角度上看的				1位地址是1个字节
	wait_ready(addr);
	nor_flash_cmd(0,0xf0);


}


void Read_nor_flash()
{
	volatile u8 *p;
	u32 addr;
	u8 i,j;

	printf("Enter the address to read: ");
	addr=get_uint();

	p=(u8 *)addr;

	for(i=0;i<6;i++)
	{

		for(j=0;j<16;j++)
		{
			printf("%02x ",*p++);
			printf(" ");
		

		}
		printf("\n\r");
	}


}



void Write_nor_flash()
{
	u8 str[100];
	u32 addr;
	u8 i=0,j=1;
	u16 val;

	printf("Enter the address to write: ");
	addr=get_uint();

	printf("Enter the string to write: ");
	gets(str);

	while(str[i] && str[j])
	{
		val=str[i]+(str[j]<<8);
		i+=2;
		j+=2;
;
		
		nor_flash_cmd(0x555,0xaa);			
		nor_flash_cmd(0x2aa,0x55);
		nor_flash_cmd(0x555,0xa0);
		nor_flash_cmd(addr>>1,val);
		wait_ready(addr);
		addr+=2;

	}

	val=str[i]+(str[j]<<8);
	nor_flash_cmd(0x555,0xaa);			
	nor_flash_cmd(0x2aa,0x55);
	nor_flash_cmd(0x555,0xa0);
	nor_flash_cmd(addr>>1,val);
	wait_ready(addr);

	


}





void nor_flash_test()
{
	char c;
	while(1)
	{
		/* 打印菜单, 供我们选择测试内容 */
		printf("[s] Scan nor flash\n\r");
		printf("[e] Erase nor flash\n\r");
		printf("[w] Write nor flash\n\r");
		printf("[r] Read nor flash\n\r");
		printf("[q] quit\n\r");
		printf("Enter selection: ");

		c = getchar();
		printf("%c\n\r", c);
		printf("\n\r");
		switch(c)
		{

			case 's':
			case 'S':
			Scan_nor_flash();
			break;

			case 'e':
			case 'E':
			Sector_Erase();
			break;

			case 'w':
			case 'W':
			Write_nor_flash();
			break;			

			case 'r':
			case 'R':
			Read_nor_flash();
			break;	

			case 'q':
			case 'Q':
			return;
			break;


		}










	}










}




























