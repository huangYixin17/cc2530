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
   P1SEL &= ~ 0x06 ;   //將P1_1,P1_2設置為通用I/O端口功能
   P1DIR |= 0x06 ;   // 將P1_1,P1_2的端口傳輸方式設置為輸出
   P1SEL &= ~ 0x01 ;//將P1_0設置為通用I/O端口功能
   P1DIR &= ~0x01 ;  //將P1_0設置為輸入
   P1INP &= ~ 0x01;          // 將P1_0的端口輸入方式設置為：上拉/下拉 
  P2INP &= ~ 0x60 ;          // 將P0端口和P1端口引腳設置為：上拉 
  
   LED1=0;
 }

 void main()
 {
   Init_Port();           // 初始化通用I/O端口
  
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
