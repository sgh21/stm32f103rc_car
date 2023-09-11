#include "stm32f10x.h"
//#include "motor.h"
//#include "blueteeth.h"
//#include "motorPWM.h"
//#include "trace.h"
#include "ultrasonic.h"
#include "control.h"
#include "avoid_trace.h"
#include "blueteeth.h"
void ControlMotor(uint8_t state)//add other mode and function
{
  if (state == 0)
  {
    MotorPWM_Stop(1000);
  }
  else if (state==1)
  {
		MotorPWM_Forward(50);
  }
	else if (state==2)
  {
		MotorPWM_LeftSpin(50);
  }
	else if (state==3)
  {
		MotorPWM_RightSpin(50);
  }
	else if (state==4)
  {
		 MotorPWM_Backward(50);
  }
}

int main(void)
{
  USART2_Init();
  delay_init();
  while (1)
  {
    char command = USART2_ReceiveChar();
    
    if (command == '0')
    {
      ControlMotor(0);  
    }
    else if (command == 'W')
    {
      ControlMotor(1);  
    }
		 else if (command == 'A')
    {
      ControlMotor(2);  
    }
		 else if (command == 'S')
    {
      ControlMotor(3);  
    }
		 else if (command == 'D')
    {
      ControlMotor(4);  
    }
		else if (command=='C'){
			TheLast();
		}
  }
}
