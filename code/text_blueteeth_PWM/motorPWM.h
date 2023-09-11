#ifndef MOTORPWM_H
#define MOTORPWM_H

#include"stm32f10x.h"
#include"IO_INIT.h"
#include"delay.h"

void MotorPWM_Init();
void MotorPWM_Forward(int speed, int d_speed);
void MotorPWM_Backward(int speed, int d_speed);
void MotorPWM_Left(int speed, int d_speed);
void MotorPWM_Right(int speed, int d_speed);
void MotorPWM_LeftSpin(int speed);
void MotorPWM_RightSpin(int speed);
void MotorPWM_Stop(int time);

#endif