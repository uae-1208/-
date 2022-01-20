#ifndef __MORTOR_H__
#define	__MORTOR_H__

#include "stm32f4xx.h"


void MOTOR_Config(void);
void FORWARD_MOVE(void);
void BACKWARD_MOVE(void);
void LEFT_TURNING(void);
void RIGHT_TURNING(void);

void STOP_MOVE(void);


#endif

