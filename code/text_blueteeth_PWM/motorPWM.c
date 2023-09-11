#include"motorPWM.h"
#define period 999
#define psc 100



void MotorPWM_Init(){
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;


  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler =psc;
  TIM_TimeBaseStructure.TIM_Period = period;                                            
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  //TIM_OCInitStructure.TIM_Pulse = (uint16_t)((TIM_TimeBaseStructure.TIM_Period * pwmDutyCycle) / 100); 
  TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);

 
  TIM_Cmd(TIM4, ENABLE);
  TIM_CtrlPWMOutputs(TIM4, ENABLE);
	
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	
	
	GPIO_INIT(GPIOA ,GPIO_Pin_4,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOB ,GPIO_Pin_9,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOB ,GPIO_Pin_7,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOB ,GPIO_Pin_8,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);
}
	
void MotorPWM_Forward(int speed,int d_speed)
{
	u16 high_line_left;
	u16 high_line_right;
	if (speed>=d_speed){
	high_line_left=(speed+d_speed)*10;
	high_line_right=(speed-d_speed)*10;
	}
	else {
	high_line_left=speed*10;
	high_line_right=speed*10;
	}
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
  GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	TIM_SetCompare3(TIM4, high_line_right);
	TIM_SetCompare4(TIM4, high_line_left);
}
void MotorPWM_Backward(int speed,int d_speed)
{
	u16 high_line_left;
	u16 high_line_right;
	if (speed>=d_speed){
	high_line_left=(speed+d_speed)*10;
	high_line_right=(speed-d_speed)*10;
	}
	else {
	high_line_left=speed*10;
	high_line_right=speed*10;
	}
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
  GPIO_SetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, period-high_line_right);
	TIM_SetCompare4(TIM4, period-high_line_left);
}
void MotorPWM_Left(int speed,int d_speed)
{
	u16 high_line_left;
	u16 high_line_right;
	if (speed>=d_speed){
	high_line_left=(speed+d_speed)*10;
	high_line_right=(speed-d_speed)*10;
	}
	else {
	high_line_left=speed*10;
	high_line_right=speed*10;
	}
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
  GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	TIM_SetCompare3(TIM4, high_line_right);
	TIM_SetCompare4(TIM4, high_line_left);
}
void MotorPWM_Right(int speed,int d_speed)
{
	u16 high_line_left;
	u16 high_line_right;
	if (speed>=d_speed){
	high_line_left=(speed+d_speed)*10;
	high_line_right=(speed-d_speed)*10;
	}
	else {
	high_line_left=speed*10;
	high_line_right=speed*10;
	}
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
  GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	TIM_SetCompare3(TIM4, high_line_right);
	TIM_SetCompare4(TIM4, high_line_left);
}
void MotorPWM_LeftSpin(int speed)
{ 
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
  GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, period-speed*10);
	TIM_SetCompare4(TIM4, speed*10);
}
void MotorPWM_RightSpin(int speed)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
  GPIO_SetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, speed*10);
	TIM_SetCompare4(TIM4, period-speed*10);
}

void MotorPWM_Stop(int time)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
  GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, 0);
	delay_ms(time);
}
