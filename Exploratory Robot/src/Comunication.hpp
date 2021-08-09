#ifndef COMUNICATION_H
#define COMUNICATION_H

#include <SoftwareSerial.h> 
#include "Arduino.h"

class Comunication
{
private:
   int baundRate;
   int pinRX;
   int pinTX;
   SoftwareSerial mySerial = SoftwareSerial(pinRX, pinTX); 
public:
   Comunication(int pinrx, int pintx, int baundrate);
   void  BeginHC12();
   void  Send (char output);
   char  Receive ();
  

};
 
#endif