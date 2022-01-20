#include "stm32f4xx.h"
#include "motor.h"

static void MOTOR_GPIO_Configuration(void)                 
{
	//E3��E5wheel3      E4��E6wheel4         B7��B9wheel2          B6��B8wheel1
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOB, ENABLE);    //���ת���������pin�ڣ�
	RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOE, ENABLE);    //PB6-PB9��PE3-PE6
	
	GPIO_InitTypeDef GPIO_InitStructure;													   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);		
}


void MOTOR_Config(void)                              //�������
{
	MOTOR_GPIO_Configuration();
}

enum Wheel{wheel1,wheel2,wheel3,wheel4};              //���ӱ��
                                            
static void WHEEL_BACKWARD_MOVE(enum Wheel wheel)           //���������Ⱥ�ת
{
	 switch(wheel)
	{
		case wheel1:GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_SET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_RESET);
					break;
		case wheel2:GPIO_WriteBit(GPIOB,GPIO_Pin_7,Bit_SET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_9,Bit_RESET);
					break;
		case wheel3:GPIO_WriteBit(GPIOE,GPIO_Pin_5,Bit_SET);
					GPIO_WriteBit(GPIOE,GPIO_Pin_3,Bit_RESET);
					break;
		case wheel4:GPIO_WriteBit(GPIOE,GPIO_Pin_6,Bit_SET);
					GPIO_WriteBit(GPIOE,GPIO_Pin_4,Bit_RESET);
					break;
	}	 
}


static void WHEEL_FORWARD_MOVE(enum Wheel wheel)              //����������ǰת
{
	 switch(wheel)
	{
		case wheel1:GPIO_WriteBit(GPIOB,GPIO_Pin_6,Bit_SET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_8,Bit_RESET);
					break;
		case wheel2:GPIO_WriteBit(GPIOB,GPIO_Pin_9,Bit_SET);
					GPIO_WriteBit(GPIOB,GPIO_Pin_7,Bit_RESET);
					break;
		case wheel3:GPIO_WriteBit(GPIOE,GPIO_Pin_3,Bit_SET);
					GPIO_WriteBit(GPIOE,GPIO_Pin_5,Bit_RESET);
					break;
		case wheel4:GPIO_WriteBit(GPIOE,GPIO_Pin_4,Bit_SET);
					GPIO_WriteBit(GPIOE,GPIO_Pin_6,Bit_RESET);
					break;
	}	 
}


static void MOTIVE_MOVE(void)                          //��L298Nʹ�ܶ�
{
	TIM_SetCompare1(TIM3,1000);
	TIM_SetCompare2(TIM3,1000);
	TIM_SetCompare3(TIM3,1000);
	TIM_SetCompare4(TIM3,1000);
}

                                                       //�ر�L298Nʹ�ܶˣ�С��Ҳֹͣ�˶�
void STOP_MOVE(void)
{
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_SetCompare4(TIM3,0);
}

void FORWARD_MOVE(void)                                       //С����ǰ�ƶ�
{
	MOTIVE_MOVE();
	WHEEL_FORWARD_MOVE(wheel1);
	WHEEL_FORWARD_MOVE(wheel2);
	WHEEL_FORWARD_MOVE(wheel3);
	WHEEL_FORWARD_MOVE(wheel4);
}	


void BACKWARD_MOVE(void)                                  //С������ƶ�
{
	MOTIVE_MOVE();
	WHEEL_BACKWARD_MOVE(wheel1);
	WHEEL_BACKWARD_MOVE(wheel2);
	WHEEL_BACKWARD_MOVE(wheel3);
	WHEEL_BACKWARD_MOVE(wheel4);
}


void LEFT_TURNING(void)                                      //С����ת
{
	MOTIVE_MOVE();
	WHEEL_BACKWARD_MOVE(wheel1);
	WHEEL_BACKWARD_MOVE(wheel2);
	WHEEL_FORWARD_MOVE(wheel3);
	WHEEL_FORWARD_MOVE(wheel4);
}



void RIGHT_TURNING(void)									//С����ת
{
	MOTIVE_MOVE();
	WHEEL_BACKWARD_MOVE(wheel3);
	WHEEL_BACKWARD_MOVE(wheel4);
	WHEEL_FORWARD_MOVE(wheel1);
	WHEEL_FORWARD_MOVE(wheel2);
}




