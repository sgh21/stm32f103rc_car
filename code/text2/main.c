#include"stm32f10x.h"
#include"delay.h"
#include"IO_INIT.h"
#include"motor.h"

int main(void){
	Motor_Init();
	delay_init();
	Motor_Forward(2000);
	Motor_Stop(1000);
	Motor_Left(2000);
	Motor_Stop(1000);
	Motor_Right(2000);
	Motor_Stop(1000);
	Motor_LeftSpin(2000);
	Motor_Stop(1000);
	Motor_RightSpin(2000);
	Motor_Stop(1000);
	Motor_Backward(2000);
	while(1){}
}
