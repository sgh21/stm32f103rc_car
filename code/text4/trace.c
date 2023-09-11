#include"trace.h"
uint8_t SEARCH_R_IO;                                 //�������ڶ�ȡ�Ҳ������չܵ�IO��״̬
uint8_t SEARCH_L_IO;
void trace_init(){
	GPIO_INIT(GPIOA,GPIO_Pin_7,GPIO_Mode_IPU,GPIO_Speed_50MHz);
	GPIO_INIT(GPIOB,GPIO_Pin_0,GPIO_Mode_IPU,GPIO_Speed_50MHz);
	MotorPWM_Init();
}
void trace_begin(int speed,int d_speed){
	//while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET){
	while(1){
	//USART_ReceiveData(USART2);
	SEARCH_R_IO=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7); 
  SEARCH_L_IO=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
	 if(SEARCH_R_IO == 1 && SEARCH_L_IO==1)          //ֱ�� LED����
	{
		MotorPWM_Forward(speed,0);
	}
	else if(SEARCH_R_IO==1&& SEARCH_L_IO==0)         //��ת LED��
	{
			MotorPWM_Right(speed,d_speed);
			
	}
	else if(SEARCH_R_IO==0&& SEARCH_L_IO==1)         //��ת LED��
	{
		
		MotorPWM_Left(speed,d_speed);
	}
	else
	{
		MotorPWM_Forward(speed,0);
	}}return;
}