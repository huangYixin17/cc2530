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
	//Timer�q�D?�m
    P1SEL |= 0x01;              //Timer1�q�D2�M�g��P1_0�A�\����
    PERCFG |= 0x40;             //�ƥΦ�m2�A?���H��
    P2SEL &= ~0x10;             //�۹��Timer4�ATimer1�u��
    P2DIR |= 0xC0;              //�w?���q�D2-3�㦳�Ĥ@�u������
    P1DIR |= 0x01;				//P1_0����X
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
    
	//T1CCTL0 |= 0x04;      		//<2>??�q�D0��?�X��?�Ҧ�
    //Timer�Ҧ�?�m
    T1CTL = 0x02;               //250KHZ�����W�A�ҼҦ�
    
    //�ھ�Table7-1�AP1_0������Timer1�q�D2�i����
	
    T1CCTL2 = 0x1C;             //����۵���1�A�p�ƾ��^0�h�M�s
	
    //��Timer�q�D0���
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM�H���g��?1ms�A�W�v��1KHZ
	
	

	
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//���16MHZ RCOSC���t�ή�����
	while(!(CLKCONSTA & 0X40)); //���ݮ���í�w
	CLKCONCMD &=~0XF8;			//���32MHz���D����
	
	CLKCONCMD |= 0x38;          //Timer�аO��X��250kHz
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