#include "tim.h"

static void TIM_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//PB0��PB1��PA6��PA7
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
		
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOA6����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOA7����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOB0����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOB1����Ϊ��ʱ��3

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;           //PA6��PA7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;            //PB0��PB1
	GPIO_Init(GPIOB,&GPIO_InitStructure);             
}

static void TIM3_Mode_Init(void)
{		 					 
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	 
	TIM_TimeBaseStructure.TIM_Prescaler=180-1;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=1000-1;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	//��ʼ��TIM3 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse=1000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:�ߵ�ƽ��Ч
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	

	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);  //�ر�TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);  //CCR3
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);  //CCR2 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);  //CCR1
	TIM_ARRPreloadConfig(TIM3,DISABLE);					//�ر�ARPE
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3									  
}  

void TIM3_Init(void)	
{
	TIM_GPIO_Init();
	TIM3_Mode_Init();
}

