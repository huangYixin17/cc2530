#include "ioCC2530.h"

#define servopin P1_0
#define buzzerpin P1_6 
#define testLED P1_1
#define testLED2 P1_3
#define testLED3 P1_4
#define overtime P1_2
#define sw1 P0_7
unsigned char DataRecieve;		//讀取緩衝區資料的變數
unsigned char Flag = 0;			//接收指令標誌的變數
int countsecond=0;
int overtime_five_min=0;

void PortInit();
void T1Init();
void InitT3();
void InitT4();
void Delay(unsigned int t);
void servo1();
void servo2();
void buzzer();
void set_main_clock();	//設置主時鐘
void Init_UART0();		//序列埠0的初始化函數
void UR0SendByte(unsigned char data);	//UR0發送字元函數
void UR0SendString(unsigned char *str);	//UR0發送字串函數
void ExecuteTheOrder();		//執行上位機指令


void main()
{
  PortInit();
  T1Init();
  set_main_clock();
  Init_UART0();
  //overtime_five_min=0;
 /* while(1)
  {UR0SendString("1\n");
  Delay(50000);
  Delay(50000);
  Delay(50000);
  Delay(50000);
  Delay(50000);
  }*/
  while(1)
{
	 
	// overtime_five_min=0;
    if(Flag == 1)      //是否收到上位機指令?
    {
      ExecuteTheOrder();    
      //解析並運行指令
    }
  }
  
}

void Delay(unsigned int t){
	while(t--);
}

void Init_UART0(){
	
	//對應的引腳為外設功能

	PERCFG = 0x00;	//串口0的引腳映射到位置1，即P0_2、3
        PERCFG |= 0x40;
	P0SEL = 0x0C;	//將P0_2、3 Port 設置成外設功能
	P2DIR &= ~0x3F;	//P0外設優先級USART0最高
	
	U0BAUD = 216 ;	//16MHz的系統時鐘產生9600BPS鮑率
	U0GCR = 12;
	
	U0UCR |= 0x80;	//禁止流控，8bit數據，清除緩衝器
	U0CSR |= 0x80;	//選擇UART模式(7)，致能接收器(6)
	
	UTX0IF = 0;		//清除TX發送中斷標誌
	
	//UART2.c外加
	
	U0CSR |=0X40;			//致能UART0 接收
	IEN0 |=0X04;			//致能UART0 接收中斷
	EA=1;					//開啟總中斷

}
//數據接收中斷服務函數
#pragma vector = URX0_VECTOR		
__interrupt void UR0_Recieve_Service(){
	
	URX0IF = 0;				//清除RX接收中斷標誌
	DataRecieve = U0DBUF;	//將數據從接收緩衝區讀出
	Flag = 1;				//設置接收指令標誌
}

void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//將要發送的1字節數據寫入U0DBUF
	while(!UTX0IF);			//等待TX中斷標誌，即數據發送完成
	UTX0IF = 0;				//等待TX中斷標誌，準備下一次發送
	
}

void UR0SendString(unsigned char *str){
	
	while(*str != '\0'){	//發送一個字串
		UR0SendByte(*str++);//逐一發送字串的字元
	}
	
}


void ExecuteTheOrder(){
	
	Flag = 0;//清除接收指令標誌
	Delay(500);
        if(Flag == 0)
        {
	switch(DataRecieve){
		
		case 0x31:
                  testLED =1;
                  Delay(50000);
                 Delay(50000);
                  Delay(50000);
                  testLED=0;
		overtime_five_min=0;
		//UR0SendString("buzzer_ON\n");
                while(sw1==1 && overtime_five_min<130)
	        {
                   buzzer();
		   Flag=0;
		   InitT4();
                   testLED3=1;
                   
                }
                testLED3=0;
                testLED2=1;
                Delay(50000);
                 Delay(50000);
                  Delay(50000);
                  testLED2=0;
                T4CTL &=~ 0x08;  //關溢出中斷
                T3CC0=0x00;     //讓比較值為0x00,蜂鳴器就不會叫。
		//T4CC0=0x00;
		overtime_five_min=0;    //T4計數值歸零
                  Flag=0;
                if(sw1==0)
		{
                  Delay(500);
                  if(sw1==0)
                  {
                    Delay(500);
                    while(sw1==0);
		  
                  servo1();
		  //UR0SendString("servo1\n");
		   
                }
                }
		break;
		
		case 0x32:
                overtime_five_min=0;
                //UR0SendString("buzzer_ON\n");
                while(sw1==1 && overtime_five_min<130)
	        {
                   buzzer();
                   Flag=0;
		   InitT4();
                }
                T4CTL &=~ 0x08 ;
                T3CC0=0x00;
                //T4CC0=0x00;
		overtime_five_min=0;
                  Flag=0;
                if(sw1==0)
		{
                  /*Delay(500);
                  if(sw1==0)
                  {
                    Delay(500);
                    while(sw1==0);*/
		    servo2();
                    //UR0SendString("servo2\n");
                  
                }
		  
		   
		break;
	}
        }
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
}

void PortInit()
{
	//Timer通道?置
    P1SEL |= 0x01;              //Timer1通道2映射至P1_0，功能選擇
    PERCFG |= 0x40;             //備用位置2，?明信息
    P2SEL &= ~0x10;             //相對於Timer4，Timer1優先
    P2DIR |= 0xC0;              //定?器通道2-3具有第一優先順序
    P1DIR |= 0x01;				//P1_0為輸出
    P1SEL &= ~0x80 ;          // 將P2_3設置為通用I/O端口功能 
    P0DIR &= ~0x80 ;          // 將P2_3的端口傳輸方式設置為輸入 
    P0INP &=~ 0x80;
    P2INP &= ~0x20 ;          // 將P0_1的端口輸入方式設置為：上拉/下拉 
	sw1=0;
	P1SEL &=~0X1E;
	P1DIR |=0X1E;
	testLED=0;
	testLED2=0;
        testLED3=0;
	overtime=0;
	
	
}

void T1Init()
{
    
	//T1CCTL0 |= 0x04;      		//<2>??通道0的?出比?模式
    //Timer模式?置
    T1CTL = 0x02;               //250KHZ不分頻，模模式
    
    //根據Table7-1，P1_0必須裝Timer1通道2進行比較
	
    T1CCTL2 = 0x1C;             //比較相等為1，計數器回0則清零
	
    //裝Timer通道0初值
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM信號週期?1ms，頻率為1KHZ

}

void InitT3()
{  
  P1SEL |=0x40;  //設1_6腳為外設腳位
  PERCFG |=0x20; //設置timer3的位置
  
  T3CTL &= ~0x08 ;    //關溢出中斷
  T3CTL|=0xE0;    //128 分頻,128/16000000*N=0.5S,N=65200
  T3CTL &= ~0x03;    //自動重裝 00－>0xff   65200/256=254(次)
  T3CCTL0 &=~0x40;    //中斷禁止
  T3CCTL0 |=0x1c;   // 
  T3CTL |=0X10; //   啟動
 }

void InitT4()
{ 
 
T4CTL |= 0x08 ;    //開溢出中斷
T4IE = 1;    //開總中斷和 T3中斷
T4CTL|=0XE0;    //128 分頻,128/16000000*N=0.5S,N=65200
T4CTL &= ~0X03;    //自動重裝 00－>0xff   65200/256=254(次)
T4CTL |=0X10; //   啟動
EA = 1;     //開總中斷	
}
#pragma vector = T4_VECTOR     //定時器 T4
__interrupt void T4_ISR(void)
{
IRCON = 0x00;    //清中斷標誌,也可由硬件自動完成
if(++countsecond>254)   //254 次中斷後LED取反，閃爍一輪（約為0.5秒時間）
{
	
  countsecond = 0;   // 計數清零 
  overtime_five_min++;
  if(overtime_five_min==130)
  {
    UR0SendString("A\n");

  }
 
}
}
 
void servo1()
{ 
        T1CC2H = 0x06;  //1.39
        T1CC2L = 0x50;
        int i;
        for(i=0;i<23;i++)
        {
          Delay(50000);
        }
        T1CC2H = 0x09;
        T1CC2L = 0xc5;
}

void servo2()
{ 
        T1CC2H = 0x06;  //1.39
        T1CC2L = 0x50;
        int i;
        for(i=0;i<44;i++)
        {
          Delay(48000);
        }
        T1CC2H = 0x09;
        T1CC2L = 0xc5;
}

void buzzer()
{
  int i;
  int rate[11]={0xF7,0xE1,0xC8,0xAF,0x96,0x7D,0x64,0x4B,0x32,0x19,0x0A};
  InitT3();
     for(i=0;i<11;i++) 
        { 
          T3CC0=rate[i]; 
          Delay(50000);

        }
}

