#include "control.h"
float DISTANCE[3]={0,0,0};
void TIM5_PWM_Init(u16 arr,u16 psc)
{
	//�����ʼ���ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
	
	//ʹ�ܶ�ʱ��ʱ�� TIM5
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	//ʹ��GPIOA����ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//��ʼ��GPIO
	GPIO_INIT(GPIOA,GPIO_Pin_0,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);
	//steering_gear_init();
	
	//��ʼ��ʱ��
	//��������һ�������¼�װ�����Զ���װ�ؼĴ�������ֵ50HZ
	 TIM_TimeBaseStructure.TIM_Period = arr;
	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ ����Ƶ
	 TIM_TimeBaseStructure.TIM_Prescaler =psc;
	//����ʱ�ӷָTDTS = Tck_tim
	 TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	 //TIM���ϼ���ģʽ
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	 //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); 
	
	   //���ģʽ����
	   // ����PWMͨ��1
    //TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse = 1500; // ��ʼռ�ձ�Ϊ1.5ms����Ӧ�������λ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	 //ѡ��ʱ��ģʽ��TIM�����ȵ���ģʽ1
	 //TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	 //�Ƚ����ʹ��
	// TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	 //TIM_OCInitStructure.TIM_Pulse = 1500;//���ô�װ�벶��ȽϼĴ���������ֵ
	 //������ԣ�TIM����Ƚϼ��Ը�
	 //TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	 //TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	 
	 TIM_CtrlPWMOutputs(TIM5,ENABLE);	//MOE �����ʹ��	
	 
	 //TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1Ԥװ��ʹ��
   //TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	 
	 //ʹ��ARR��MOE����ʱ��
	 TIM_ARRPreloadConfig(TIM5, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
   TIM_Cmd(TIM5, ENABLE); //ʹ��TIM5
	 	
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
	//MotorPWM_Init();//�������
	delay_init();
	//steering_gear_init();//�������
	TIM5_PWM_Init(2999,71);//�����������PWM����
	ultrasonic_init();//������������ģ��
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
		//steering_gear_left(90,1000);//����������
		distance=calculate_distance();
		delay_ms(4000);
		DISTANCE[1]=distance;
		//set_angle(0.0);
		delay_ms(2000);
		//steering_gear_right(180,1000);//�����Ҳ����
		set_angle(-68.0);
		delay_ms(1000);
		distance=calculate_distance();
		delay_ms(4000);
		DISTANCE[2]=distance;
		set_angle(0.0);
		//steering_gear_left(90,1000);//�����ǰ
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
			case 0://����ȫ���ϰ���ʱ���������
				MotorPWM_Backward(50,0);
				delay_ms(1000);
				MotorPWM_Stop(1);
				break;
			case 1://�����·
				MotorPWM_Left(40,40);
				break;
			case 2://�Ҳ���·
				MotorPWM_Right(40,40);
				break;
		}
		delay_ms(410);
	}
	else{
		MotorPWM_Forward(50,0);
	}
}*/
