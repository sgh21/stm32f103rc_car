#include"IO_INIT.h"
void GPIO_INIT(GPIO_TypeDef* CPIOx,u16 GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,GPIOSpeed_TypeDef GPIO_Speed){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed;
	GPIO_Init(CPIOx,&GPIO_InitStructure);
}