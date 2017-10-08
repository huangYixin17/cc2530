#include "ioCC2530.h" 

#define  reciver P1_1
#define  servo  P1_0
#define  LED1  P1_3
#define  LED2  P1_4
/* ===================延時函數= ======================== */ 
 void Delay(unsigned int t)
 {
   while (t-- );
 }
 /* = =================端口初始化函數===================== */
 void Init_Port()
 {
   //將P1_0設置為通用I/O端口功能
   P1SEL &= ~ 0x19 ;   
   // 將P1_0的端口傳輸方式設置為輸出
   P1DIR |= 0x19 ;   
   P1SEL &= ~ 0x02 ;
   P1DIR &= ~0x02 ;  
   P1INP &= ~ 0x02;          // 將P1_2的端口輸入方式設置為：上拉/下拉 
  P2INP &= ~ 0x60 ;          // 將P0端口和P1端口引腳設置為：上拉 
  servo=0;
   LED1=0;
 }
 /* = =================馬達轉一圈===================== */
 void servo_1()
 {
   servo = 1 ;
   Delay( 45000 );
   servo = 0 ;
 }
 /* = =================偵測紅外線===================== */
 void reciver_1()
 {
  if(reciver == 0) 
    {
       LED1=1;
       Delay( 50000 );
       LED1=0;
       Delay( 50000 );
     }
 }
/* ============= ==外部中斷初始化函數================== */ 
 void Init_INTP()
 {
   IEN2 |= 0x10 ;          // 端口1中斷使能
   P1IEN |= 0x04 ;         // 端口P1_2外部中斷使能
   PICTL |= 0x02 ;         // 端口P1_0到P1_3下降沿觸發
   EA = 1 ;                // 使能總中斷
 }
 /* ================外部中斷1服務函數==================== */ 
 #pragma vector = P1INT_VECTOR      // 外部中斷1的向量入口
__interrupt void Int1_Sevice()
 {
   servo_1();
 /* 先清除引腳標誌位，再清除端口標誌位，否則會不斷進入中斷*/ 
   P1IFG &= ~ 0x04 ;         //軟件清除P1_2引腳的標誌位
   P1IF = 0 ;                // 軟件清除P1端口組的標誌位
 }
 void main()
 {
   Init_Port();           // 初始化通用I/O端口
   Init_INTP ();           // 初始化外部中斷
   void reciver_1();
   while(1)
   {
   LED2=1;
   Delay(50000);
   LED2=0;
   Delay(50000);
   }
 }
