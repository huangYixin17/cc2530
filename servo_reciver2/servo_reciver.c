#include "ioCC2530.h" 

#define  reciver P1_1
#define  servo  P1_0
#define  LED1  P1_3
#define  LED2  P1_4
/* ===================���ɨ��= ======================== */ 
 void Delay(unsigned int t)
 {
   while (t-- );
 }
 /* = =================�ݤf��l�ƨ��===================== */
 void Init_Port()
 {
   //�NP1_0�]�m���q��I/O�ݤf�\��
   P1SEL &= ~ 0x19 ;   
   // �NP1_0���ݤf�ǿ�覡�]�m����X
   P1DIR |= 0x19 ;   
   P1SEL &= ~ 0x02 ;
   P1DIR &= ~0x02 ;  
   P1INP &= ~ 0x02;          // �NP1_2���ݤf��J�覡�]�m���G�W��/�U�� 
  P2INP &= ~ 0x60 ;          // �NP0�ݤf�MP1�ݤf�޸}�]�m���G�W�� 
  servo=0;
   LED1=0;
 }
 /* = =================���F��@��===================== */
 void servo_1()
 {
   servo = 1 ;
   Delay( 45000 );
   servo = 0 ;
 }
 /* = =================�������~�u===================== */
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
/* ============= ==�~�����_��l�ƨ��================== */ 
 void Init_INTP()
 {
   IEN2 |= 0x10 ;          // �ݤf1���_�ϯ�
   P1IEN |= 0x04 ;         // �ݤfP1_2�~�����_�ϯ�
   PICTL |= 0x02 ;         // �ݤfP1_0��P1_3�U���uĲ�o
   EA = 1 ;                // �ϯ��`���_
 }
 /* ================�~�����_1�A�Ȩ��==================== */ 
 #pragma vector = P1INT_VECTOR      // �~�����_1���V�q�J�f
__interrupt void Int1_Sevice()
 {
   servo_1();
 /* ���M���޸}�лx��A�A�M���ݤf�лx��A�_�h�|���_�i�J���_*/ 
   P1IFG &= ~ 0x04 ;         //�n��M��P1_2�޸}���лx��
   P1IF = 0 ;                // �n��M��P1�ݤf�ժ��лx��
 }
 void main()
 {
   Init_Port();           // ��l�Ƴq��I/O�ݤf
   Init_INTP ();           // ��l�ƥ~�����_
   void reciver_1();
   while(1)
   {
   LED2=1;
   Delay(50000);
   LED2=0;
   Delay(50000);
   }
 }
