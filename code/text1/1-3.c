#include "stm32f10x.h"                  // Device header

//�������Ʒ�����������ͨ��һ�ΰ������Ʒ���������10�Σ�֮������ÿ�η�������1s�����1s��
//������IO�ڶ���
#define BEEP_PIN      GPIO_Pin_3
#define BEEP_GPIO     GPIOC
#define BEEP_SET      GPIO_SetBits(BEEP_GPIO,BEEP_PIN)
#define BEEP_RESET    GPIO_ResetBits(BEEP_GPIO,BEEP_PIN)
#define LED_RESET	  GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define LED_SET	      GPIO_SetBits(GPIOA,GPIO_Pin_5) 
//��ȡ����
#define KEY  GPIO_ReadInputDataBit(GPIOC,ENABLE);             //��ȡ����0

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);        //ʹ��PORTCʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                   //PC2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);                       //��ʼ��GPIOC2

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                   //PC3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC,&GPIO_InitStructure);                       //��ʼ��GPIOC3
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);  //ʹ��PA��PD�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;          //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //�����趨������ʼ��GPIOA.8
	GPIO_SetBits(GPIOA,GPIO_Pin_5);        
}

void keysacn()
{
	int val;
	val=KEY;                                                    //��ȡ����
	while(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))             //������û�б�����ʱ��һֱѭ��
	{
		val=KEY;                                                  //�ʾ��ʡ�ԣ�����ѭ���ܿ�
	}
	delay_init();
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2))              //������������ʱ
	{
		delay_ms(10);                                             //��ʱ10ms
		val=KEY;                                                  //��ȡ���ֶ˿�PC2�ڵ�ƽֵ����val
		if(val==1)                                                //�ڶ����жϰ����Ƿ񱻰���
		{
			BEEP_SET;                                               //��������
			
		}
		else
			BEEP_RESET;                                             //������ֹͣ
	}
}

int a = 0;           //�����������
int main(void)
{
	KEY_Init();
	
	BEEP_RESET;
	LED_RESET;
	//��������10�κ�ر�
	while(1)
	{
		keysacn();//�����û�а���
		while(a<10)
		{
			BEEP_SET;//��������
			LED_SET;
			delay_ms(1000);//��������1s
			
			BEEP_RESET;//������ֹͣ
			LED_RESET;
			delay_ms(1000);//������ֹͣ1s
			
			a++;
		}
		a=0;//����������㣬�ȴ���һ�ΰ���
	}
}
