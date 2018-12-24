#include "lcd_controller.h"





/*			�𵽳������µ�����
 *		���Ͻ��ղ�ͬ��lcd����    
 *		����ʹ����Щ�������ö�Ӧ��lcd������
 */


#define lcd_controller_num 10									//֧��10��lcd
   
p_lcd_con_opr lcd_con[lcd_controller_num];
p_lcd_con_opr glb_lcd_con;



 int lcd_controller_regesiter(p_lcd_con_opr p)
 {

 	 u8 i=0;
	 for(i=0;i<lcd_controller_num;i++)
	 {
		 if(!(lcd_con[i]))				 //�������ڴ�û���õĻ�	 ��ע������ڴ�
		 {
 
			 lcd_con[i]=p;
			 return i;
 
		 }
 
	 }
	 return -1;
 }
 
 
 int select_lcd_controller(u8 *name)
 {
	 u8 i;
	 for(i=0;i<lcd_controller_num;i++)
	 {
 
		 if((lcd_con[i]) && strcmp(lcd_con[i]->name,name))
		 {
			 glb_lcd_con = lcd_con[i];
			 return i;
 
		 }
 
 
	 }
	 return -1;
 
 }




int lcd_controller_init(p_lcd_parameter p)
{
	if(glb_lcd_con)
	{

		glb_lcd_con->lcd_con_init(p);
		glb_lcd_con->lcd_con_palette_init();
		return 1;

	}
	return 0;


}










