/*****馬達******/

#include "ioCC2530.h" 

 #define   LED3 P1_0
 #define   LED4 P1_1
#define    sw1 P2_3
 /* ===================延時函數= ======================== */ 
 void Delay(unsigned int t)
 {
   while (t-- );
 }
 /* = =================端口初始化函數===================== */ 
 void Init_Port()
 {
   //將P1_0、P1_1和P1_4設置為通用I/O端口功能
   P1SEL &= ~ 0x03 ;   
   // 將P1_0、P1_1和P1_4的端口傳輸方式設置為輸出
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

 /* ====================主函數========================== */ 
 void main()
 {
   Init_Port();           // 初始化通用I/O端口
   Init_Port();           // 初始化外部中斷
   while ( 1 )
   {
     if(sw1==1)
   {
     Delay(100);
     if(sw1==1)
     {
       while(sw1==1);
       servo1();      // 跑馬燈
     }
   } 
   }
}