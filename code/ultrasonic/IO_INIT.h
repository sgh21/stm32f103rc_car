#ifndef IO_INIT_H
#define IO_INIT_H
#include"stm32f10x.h"
void GPIO_INIT(GPIO_TypeDef* CPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,GPIOSpeed_TypeDef GPIO_Speed);
#endif // !IO_INIT_H