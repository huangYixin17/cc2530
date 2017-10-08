#include <iocc2530.h>
#define uint unsigned int
#define uchar unsigned char
//定義控制LED 燈的端口
#define LED1 P1_0 //定義LED1為P10口控制
void inittimer(void)
{
CLKCONCMD &= ~0x40; //晶振
while(!(SLEEPSTA & 0x40)); //等待晶振穩定
CLKCONCMD &= ~0x07; //TICHSPD分頻，CLKSPD 不分頻
CLKCONCMD |= 0x38; // time1的定時時鐘為250KHz 
SLEEPCMD |= 0x04; //關閉不用的RC 振盪器
P0SEL = 0x00;
P1DIR |= 0xff;
P0 |= 0xaa;
PERCFG |= 0x40; //timer1 io 備用2
P2SEL &= ~0X10;
P2DIR |= 0XC0;
P1SEL |= 0x01; //P1 timer 通道2 P1_0
P1DIR |=0x01;  //time 1 init
T1CC2H = 0x0c;//1S 的佔空比
T1CC2L = 0x35;
T1CC0H = 0x7a;//1S的周期時鐘
T1CC0L = 0x12;
T1CCTL2 = 0x1c; // 模式選擇
T1CTL = 0x06; //250KHz8分頻
}
void main(void)
{
inittimer();
while(1);
}