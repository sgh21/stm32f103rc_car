#ifndef TRACE_H
#define TRACE_H
#include"stm32f10x.h"
#include"IO_INIT.h"
#include"motorPWM.h"
#include"blueteeth.h"

void trace_init();
void trace_begin(int speed,int d_speed);

#endif 