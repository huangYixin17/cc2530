#include <iocc2530.h>
#define uint unsigned int
#define uchar unsigned char
//�w�q����LED �O���ݤf
#define LED1 P1_0 //�w�qLED1��P10�f����
void inittimer(void)
{
CLKCONCMD &= ~0x40; //����
while(!(SLEEPSTA & 0x40)); //���ݴ���í�w
CLKCONCMD &= ~0x07; //TICHSPD���W�ACLKSPD �����W
CLKCONCMD |= 0x38; // time1���w�ɮ�����250KHz 
SLEEPCMD |= 0x04; //�������Ϊ�RC ������
P0SEL = 0x00;
P1DIR |= 0xff;
P0 |= 0xaa;
PERCFG |= 0x40; //timer1 io �ƥ�2
P2SEL &= ~0X10;
P2DIR |= 0XC0;
P1SEL |= 0x01; //P1 timer �q�D2 P1_0
P1DIR |=0x01;  //time 1 init
T1CC2H = 0x0c;//1S �����Ť�
T1CC2L = 0x35;
T1CC0H = 0x7a;//1S���P������
T1CC0L = 0x12;
T1CCTL2 = 0x1c; // �Ҧ����
T1CTL = 0x06; //250KHz8���W
}
void main(void)
{
inittimer();
while(1);
}