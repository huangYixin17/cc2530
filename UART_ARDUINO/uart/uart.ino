#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
mySerial.begin(9600);
}

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}



/*
void loop() { // run over and over

  
  if (mySerial.available() > 0) {
    //Serial.println(mySerial.read());
  }
 if (Serial.available() > 0) {
  int i=0;
    i=Serial.read();
    Serial.println(i, HEX);
    delay(500);
    Serial.println(Serial.read());
    
    mySerial.write(Serial.read());
   
    
 }
    mySerial.write(01);
    delay(1000);
    mySerial.write(02);
    delay(1000);
    mySerial.write(03);
    delay(1000);
    mySerial.write(04);
    delay(1000);

}  
*/

