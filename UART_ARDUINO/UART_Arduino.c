#include "ioCC2530.h"

#define LED4 P1_1
#define LED5 P1_0
#define sw1 P2_3
#define sw2 P2_4

unsigned char DataRecieve;		//讀取緩衝區資料的變數
unsigned char Flag = 0;			//接收指令標誌的變數

void PortInit();
void T1Init();
void Delay(unsigned int t);
void servo1();
void servo2();
void set_main_clock();	//設置主時鐘
void Init_UART0();		//序列埠0的初始化函數
void UR0SendByte(unsigned char data);	//UR0發送字元函數
void UR0SendString(unsigned char *str);	//UR0發送字串函數
void ExecuteTheOrder();		//執行上位機指令
void test();


void main()
{
  PortInit();
  T1Init();
  set_main_clock();
  Init_UART0();
  
  UR0SendString("ABC");
  
  while(1)
  {
    if(Flag == 1)      //是否收到上位機指令?
    {
      ExecuteTheOrder();    //解析並運行指令
    }
  }
  
}
void test()
{
  LED4=1;
  Delay(50000);
  LED4=0;
}

void Init_UART0(){
	
	//對應的引腳為外設功能

	PERCFG = 0x00;	//串口0的引腳映射到位置1，即P0_2、3
	P0SEL = 0x0C;	//將P0_2、3 Port 設置成外設功能
	P2DIR &= ~0x3F;	//P0外設優先級USART0最高
	
	U0BAUD = 59;	//16MHz的系統時鐘產生9600BPS鮑率
	U0GCR = 9;
	
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
	
	Flag = 0;	//清除接收指令標誌
	
	/*
	if(DataRecieveTime==1){
		Buzzer = 1
		if(Button==1){
			Buzzer = 0
			Running1()
		}
	else
		Buzzer = 0
		Running0()
	}
	*/
	
	
	
	switch(DataRecieve){
		
		case 0x31:
			test();
			UR0SendString("servo1\n");
		break;
		
		case 0x32:
			servo2();
			UR0SendString("servo2\n");
		break;
		
	}
}

void set_main_clock()
{ 
	CLKCONCMD |= 0X40;			//選擇16MHZ RCOSC為系統時鐘源
	while(!(CLKCONSTA & 0X40)); //等待時鐘穩定
	CLKCONCMD &=~0XF8;			//選擇32MHz為主時鐘
}

void Delay(unsigned int t){
	while(t--);
}

void PortInit()
{
	//Timer通道?置
    P1SEL |= 0x01;              //Timer1通道2映射至P1_0，功能選擇
    PERCFG |= 0x40;             //備用位置2，?明信息
    P2SEL &= ~0x10;             //相對於Timer4，Timer1優先
    P2DIR |= 0xC0;              //定?器通道2-3具有第一優先順序
    P1DIR |= 0x01;				//P1_0為輸出
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
    
	//T1CCTL0 |= 0x04;      		//<2>??通道0的?出比?模式
    //Timer模式?置
    T1CTL = 0x02;               //250KHZ不分頻，模模式
    
    //根據Table7-1，P1_0必須裝Timer1通道2進行比較
	
    T1CCTL2 = 0x1C;             //比較相等為1，計數器回0則清零
	
    //裝Timer通道0初值
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM信號週期?1ms，頻率為1KHZ
	
	

	
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

