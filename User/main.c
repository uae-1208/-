#include "stm32f4xx.h"
#include "usart.h"
#include "motor.h"
#include "tim.h"


int main(void)
{
	extern enum State{busy,free} state;
	extern enum Order{forward,backward,left,right,stop} order;

	HC06_Config();	
	MOTOR_Config();	
	TIM3_Init();

  	while(1) 
	{
		 if(busy)            //接收到命令并且该执行
		 {
			 switch(order)
			 {
				 case forward:	FORWARD_MOVE();
								break;
				 case backward:	BACKWARD_MOVE();
				 				break;
				 case left:	LEFT_TURNING();
				 				break;
				 case right: RIGHT_TURNING();
				 				break;
				 case stop: STOP_MOVE();
				 				break;
			 }
			 state = free;       //执行完成
		 }  
	}  
}

