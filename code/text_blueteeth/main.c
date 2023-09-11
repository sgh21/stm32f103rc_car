#include "stm32f10x.h"
#include"motor.h"
#include"blueteeth.h"

void ControlMotor(uint8_t state)//add other mode and function
{
	Motor_Init();
  if (state == 0)
  {
    Motor_Stop(1000);
  }
  else if (state==1)
  {
		
		Motor_Forward(2000);
  }
	else if (state==2)
  {
		
		Motor_LeftSpin(2000);
  }
	else if (state==3)
  {
		
		Motor_RightSpin(2000);
  }
	else if (state==4)
  {
		
		Motor_Backward(2000);
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
  }
}
