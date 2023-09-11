
#include"blueteeth.h"

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
