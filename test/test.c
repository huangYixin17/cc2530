#include "ioCC2530.h"

#define servopin P1_0
#define buzzerpin P1_6 
#define testLED P1_1
#define testLED2 P1_3
#define testLED3 P1_4
#define overtime P1_2
#define sw1 P0_7
unsigned char DataRecieve;		//Ū���w�İϸ�ƪ��ܼ�
unsigned char Flag = 0;			//�������O�лx���ܼ�
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
void set_main_clock();	//�]�m�D����
void Init_UART0();		//�ǦC��0����l�ƨ��
void UR0SendByte(unsigned char data);	//UR0�o�e�r�����
void UR0SendString(unsigned char *str);	//UR0�o�e�r����
void ExecuteTheOrder();		//����W������O


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
    if(Flag == 1)      //�O�_����W������O?
    {
      ExecuteTheOrder();    
      //�ѪR�ùB����O
    }
  }
  
}

void Delay(unsigned int t){
	while(t--);
}

void Init_UART0(){
	
	//�������޸}���~�]�\��

	PERCFG = 0x00;	//��f0���޸}�M�g���m1�A�YP0_2�B3
        PERCFG |= 0x40;
	P0SEL = 0x0C;	//�NP0_2�B3 Port �]�m���~�]�\��
	P2DIR &= ~0x3F;	//P0�~�]�u����USART0�̰�
	
	U0BAUD = 216 ;	//16MHz���t�ή�������9600BPS�j�v
	U0GCR = 12;
	
	U0UCR |= 0x80;	//�T��y���A8bit�ƾڡA�M���w�ľ�
	U0CSR |= 0x80;	//���UART�Ҧ�(7)�A�P�౵����(6)
	
	UTX0IF = 0;		//�M��TX�o�e���_�лx
	
	//UART2.c�~�[
	
	U0CSR |=0X40;			//�P��UART0 ����
	IEN0 |=0X04;			//�P��UART0 �������_
	EA=1;					//�}���`���_

}
//�ƾڱ������_�A�Ȩ��
#pragma vector = URX0_VECTOR		
__interrupt void UR0_Recieve_Service(){
	
	URX0IF = 0;				//�M��RX�������_�лx
	DataRecieve = U0DBUF;	//�N�ƾڱq�����w�İ�Ū�X
	Flag = 1;				//�]�m�������O�лx
}

void UR0SendByte(unsigned char data){
	
	U0DBUF = data;			//�N�n�o�e��1�r�`�ƾڼg�JU0DBUF
	while(!UTX0IF);			//����TX���_�лx�A�Y�ƾڵo�e����
	UTX0IF = 0;				//����TX���_�лx�A�ǳƤU�@���o�e
	
}

void UR0SendString(unsigned char *str){
	
	while(*str != '\0'){	//�o�e�@�Ӧr��
		UR0SendByte(*str++);//�v�@�o�e�r�ꪺ�r��
	}
	
}


void ExecuteTheOrder(){
	
	Flag = 0;//�M���������O�лx
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
                T4CTL &=~ 0x08;  //�����X���_
                T3CC0=0x00;     //������Ȭ�0x00,���ﾹ�N���|�s�C
		//T4CC0=0x00;
		overtime_five_min=0;    //T4�p�ƭ��k�s
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
	CLKCONCMD |= 0X40;			//���16MHZ RCOSC���t�ή�����
	while(!(CLKCONSTA & 0X40)); //���ݮ���í�w
	CLKCONCMD &=~0XF8;			//���32MHz���D����
}

void PortInit()
{
	//Timer�q�D?�m
    P1SEL |= 0x01;              //Timer1�q�D2�M�g��P1_0�A�\����
    PERCFG |= 0x40;             //�ƥΦ�m2�A?���H��
    P2SEL &= ~0x10;             //�۹��Timer4�ATimer1�u��
    P2DIR |= 0xC0;              //�w?���q�D2-3�㦳�Ĥ@�u������
    P1DIR |= 0x01;				//P1_0����X
    P1SEL &= ~0x80 ;          // �NP2_3�]�m���q��I/O�ݤf�\�� 
    P0DIR &= ~0x80 ;          // �NP2_3���ݤf�ǿ�覡�]�m����J 
    P0INP &=~ 0x80;
    P2INP &= ~0x20 ;          // �NP0_1���ݤf��J�覡�]�m���G�W��/�U�� 
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
    
	//T1CCTL0 |= 0x04;      		//<2>??�q�D0��?�X��?�Ҧ�
    //Timer�Ҧ�?�m
    T1CTL = 0x02;               //250KHZ�����W�A�ҼҦ�
    
    //�ھ�Table7-1�AP1_0������Timer1�q�D2�i����
	
    T1CCTL2 = 0x1C;             //����۵���1�A�p�ƾ��^0�h�M�s
	
    //��Timer�q�D0���
    T1CC0H = 0x09;
    T1CC0L = 0xC4;              //PWM�H���g��?1ms�A�W�v��1KHZ

}

void InitT3()
{  
  P1SEL |=0x40;  //�]1_6�}���~�]�}��
  PERCFG |=0x20; //�]�mtimer3����m
  
  T3CTL &= ~0x08 ;    //�����X���_
  T3CTL|=0xE0;    //128 ���W,128/16000000*N=0.5S,N=65200
  T3CTL &= ~0x03;    //�۰ʭ��� 00��>0xff   65200/256=254(��)
  T3CCTL0 &=~0x40;    //���_�T��
  T3CCTL0 |=0x1c;   // 
  T3CTL |=0X10; //   �Ұ�
 }

void InitT4()
{ 
 
T4CTL |= 0x08 ;    //�}���X���_
T4IE = 1;    //�}�`���_�M T3���_
T4CTL|=0XE0;    //128 ���W,128/16000000*N=0.5S,N=65200
T4CTL &= ~0X03;    //�۰ʭ��� 00��>0xff   65200/256=254(��)
T4CTL |=0X10; //   �Ұ�
EA = 1;     //�}�`���_	
}
#pragma vector = T4_VECTOR     //�w�ɾ� T4
__interrupt void T4_ISR(void)
{
IRCON = 0x00;    //�M���_�лx,�]�i�ѵw��۰ʧ���
if(++countsecond>254)   //254 �����_��LED���ϡA�{�{�@���]����0.5��ɶ��^
{
	
  countsecond = 0;   // �p�ƲM�s 
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

