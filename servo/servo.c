/*****馬達******/

#include "ioCC2530.h" 

 #define   LED3 P1_0
 #define   LED4 P1_1
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
   LED3 = 0 ;
   LED4 = 0 ;
 }
 /* ==================跑馬燈子函數=============== ====== */ 
 void LED_Running()
 {
  LED4 = 1 ;
   Delay( 50000 );
   LED4 = 0 ;
   Delay( 50000 );
 }
 void LED_Running1()
 {
   LED3 = 1 ;
   Delay( 60000 );
   Delay( 60000 );
   Delay( 25000 );  //7.3v 145000 delay
   LED3 = 0 ;
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
   LED_Running1();
   //LED_Running1();
 /* 先清除引腳標誌位，再清除端口標誌位，否則會不斷進入中斷*/ 
   P1IFG &= ~ 0x04 ;         //軟件清除P1_2引腳的標誌位
   P1IF = 0 ;                // 軟件清除P1端口組的標誌位
 }
 /* ====================主函數========================== */ 
 void main()
 {
   Init_Port();           // 初始化通用I/O端口
   Init_INTP ();           // 初始化外部中斷
   while ( 1 )
   {
     LED_Running();      // 跑馬燈
   }
}