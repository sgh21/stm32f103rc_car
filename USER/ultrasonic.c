#include"ultrasonic.h"
int count=0;
int N=0;
float distance;
void ultrasonic_init(){
	//时钟&&中断初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
  //TIM_ICInitTypeDef TIM_ICInitStructure;
	//初始化外设接口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	TIM_DeInit(TIM2);//复用TIM2
	GPIO_INIT(GPIOC,GPIO_Pin_0,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOC,GPIO_Pin_1,GPIO_Mode_IPD,GPIO_Speed_50MHz);
	//GPIO_INIT(GPIOA,GPIO_Pin_0,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	
	//初始化时钟

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_InternalClockConfig(TIM2);  
  TIM_TimeBaseStructure.TIM_Prescaler = 71;//预分频值MCU频率为72MHz
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//沿上升沿计数
  TIM_TimeBaseStructure.TIM_Period = 99;//最大计数值0xFFFF  //溢出时间为0.1ms
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//时钟不分割
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//不重复计数
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//中断触发设置
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//采用分组2，两个抢占位两个优先位
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	
  TIM_Cmd(TIM2, DISABLE);//关闭计数
}
void send_trig(){
	GPIO_SetBits(GPIOC, GPIO_Pin_0);
  delay_us(20);
  GPIO_ResetBits(GPIOC, GPIO_Pin_0);
}
	
void TIM2_IRQHandler(){
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET){
		N+=1;
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清楚标志位
}
float calculate_distance(){
	send_trig();
	TIM2->CNT=0;
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==RESET){}//延时等待超声波接收到信号
	TIM_Cmd(TIM2, ENABLE);
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==SET){}//延迟等待超声波完全接受到信号
	TIM_Cmd(TIM2, DISABLE);
	count=TIM_GetCounter(TIM2);
  distance = (float)(count+N*100)/58.3;//distance cm
	TIM2->CNT=0;
	N=0;
	delay_ms(1);
	//printf("%f",distance);
	return distance;
}