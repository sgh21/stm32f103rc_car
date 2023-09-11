#include "control.h"
float DISTANCE[3]={0,0,0};
void TIM5_PWM_Init(u16 arr,u16 psc)
{
	//定义初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
	
	//使能定时器时钟 TIM5
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	//使能GPIOA外设时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//初始化GPIO
	GPIO_INIT(GPIOA,GPIO_Pin_0,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);
	//steering_gear_init();
	
	//初始化时基
	//设置在下一个更新事件装入活动的自动重装载寄存器周期值50HZ
	 TIM_TimeBaseStructure.TIM_Period = arr;
	//设置用来作为TIMx时钟频率除数的预分频值 不分频
	 TIM_TimeBaseStructure.TIM_Prescaler =psc;
	//设置时钟分割：TDTS = Tck_tim
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	 //TIM向上计数模式
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	 //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
	
	   //输出模式配置
	   // 配置PWM通道1
    //TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = 1500; // 初始占空比为1.5ms，对应舵机中立位置
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	 //选择定时器模式：TIM脉冲宽度调制模式1
	 //TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	 //比较输出使能
	// TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 //TIM_OCInitStructure.TIM_Pulse = 1500;//设置待装入捕获比较寄存器的脉冲值
	 //输出极性：TIM输出比较级性高
	 //TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	 //TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	 
	 TIM_CtrlPWMOutputs(TIM5,ENABLE);	//MOE 主输出使能	
	 
	 //TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1预装载使能
   //TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	 
	 //使能ARR、MOE及定时器
	 TIM_ARRPreloadConfig(TIM5, ENABLE); //使能TIMx在ARR上的预装载寄存器
   TIM_Cmd(TIM5, ENABLE); //使能TIM5
	 	
}
void set_angle(float angle){
	TIM_OCInitTypeDef TIM_OCInitStructure;
	u16 pulse;
	pulse=angle*15+1500;
	TIM5->CCR1=pulse;
}
void steering_gear_init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_INIT(GPIOA,GPIO_Pin_0,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);
}
void steering_gear_left(int angle,int time){
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	delay_ms(angle/22.5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	delay_ms(time);
}
void steering_gear_right(int angle,int time){
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	delay_ms(angle/22.5);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	delay_ms(time);
}
int find_max(float DISTANCE[]){
	int i;
	int index;
	float max;
	index=0;
	max=0.0;
	i=0;
	for(;i<3;i++){
		if(DISTANCE[i]>max){
			max=DISTANCE[i];
			index=i;
		}
	}
	return index;
}
void init_all(){
	//MotorPWM_Init();//启动电机
	delay_init();
	//steering_gear_init();//启动舵机
	TIM5_PWM_Init(2999,71);//启动舵机及其PWM控制
	ultrasonic_init();//启动超声避障模块
}
int find_way(){
	  float distance;
	  int index;
	  set_angle(0.0);
	  distance=calculate_distance();
	  delay_ms(4000);
		DISTANCE[0]=distance;
		set_angle(61.0);
		delay_ms(1000);
		//steering_gear_left(90,1000);//测量左侧距离
		distance=calculate_distance();
		delay_ms(4000);
		DISTANCE[1]=distance;
		//set_angle(0.0);
		delay_ms(2000);
		//steering_gear_right(180,1000);//测量右侧距离
		set_angle(-68.0);
		delay_ms(1000);
		distance=calculate_distance();
		delay_ms(4000);
		DISTANCE[2]=distance;
		set_angle(0.0);
		//steering_gear_left(90,1000);//舵机朝前
		index=find_max(DISTANCE);
		if(DISTANCE[index]>20){
			return index;
		}
		else return -1;
}
/*void run(){
	  int index ;
		float distance;
	  distance=calculate_distance();
	  if(distance<=15){
		index=find_way();
		switch(index){
			case 0://三面全是障碍物时的情况处理
				MotorPWM_Backward(50,0);
				delay_ms(1000);
				MotorPWM_Stop(1);
				break;
			case 1://左侧有路
				MotorPWM_Left(40,40);
				break;
			case 2://右侧有路
				MotorPWM_Right(40,40);
				break;
		}
		delay_ms(410);
	}
	else{
		MotorPWM_Forward(50,0);
	}
}*/
