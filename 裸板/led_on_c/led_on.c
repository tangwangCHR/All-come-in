

#define GPFCON (*(unsigned int*)0x56000050)
#define GPFDAT (*(unsigned int*)0x56000054)

int main()
{


        GPFCON&=0xfffff3ff;  
        GPFCON|=0x00000400;

        GPFDAT&=0xdf;                  //������3��led
        while(1);
	return 0; 


}
























