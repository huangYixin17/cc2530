#include "ioCC2530.h"

#define  LED6   P1_4
#define  LED3   P1_0
#define  LED4   P1_1
/*===================延?函?=========================*/
void Delay(unsigned int t)
{
  while(t--);
}
/*==================端口初始化函?=====================*/
void Init_Port()
{
  //?P1_0、P1_1和P1_4?置?通用I/O端口功能
  P1SEL &= ~0x13;   
  //?P1_0、P1_1和P1_4的端口??方式?置??出
  P1DIR |= 0x13;   
  LED6 = 0;
  LED3 = 0;
  LED4 = 0;
}
/*==================跑??子函?=====================*/
void LED_Running()
{
  LED3 = 1;
  Delay(50000);
  LED4 = 1;
  Delay(50000);
  LED3 = 0;
  Delay(50000);
  LED4 = 0;
  Delay(50000);
}

void main()
{
  Init_Port();          //初始化通用I/O端口
  while(1)
  {
    LED_Running();     //跑??
  }
}