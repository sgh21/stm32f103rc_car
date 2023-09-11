#include"ultrasonic.h"
int count=0;
int N=0;
float distance;
void ultrasonic_init(){
	//ʱ��&&�жϳ�ʼ���ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
  //TIM_ICInitTypeDef TIM_ICInitStructure;
	//��ʼ������ӿ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	TIM_DeInit(TIM2);//����TIM2
	GPIO_INIT(GPIOC,GPIO_Pin_0,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOC,GPIO_Pin_1,GPIO_Mode_IPD,GPIO_Speed_50MHz);
	//GPIO_INIT(GPIOA,GPIO_Pin_0,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	
	//��ʼ��ʱ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_InternalClockConfig(TIM2);  
  TIM_TimeBaseStructure.TIM_Prescaler = 71;//Ԥ��ƵֵMCUƵ��Ϊ72MHz
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�������ؼ���
  TIM_TimeBaseStructure.TIM_Period = 99;//������ֵ0xFFFF  //���ʱ��Ϊ0.1ms
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ʱ�Ӳ��ָ�
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//���ظ�����
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//�жϴ�������
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���÷���2��������ռλ��������λ
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	
  TIM_Cmd(TIM2, DISABLE);//�رռ���
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
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//�����־λ
}
float calculate_distance(){
	send_trig();
	TIM2->CNT=0;
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==RESET){}//��ʱ�ȴ����������յ��ź�
	TIM_Cmd(TIM2, ENABLE);
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==SET){}//�ӳٵȴ���������ȫ���ܵ��ź�
	TIM_Cmd(TIM2, DISABLE);
	count=TIM_GetCounter(TIM2);
  distance = (float)(count+N*100)/58.3;//distance cm
	TIM2->CNT=0;
	N=0;
	delay_ms(1);
	//printf("%f",distance);
	return distance;
}