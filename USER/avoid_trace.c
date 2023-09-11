#include"avoid_trace.h"

uint8_t SEARCH_R_IO;                                 //�������ڶ�ȡ�Ҳ������չܵ�IO��״̬
uint8_t SEARCH_L_IO;
uint8_t AVOID_IO;
uint8_t keyMode=1;
int arr=999;
int psc=71;

//��������
void USART2_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  //begin clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_DeInit(USART2);  //reuse USART2
  
	GPIO_INIT(GPIOA,GPIO_Pin_2,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOA,GPIO_Pin_3,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);
  

  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);
  
 
  USART_Cmd(USART2, ENABLE);//cmd enable
}


void USART2_SendChar(char ch)
{
 
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
  {}
  USART_SendData(USART2, ch);
}


char USART2_ReceiveChar(void)
{
  
  while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
  {}
	
  return USART_ReceiveData(USART2);
}



//��������
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);        //??PORTC??
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);  //??PA,PD????
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                   //PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //IO????50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);                       //???GPIOC2

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                   //PC3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //IO????50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);                       //???GPIOC3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;          //LED��ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitStructure);              
	GPIO_SetBits(GPIOA,GPIO_Pin_5);        
}

void keysacn()
{
	int val;
	val=KEY;                                                    //????
	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))             //?????????,????
	{
		val=KEY;                                                  //?????,??????
	}
	delay_init();
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))              //???????
	{
		delay_ms(10);                                             //??10ms
		val=KEY;                                                  //??????PC2??????val
		if(val==1)                                                //????????????
		{
			 break;                                              //????
			
		}
		
			                                             //?????
	}
}





//IO����
void GPIO_INIT(GPIO_TypeDef* CPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,GPIOSpeed_TypeDef GPIO_Speed){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed;
	GPIO_Init(CPIOx,&GPIO_InitStructure);
}
//motor����
void Motor_Init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);       
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  
	GPIO_INIT(GPIOB,GPIO_Pin_7,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);//3
	GPIO_INIT(GPIOB,GPIO_Pin_8,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);//4
	GPIO_INIT(GPIOB,GPIO_Pin_9,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);//2
	GPIO_INIT(GPIOA,GPIO_Pin_4,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);//1
}

void Motor_Forward(int time){
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	delay_ms(time);
}
	
void Motor_BackWord(int time){
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	delay_ms(time);
}
void Motor_Left(int time){
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_ms(time);
}

void Motor_Right(int time){
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	delay_ms(time);
}

void Motor_RightSpin(int time){
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	delay_ms(time);
}

void Motor_LeftSpin(int time){
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	delay_ms(time);
}

void Motor_Stop(int time){
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	delay_ms(time);
}
//PWM����
void TIM4_PWM_Init(){
	//��ʼ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	
	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC4Init(TIM4,&TIM_OCInitStructure);
	

	
	GPIO_INIT(GPIOA ,GPIO_Pin_4,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOB ,GPIO_Pin_9,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOB ,GPIO_Pin_7,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOB ,GPIO_Pin_8,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);
	
	TIM_CtrlPWMOutputs(TIM4,ENABLE);	//�����ʹ��
  
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ�� 
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��
	
  TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIM4��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM4, ENABLE); 
}
	
void MotorPWM_Forward(int speed)
{
	int spwm = speed*arr/100;
	TIM_SetCompare3(TIM4, spwm);//you
	TIM_SetCompare4(TIM4, spwm);//zuo
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);//zuo
  GPIO_ResetBits(GPIOB, GPIO_Pin_7);//you

}

void MotorPWM_Backward(int speed)
{
	int spwm =(arr-speed)*arr/100;
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
  GPIO_SetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, speed);
	TIM_SetCompare4(TIM4, speed);

}
void MotorPWM_Left(int speed)
{
	int spwm = speed*arr/100;
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);//1
  GPIO_ResetBits(GPIOB,GPIO_Pin_7);//3
	TIM_SetCompare3(TIM4, spwm);//4
	TIM_SetCompare4(TIM4, 0);//2

}
void MotorPWM_Right(int speed)
{
	int spwm = speed*arr/100;
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
  GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, spwm);

}
void MotorPWM_LeftSpin(int speed)
{	
	int spwm = speed*arr/100;
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
  GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, spwm);//����
	TIM_SetCompare4(TIM4, arr-spwm);//����
	
}
void MotorPWM_RightSpin(int speed)
{
	int spwm = speed*arr/100;
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
  GPIO_SetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, arr-spwm);
	TIM_SetCompare4(TIM4, spwm);
	
}

void MotorPWM_Stop(int time)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
  GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, 0);
	delay_ms(time);
}

void MotorPWM_Stopall(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
  GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	TIM_SetCompare3(TIM4, 0);
	TIM_SetCompare4(TIM4, 0);
}

void MotorPWM_Steering(int left,int right)
{	int spwm_l = left*arr/100;
	int spwm_r = right*arr/100;
	if(left>=100){
	spwm_l=arr;}
	if(left<=0){
	spwm_l=0;}
	
	if(right>=100){
	spwm_r=arr;}
	if(right<=0){
	spwm_r=0;}
	
	TIM_SetCompare3(TIM4, spwm_r);//you
	TIM_SetCompare4(TIM4, spwm_l);//zuo
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);//zuo
  GPIO_ResetBits(GPIOB, GPIO_Pin_7);//you
	
}
//�������
void IRAvoidInit(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_INIT(GPIOB,GPIO_Pin_1,GPIO_Mode_IPU,GPIO_Speed_50MHz);//��ʼ��red
	GPIO_INIT(GPIOA,GPIO_Pin_5,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);//��ʼ��LED
	GPIO_INIT(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);//��ʼ��beep

	GPIO_ResetBits(GPIOA,GPIO_Pin_5);//LED��ʼ����
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
}


void AVoidRun(void){
	AVOID_IO = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
	
	if(AVOID_IO == 1)
	{
	  GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	  GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		MotorPWM_Forward(50);
	}
	if(AVOID_IO == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
		MotorPWM_Stop(500);
		MotorPWM_Backward(50);
		delay_ms(100);
		MotorPWM_LeftSpin(50);
		delay_ms(500);
	}
}
void trace_init(){
	GPIO_INIT(GPIOA,GPIO_Pin_7,GPIO_Mode_IPU,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOB,GPIO_Pin_0,GPIO_Mode_IPU,GPIO_Speed_50MHz);
	TIM4_PWM_Init();
}
void trace_begin(int speed1,int speed2){
	//while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET){
	//USART_ReceiveData(USART2);
	SEARCH_R_IO=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7); 
  SEARCH_L_IO=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);//��ȡ��������
	 if(SEARCH_R_IO == 1 && SEARCH_L_IO==1)          //ֱ�� LED�����������������ⶼ�������źţ�
	{
		//MotorPWM_Forward(0);
		MotorPWM_RightSpin(100);
		//delay_ms(100);
	}
	else {
			if(SEARCH_R_IO==1&& SEARCH_L_IO==0)         //��ת LED��
			{
				MotorPWM_Steering(speed1,speed2);
			}
			else if(SEARCH_R_IO==0&& SEARCH_L_IO==1)         //��ת LED��
			{	
				MotorPWM_Steering(speed2,speed1);				
			}
			else
			{
				MotorPWM_Forward(40);			
			}
		}
				
}

//�����л�
void KeyScanTask(){
	static u8 keypre = 0;
	if((keypre == 0)&& (KEY==1)){
		keypre = 1;
		switch(keyMode)
		{
			case 1:keyMode = 2;break;
			case 2:keyMode = 1;break;
			default:break;
		}
	}
	if(!KEY)
	{
		keypre = 0;
	}
}




//������
//�߰��ֺ���
void main_motor_8(){
		int i;
		int j;
		TIM4_PWM_Init();
		delay_init();//��ʼ��
		MotorPWM_Stopall();//��������
		
		i=0;
		MotorPWM_Steering(68,100);
		for(;i<4;i++){
		delay_ms(1000);}
		MotorPWM_Steering(100,70);	
		
		j=0;
		for(;j<3;j++){
		delay_ms(1400);}
	  MotorPWM_Stopall();
}
//���ٺ���
void main_speed(){
		int speed;	
		int speed2;
		TIM4_PWM_Init();
		delay_init();//��ʼ��
		MotorPWM_Stopall();//��������
		
		speed=20;
		for(;speed<=100;speed++){
			MotorPWM_Forward(speed);
			delay_ms(100);
	}
		MotorPWM_Forward(100);
		delay_ms(1800);
		
		speed2=100;
		for(;speed2>=0;speed2--){
			MotorPWM_Forward(speed2);
			delay_ms(100);
		
	}
		MotorPWM_Stopall();
}




//ѭ�������
void main_avoid_trace(int speed1,int speed2){
	TIM4_PWM_Init();
	IRAvoidInit();
	trace_init();
	delay_init();
while(1){
	AVoidRun();
	trace_begin(speed1,speed2);
	}
}

//����ѭ��������
void main_trace(int speed1,int speed2){
	USART2_Init();
  delay_init();
	trace_init(); 
	while(1){
	trace_begin(speed1, speed2);
	}
}

//�������������
void main_red_avoid(){
	IRAvoidInit();
	TIM4_PWM_Init();
	delay_init();
	while(1){
		AVoidRun();
	}
}

//ѭ��������֮��ص����
void main_trace_avoid(int speed1,int speed2){
	IRAvoidInit();
	TIM4_PWM_Init();
	trace_init(); 
	delay_init();
	
	while(1){
	AVOID_IO = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	if(AVOID_IO == 1)
	{
	 trace_begin(speed1,speed2);
		delay_ms(10);
		MotorPWM_Stopall();
		delay_ms(10);
	}
	if(AVOID_IO == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOC,GPIO_Pin_3);
		delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);
		MotorPWM_Stop(500);
		delay_ms(100);
		MotorPWM_RightSpin(100);
		delay_ms(200);
		MotorPWM_Forward(50);
		delay_ms(700);
		MotorPWM_LeftSpin(100);
		delay_ms(200);
		MotorPWM_Forward(50);
		delay_ms(700);
		MotorPWM_LeftSpin(100);
		delay_ms(200);
		MotorPWM_Forward(50);
	}
	
	}

}


//�����л�������
void main_key_switch(){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		KEY_Init();//�ɰ�LED ������ key����ʼ����
		delay_init();
		IRAvoidInit();
		TIM4_PWM_Init();	
		trace_init();
		BEEP_RESET;
		LED_RESET;
		while(1){
		KeyScanTask();
		if(keyMode==1){
			//BEEP_SET;
			//delay_ms(1000);
			//BEEP_RESET;
			trace_begin(50,35);
			}
		else if(keyMode==2){
			LED_SET;
			//delay_ms(1000);
			//LED_RESET;
			AVoidRun();
			}
		else{
			break;}
		}
	}		
char USART_IRQHandler(){
	if(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == SET){
		return USART_ReceiveData(USART2);
	}
	else return 'M';
}
void TheLast(speed1,speed2){
	IRAvoidInit();
	TIM4_PWM_Init();
	trace_init(); 
	delay_init();
	KEY_Init();
	init_all();
	while(1){
	char command;
	command=USART_IRQHandler();
	if(command=='E'){return ;}
	AVOID_IO = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	if(AVOID_IO == 1)//�����ȡ��û���ϰ���
	{
	 trace_begin(speed1,speed2);
		delay_ms(10);
		MotorPWM_Stopall();
		delay_ms(10);
	}
	if(AVOID_IO == 0)//�����ȡ�����ϰ���
	{
			//������������඼���ϰ���򱨾�
				int index;
				index=find_way();
				switch(index){
				case 0:
					GPIO_SetBits(GPIOA,GPIO_Pin_5);//LED
					GPIO_SetBits(GPIOC,GPIO_Pin_3);//beep
					delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					GPIO_ResetBits(GPIOC,GPIO_Pin_3);
					delay_ms(500);
					Motor_Stop(1000);
					break;
				case 1:
					//�����������������ϰ�����������������
					GPIO_SetBits(GPIOA,GPIO_Pin_5);//LED
					GPIO_SetBits(GPIOC,GPIO_Pin_3);//beep
					delay_ms(1000);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					GPIO_ResetBits(GPIOC,GPIO_Pin_3);
					MotorPWM_Stop(500);
					delay_ms(100);
					MotorPWM_LeftSpin(100);
					delay_ms(200);
					MotorPWM_Forward(50);
					delay_ms(700);
					MotorPWM_RightSpin(100);
					delay_ms(200);
					MotorPWM_Forward(50);
					delay_ms(700);
					MotorPWM_RightSpin(100);
					delay_ms(200);
					MotorPWM_Forward(50);
					break;
				case 2:
					//������������Ҳ����ϰ�������������ұ���
					GPIO_SetBits(GPIOA,GPIO_Pin_5);
					GPIO_SetBits(GPIOC,GPIO_Pin_3);
					delay_ms(1000);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					GPIO_ResetBits(GPIOC,GPIO_Pin_3);
					MotorPWM_Stop(500);
					delay_ms(100);
					MotorPWM_RightSpin(100);
					delay_ms(200);
					MotorPWM_Forward(50);
					delay_ms(700);
					MotorPWM_LeftSpin(100);
					delay_ms(200);
					MotorPWM_Forward(50);
					delay_ms(700);
					MotorPWM_LeftSpin(100);
					delay_ms(200);
					MotorPWM_Forward(50);
					break;
				default:
					GPIO_SetBits(GPIOA,GPIO_Pin_5);//LED
					GPIO_SetBits(GPIOC,GPIO_Pin_3);//beep
					delay_ms(500);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
					GPIO_ResetBits(GPIOC,GPIO_Pin_3);
					delay_ms(500);
					Motor_Stop(1000);
					break;
			}
	}
	
	}
	
}