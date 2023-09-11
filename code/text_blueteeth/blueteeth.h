#include "stm32f10x.h"
#include"motor.h"
#include"IO_INIT.h"
void USART2_Init(void);
void USART2_SendChar(char ch);
char USART2_ReceiveChar(void);//add other function with the received char