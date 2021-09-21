#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void BeginHC12(int baundRate) {
  mySerial.begin(baundRate);
}

void setup(){
  BeginHC12(19200);
}

void loop(){
  mySerial.print(" ");
  delay(10);
}
