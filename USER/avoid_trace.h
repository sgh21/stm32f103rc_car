#ifndef AVOID_TRACE_H
#define AVOID_TRACE_H

#include "stm32f10x.h"
#include "delay.h"
#include "control.h"

#define BEEP_SET 		GPIO_SetBits(GPIOC,GPIO_Pin_3)
#define BEEP_RESET 	GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define LED_SET			GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define LED_RESET 	GPIO_ResetBits(GPIOA,GPIO_Pin_5)

#define KEY  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)           


//蓝牙函数
void USART2_Init(void);
void USART2_SendChar(char ch);
char USART2_ReceiveChar(void);//add other function with the received char

//按键函数
void KEY_Init(void);
void keysacn();


//IO函数
void GPIO_INIT(GPIO_TypeDef* CPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,GPIOSpeed_TypeDef GPIO_Speed);


//motor函数
void Motor_Init();
void Motor_Forward(int time);
void Motor_Backward(int time);
void Motor_Left(int time);
void Motor_Right(int time);
void Motor_LeftSpin(int time);
void Motor_RightSpin(int time);
void Motor_Stop(int time);


//PWM函数
void TIM4_PWM_Init();
void MotorPWM_Forward(int speed);
void MotorPWM_Backward(int speed);
void MotorPWM_Left(int speed);
void MotorPWM_Right(int speed);
void MotorPWM_LeftSpin(int speed);
void MotorPWM_RightSpin(int speed);
void MotorPWM_Stop(int time);
void MotorPWM_Stopall(void);
void MotorPWM_Steering(int left,int right);


void IRAvoidInit(void);//红外初始化
void AVoidRun(void);//红外避障函数



void trace_init();//循迹初始化
void trace_begin(int speed1,int speed2);//循迹函数


void KeyScanTask();//按键切换


//主函数
void TheLast();
void main_trace_avoid(int speed1,int speed2);//避障之后能回去
void main_motor_8();//走八字
void main_speed();//加速函数
void main_trace(int speed1,int speed2);
void main_red_avoid();
void main_key_switch();//按键切换
void main_avoid_trace(int speed1,int speed2);//循迹和避障同时
#endif