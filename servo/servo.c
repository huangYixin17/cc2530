#include "ioCC2530.h"

#define LED4 P1_1
#define LED5 P1_0
#define sw1 P2_3
#define sw2 P2_4


void set_main_clock();
void PortInit();
void T1Init();
void Delay(unsigned int t);
void test();
void servo1();
void servo2();
void main()
{
  PortInit();
  T1Init();
  while(1){
    test();
  }

}
void test()
{
    if(sw1==0)
    {
      Delay(500);
      if(sw1==0)
      {
         while(sw1==0);
         servo1();
     }
    }
    if(sw2==0)
    {
      Delay(500);
      if(sw2==0)
      {
         while(sw2==0);
         servo2();
      }
   }
}




void Delay(unsigned int t){
	while(t--);
}

void PortInit()
{
	//Timer通道?置
    P1SEL |= 0x01;              //Timer1通道2映射至P1_0，功能選擇
    PERCFG |= 0x40;             //備用位置2，?明信息
    P2SEL &= ~0x10;             //相對於Timer4，Timer1優先
    P2DIR |= 0xC0;              //定?器通道2-3具有第一優先順序
    P1DIR |= 0x01;				//P1_0為輸出
    P2SEL &=~0x18;
    P2DIR &=~0x18;
    P2INP &=~0x98;
    P1SEL &=~0x02;
    P1DIR |=0x02;
    LED4=0;
    sw1=0;
    sw2=0;
}


void T1Init()
{
    
	//T1CCTL0 |= 0x04;      		//<2>??通道0的?出比?模式
    //Timer模式?置
    T1CTL = 0x02;               //250KHZ不分頻，模模式
    
    //根據Table7-1，P1_0必須裝Timer1通道2進行比較
	
    T1CCTL2 = 0x1C;             //比較相等為1，計數器回0則清零
	
    //裝Timer通道0初值
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM信號週期?1ms，頻率為1KHZ
	
	

	
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
	
	CLKCONCMD |= 0x38;          //Timer標記輸出為250kHz
}

void servo1()
{ 
        T1CC2H = 0x07;
        T1CC2L = 0x3a;
        int i;
        for(i=0;i<10;i++)
        {
          Delay(50000);
        }
        T1CC2H = 0x09;
        T1CC2L = 0xc5;
}

void servo2()
{ 
        T1CC2H = 0x07;
        T1CC2L = 0x3a;
        int i;
        for(i=0;i<20;i++)
        {
          Delay(48000);
        }
        T1CC2H = 0x09;
        T1CC2L = 0xc5;
}