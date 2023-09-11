#include "stm32f10x.h"                  // Device header

//按键控制蜂鸣器发声：通过一次按键控制蜂鸣器发声10次，之后静音。每次发声持续1s，间隔1s。
//蜂鸣器IO口定义
#define BEEP_PIN      GPIO_Pin_3
#define BEEP_GPIO     GPIOC
#define BEEP_SET      GPIO_SetBits(BEEP_GPIO,BEEP_PIN)
#define BEEP_RESET    GPIO_ResetBits(BEEP_GPIO,BEEP_PIN)
#define LED_RESET	  GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define LED_SET	      GPIO_SetBits(GPIOA,GPIO_Pin_5) 
//读取按键
#define KEY  GPIO_ReadInputDataBit(GPIOC,ENABLE);             //读取按键0

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);        //使能PORTC时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                   //PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //IO口速度为50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);                       //初始化GPIOC2

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                   //PC3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //IO口速度为50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);                       //初始化GPIOC3
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);  //使能PA，PD端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;          //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO口速度为50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //根据设定参数初始化GPIOA.8
	GPIO_SetBits(GPIOA,GPIO_Pin_5);        
}

void keysacn()
{
	int val;
	val=KEY;                                                    //读取按键
	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))             //当按键没有被按下时，一直循环
	{
		val=KEY;                                                  //词句可省略，可让循环跑空
	}
	delay_init();
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))              //当按键被按下时
	{
		delay_ms(10);                                             //延时10ms
		val=KEY;                                                  //读取数字端口PC2口电平值赋给val
		if(val==1)                                                //第二次判断按键是否被按下
		{
			BEEP_SET;                                               //蜂鸣器响
			
		}
		else
			BEEP_RESET;                                             //蜂鸣器停止
	}
}

int a = 0;           //鸣响次数清零
int main(void)
{
	KEY_Init();
	
	BEEP_RESET;
	LED_RESET;
	//鸣响器响10次后关闭
	while(1)
	{
		keysacn();//检测有没有按键
		while(a<10)
		{
			BEEP_SET;//蜂鸣器响
			LED_SET;
			delay_ms(1000);//蜂鸣器响1s
			
			BEEP_RESET;//蜂鸣器停止
			LED_RESET;
			delay_ms(1000);//蜂鸣器停止1s
			
			a++;
		}
		a=0;//鸣响次数清零，等待下一次按键
	}
}
