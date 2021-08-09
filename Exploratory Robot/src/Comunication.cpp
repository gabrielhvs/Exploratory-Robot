
#include "Comunication.hpp" 
#include <SoftwareSerial.h> 

 
Comunication::Comunication(int pinrx, int pintx, int baundrate)
{
    pinRX=pinrx;
    pinTX=pintx;
    baundRate=baundrate;  
    mySerial = SoftwareSerial(pinRX, pinTX);
}


void Comunication::BeginHC12(){
  mySerial.begin(baundRate);
}

void Comunication::Send (char output){
  mySerial.println(output);
}

char Comunication::Receive (){
    if (mySerial.available() > 0) 
      return mySerial.read();       
}
