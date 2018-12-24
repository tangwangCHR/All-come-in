


void Copy_text_R_data(void)
{
	extern int __code_start,_end;
	volatile unsigned int *code_start = (volatile unsigned int *)&__code_start;
	volatile unsigned int *end = (volatile unsigned int *)&_end;
	volatile unsigned int *src = (volatile unsigned int *)0;

	while(code_start < end)
	{
		*code_start++ = *src++ ;

	}



}


void Copy_bss()
{
	extern int __bss_start,_end;
	volatile unsigned int *bss_start = (volatile unsigned int *)&__bss_start;
	volatile unsigned int *end = (volatile unsigned int *)&_end;
	


	while(bss_start <= end)
	{
		*bss_start++=0;

	}



}

























