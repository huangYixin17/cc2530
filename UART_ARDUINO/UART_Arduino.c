/*****���F******/

#include "ioCC2530.h" 

 #define   LED3 P1_0
 #define   LED4 P1_1
#define    sw1 P2_3
 /* ===================���ɨ��= ======================== */ 
 void Delay(unsigned int t)
 {
   while (t-- );
 }
 /* = =================�ݤf��l�ƨ��===================== */ 
 void Init_Port()
 {
   //�NP1_0�BP1_1�MP1_4�]�m���q��I/O�ݤf�\��
   P1SEL &= ~ 0x03 ;   
   // �NP1_0�BP1_1�MP1_4���ݤf�ǿ�覡�]�m����X
   P1DIR |= 0x03 ;   
   P2SEL &=~0x08;
   P2DIR &=~0x08;
   P2INP &=~0x88;
   sw1=0;
   LED3 = 0 ;
   LED4 = 0 ;
 }
int i=0;
 void servo1()
 {
   
   for(i=0;i<10;i++)
   {
     LED3 = 1 ;
     Delay( 10000 );
     LED3 = 0 ;
     Delay( 40000 );
     Delay( 40000 );
   }
   
 }

 /* ====================�D���========================== */ 
 void main()
 {
   Init_Port();           // ��l�Ƴq��I/O�ݤf
   Init_Port();           // ��l�ƥ~�����_
   while ( 1 )
   {
     if(sw1==1)
   {
     Delay(100);
     if(sw1==1)
     {
       while(sw1==1);
       servo1();      // �]���O
     }
   } 
   }
}