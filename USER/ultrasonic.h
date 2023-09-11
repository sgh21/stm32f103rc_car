#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "stm32f10x.h"
#include"IO_INIT.h"
#include"delay.h"

void ultrasonic_init();
float calculate_distance();
//void TIM2_IRQHander();
#endif 