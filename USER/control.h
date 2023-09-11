#ifndef STEERING_GEAR_H
#define STEERING_GEAR_H
#include "stm32f10x.h"
//#include "motorPWM.h"
#include "ultrasonic.h"
#include "IO_INIT.h"
#include "delay.h"
void TIM5_PWM_Init(u16 arr,u16 psc);
void set_angle(float angle);
void steering_gear_init();
void steering_gear_left(int angle,int time);
void steering_gear_right(int angle,int time);
int find_max(float DISTANCE[]);
void init_all();
int find_way();
//void run();
#endif