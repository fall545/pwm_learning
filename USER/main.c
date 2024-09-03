#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
//ALIENTEKս��STM32������ʵ��9
//PWM���ʵ��  
//����֧�֣�www.openedv.com
//�������������ӿƼ����޹�˾ 
	
 int main(void)
 {		
 	u16 led0pwmval=300;
	u8 dir=1;	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
 	TIM3_PWM_Init(719,0);	 //����Ƶ��PWMƵ��=72000/900=8Khz 72000/720=100khz
	 
   	while(1)
	{
			
		//delay_ms(10);	 
		if(dir)led0pwmval++;
		else led0pwmval--;

		if(led0pwmval>700)dir=0;
		if(led0pwmval==0)dir=1;										 
	TIM_SetCompare2(TIM3,led0pwmval);		   
	}	 
 }

