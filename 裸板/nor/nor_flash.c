#include "nor_flash.h"
#include "my_printf.h"
#include "string_utils.h"
#include "s3c2440_soc.h"





void nor_flash_cmd(u32 addr,u32 dat)
{
	//LADDR1--LADDR20      �ӵ�   A0--A19
	//���԰���˵����cpu��norflash���͵�ַλʱҪ����һλ
	//norflash���ӵ���0   ���ַ��0��ʼ
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
	pre=nor_dat(addr>>1);				//�ϴ�����
	val=nor_dat(addr>>1);				//��������
	while((pre & (1<<6))!=(val & (1<<6)))		//����������д �� ����ɾ���Ĺ�����DQ6��ƽ״̬�����ط�ת��
	{

		pre=val;
		val=nor_dat(addr>>1);

	}
}



void Scan_nor_flash()
{
	//��ӡ����ID���豸ID
	u32 Manifacture_ID;
	u32 Device_ID;
	u8 str[4];					//��ѯΨһ��ASCII�ַ�����QRY��
	u32 Device_size;			//�����ڴ��С
	u8 region_nums;			//�����������
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

	nor_flash_cmd(0,0xf0);			//��λ
	//����CFIģʽ
	/*   Flash �洢���ӿڻ���������׼��CFI��JEDEC��CFIΪ����Flash�ӿ�[Common Flash Interface]��������������
	**   ��FlashоƬ�л�ȡ������ʽ��Ϣ(���������nor flash��оƬ���ȡ�����ĸ��ֲ�������оƬʱ�������޸��ں˴�
	**		�������ڳ�����Ӳ����Flash��ID
	*/
	nor_flash_cmd(0x55,0x98);
		
	//��ѯΨһ��ASCII�ַ�����QRY��
	str[0]=nor_dat(0x10);
	str[1]=nor_dat(0x11);
	str[2]=nor_dat(0x12);
	str[3]='\0';
	printf("str=%s\n\r",str);
	
	Device_size=1<<nor_dat(0x27);				//Device size = 2��n�η� in number of bytes (MX29LV160D)



	
	printf("Manifacture_ID =0x%x,Device_size=%dMB \n\r",Manifacture_ID,Device_size/1024/1024);
	printf("\n\r");

	/* ��ӡ������������ʼ��ַ */
	/* ���ʽ���:
	 *    erase block region : ���溬��1������block, ���ǵĴ�Сһ��
	 * һ��nor flash����1������region
	 * һ��region����1������block(����)

	 * Erase block region information:      ��CFI�ӿ�Э���֪��
	 *    ǰ2�ֽ�+1    : ��ʾ��region�ж��ٸ�block 
	 *    ��2�ֽ�*256  : ��ʾblock�Ĵ�С
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




//����*����һ���� Ϊʲô��λ�ο�����ƪ����
// http://www.eeworld.com.cn/mcu/article_2016080628260.html
// http://www.eeworld.com.cn/mcu/article_2016080628260.html
void Sector_Erase()
{
	u32 addr;
	
	printf("Please enter the sector address to be deleted: ");
	addr=get_uint();
	
	nor_flash_cmd(0x555,0xaa);			//����վ��norflash�Ƕȿ���			1λ��ַ��һ������
	nor_flash_cmd(0x2aa,0x55);
	nor_flash_cmd(0x555,0x80);

	nor_flash_cmd(0x555,0xaa);
	nor_flash_cmd(0x2aa,0x55);
	nor_flash_cmd(addr>>1,0x30);			// *  ����վ��ARM�Ƕ��Ͽ���				1λ��ַ��1���ֽ�
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
		/* ��ӡ�˵�, ������ѡ��������� */
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




























