#include "stm32f10x.h"
#include"motor.h"
#include"blueteeth.h"
#include"motorPWM.h"
#include"trace.h"
int main(void)
{
  USART2_Init();
  delay_init();
	trace_init(); 
	trace_begin(50,35);
}
