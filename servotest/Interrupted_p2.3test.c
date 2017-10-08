#include "ioCC2530.h"

#define  LED6   P1_4
#define  LED3   P1_0
#define  LED4   P1_1
/*===================��?��?=========================*/
void Delay(unsigned int t)
{
  while(t--);
}
/*==================�ݤf��l�ƨ�?=====================*/
void Init_Port()
{
  //?P1_0�BP1_1�MP1_4?�m?�q��I/O�ݤf�\��
  P1SEL &= ~0x13;   
  //?P1_0�BP1_1�MP1_4���ݤf??�覡?�m??�X
  P1DIR |= 0x13;   
  LED6 = 0;
  LED3 = 0;
  LED4 = 0;
}
/*==================�]??�l��?=====================*/
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
/*===============�~����?��l�ƨ�?==================*/
void Init_INTP()
{
  IEN2 |= 0x02;         //�ݤf1��?�ϯ�
  P2IEN |= 0x08;        //�ݤfP1_2�~����?�ϯ�
  PICTL |= 0x08;        //�ݤfP1_0��P1_3�U���u�D? 
  EA = 1;               //�ϯ�?��?
}
/*================�~����?1�A?��?====================*/
#pragma vector = P1INT_VECTOR     //�~����?1���V�q�J�f
__interrupt void Int1_Sevice()
{
  LED6 = ~LED6;
/*���M����??�Ӧ�A�A�M���ݤf?�Ӧ�A�_??��??�J��?*/
  P2IFG &= ~ 0x08;        //?��M��P1_2��?��?�Ӧ�
  P2IF = 0;               //?��M��P1�ݤf?��?�Ӧ�
}
/*====================�D��?==========================*/
void main()
{
  Init_Port();          //��l�Ƴq��I/O�ݤf
  Init_INTP();          //��l�ƥ~����?
  while(1)
  {
    LED_Running();     //�]??
  }
}