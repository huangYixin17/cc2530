/*****���F******/

#include "ioCC2530.h" 

 #define   LED3 P1_0
 #define   LED4 P1_1
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
   LED3 = 0 ;
   LED4 = 0 ;
 }
 /* ==================�]���O�l���=============== ====== */ 
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
   LED_Running1();
   //LED_Running1();
 /* ���M���޸}�лx��A�A�M���ݤf�лx��A�_�h�|���_�i�J���_*/ 
   P1IFG &= ~ 0x04 ;         //�n��M��P1_2�޸}���лx��
   P1IF = 0 ;                // �n��M��P1�ݤf�ժ��лx��
 }
 /* ====================�D���========================== */ 
 void main()
 {
   Init_Port();           // ��l�Ƴq��I/O�ݤf
   Init_INTP ();           // ��l�ƥ~�����_
   while ( 1 )
   {
     LED_Running();      // �]���O
   }
}