#include "ioCC2530.h" 

#define  reciver P1_0
#define  LED1  P1_1
#define  LED2  P1_2
 void Delay(unsigned int t)
 {
   while (t-- );
 }
 void Init_Port()
 {
   P1SEL &= ~ 0x06 ;   //�NP1_1,P1_2�]�m���q��I/O�ݤf�\��
   P1DIR |= 0x06 ;   // �NP1_1,P1_2���ݤf�ǿ�覡�]�m����X
   P1SEL &= ~ 0x01 ;//�NP1_0�]�m���q��I/O�ݤf�\��
   P1DIR &= ~0x01 ;  //�NP1_0�]�m����J
   P1INP &= ~ 0x01;          // �NP1_0���ݤf��J�覡�]�m���G�W��/�U�� 
  P2INP &= ~ 0x60 ;          // �NP0�ݤf�MP1�ݤf�޸}�]�m���G�W�� 
  
   LED1=0;
 }

 void main()
 {
   Init_Port();           // ��l�Ƴq��I/O�ݤf
  
  while(1)
   {
      if(reciver == 0) 
      {
       LED1=1;
       Delay( 50000 );
       Delay( 50000 );
       Delay( 50000 );
       Delay( 50000 );
       LED1=0;
       Delay( 50000 );
        }
   }
 }
