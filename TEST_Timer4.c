#include "iocc2530.h"

#define sw1 P2_3
#define testLED1 P1_0
#define testLED2 P1_1
#define testLED3 P1_2
#define testLED4 P1_3
#define testLED5 P1_4
int overtime_five_min=0;
int countsecond=0;
void Delay(unsigned int t);
void InitT4();
void PortInit();

void main()
{
	PortInit();
	while(1)
	{
		if(sw1==0)
		{
			Delay(50000);
			if(sw1==0)
			{
				while(sw1==0);
                                testLED5=1;
                                Delay(50000);
                                Delay(50000);
                                testLED5=0;
                                Delay(50000);
                                Delay(50000);
                                while(overtime_five_min<6)
                                {
                                  InitT4();
				}
                                T4CTL &= ~0x08 ; 
                                overtime_five_min=0;
                                testLED1=1;
				Delay(50000);
				Delay(50000);
				Delay(50000);
				Delay(50000);
				testLED1=0;
				int i;
				for(i=0;i<10;i++)
				{
					Delay(50000);
				}
			}
		}	
	}
}

void PortInit()
{
	P2SEL &=~0x08;
	P2DIR &=~0x08;
	P2INP &=~0x88;
	P1SEL &=~0x1F;
	P1DIR |=0x1F;
	sw1=0;
	testLED1=0;
	testLED2=0;
	testLED3=0;
	testLED4=0;
        testLED5=0;
}

void InitT4()
{
T4CTL |= 0x08 ;    //????????
T4IE = 1;    //???中斷??T3中斷
T4CTL|=0XE0;    //128 ??;,128/16000000*N=0.5S,N=65200
T4CTL &= ~0X03;    //????Ψ? 00＿0xff   65200/256=254(欿
T4CTL |=0X10; //   ???
EA = 1;     //???中斷	
}
#pragma vector = T4_VECTOR     //定濿?T3
__interrupt void T4_ISR(void)
{
IRCON = 0x00;    //清中???調也可??l件自?????
if(++countsecond>254)   //254 次中???LED???，?Τ?輪'?為0.5秒濿??
{
  //++overtime_five_min;
  countsecond = 0;   // 計數清零 
  testLED2=1;
  Delay(50000);
  Delay(50000);
  Delay(50000);
  Delay(50000);
  testLED2=0;
  Delay(50000);
  Delay(50000);
  Delay(50000);
  Delay(50000);
  
  overtime_five_min++;
  if(overtime_five_min==6)
  {
    testLED3=1;
    Delay(50000);
    Delay(50000);
    //UR0SendString("1\n");
    //overtime_five_min=0;
    Delay(50000);
    Delay(50000);
    Delay(50000);
    Delay(50000);
    Delay(50000);
    
  }
  testLED3=0;
  
}
}

void Delay(unsigned int t)
{
	while(t--);
}