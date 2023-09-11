#include "stm32f10x.h"
#include "motor.h"
#include "blueteeth.h"
#include "motorPWM.h"
#include "trace.h"
#include "ultrasonic.h"
#include "control.h"
int main(void)
{ 
	init_all();
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//delay_ms(2000);
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//delay_ms(2000);
	//steering_gear_left(90,100);
	while(1){
	run();
}
}