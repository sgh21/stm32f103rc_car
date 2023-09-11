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


//��������
void USART2_Init(void);
void USART2_SendChar(char ch);
char USART2_ReceiveChar(void);//add other function with the received char

//��������
void KEY_Init(void);
void keysacn();


//IO����
void GPIO_INIT(GPIO_TypeDef* CPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,GPIOSpeed_TypeDef GPIO_Speed);


//motor����
void Motor_Init();
void Motor_Forward(int time);
void Motor_Backward(int time);
void Motor_Left(int time);
void Motor_Right(int time);
void Motor_LeftSpin(int time);
void Motor_RightSpin(int time);
void Motor_Stop(int time);


//PWM����
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


void IRAvoidInit(void);//�����ʼ��
void AVoidRun(void);//������Ϻ���



void trace_init();//ѭ����ʼ��
void trace_begin(int speed1,int speed2);//ѭ������


void KeyScanTask();//�����л�


//������
void TheLast();
void main_trace_avoid(int speed1,int speed2);//����֮���ܻ�ȥ
void main_motor_8();//�߰���
void main_speed();//���ٺ���
void main_trace(int speed1,int speed2);
void main_red_avoid();
void main_key_switch();//�����л�
void main_avoid_trace(int speed1,int speed2);//ѭ���ͱ���ͬʱ
#endif