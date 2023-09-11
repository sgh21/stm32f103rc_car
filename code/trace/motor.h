#ifndef MOTOR_H
#define MOTOR_H
#include"stm32f10x.h"
#include"delay.h"
#include"IO_INIT.h"
void Motor_Init();
void Motor_Forward(int time);
void Motor_Backward(int time);
void Motor_Left(int time);
void Motor_Right(int time);
void Motor_LeftSpin(int time);
void Motor_RightSpin(int time);
void Motor_Stop(int time);
#endif 