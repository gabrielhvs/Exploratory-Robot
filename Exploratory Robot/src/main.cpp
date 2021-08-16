#include <Arduino.h>
#include "Comunication.hpp" 
#include "Actuators.hpp"
#include "Sensors.hpp"

int pinUltra[4] = {11,10,9,8};
int pinEnco[2] = {12, 13};
Actuator EngineGoes(5, 7, 4, 6);
Comunication myHC12(2, 3, 9600);
Sensor mySensor(2, pinUltra, 2 , pinEnco);

 
void setup() {
  myHC12.BeginHC12();
  mySensor.beginUltraS();
  mySensor.beginSenSpeed();
  Serial.begin(9600);
 
}
void loop() {
  //Serial.print("Sensor UltroSonic 01: ");
  //Serial.print(mySensor.readUltraS(0));
 // Serial.print(" | Sensor UltroSonic 02: ");
 // Serial.println(mySensor.readUltraS(1));
  Serial.print(mySensor.readSenSpeed(0));
  char date = myHC12.Receive();
  if(date == 'A'){
    myHC12.Send('A');
    EngineGoes.Forward(255, 255);
  }
  else if(date == 'B'){
    myHC12.Send('B');
    EngineGoes.Backward(255, 255);
  }
  else if(date == 'C'){
    myHC12.Send('C');
    EngineGoes.Right(255, 255);
  }
  else if(date == 'D'){
    myHC12.Send('D');
    EngineGoes.Left(255, 255);
  }
  else if(date == 'E'){
    myHC12.Send('E');
    EngineGoes.Forward(0, 0);
  }
  /*for(int i =0; i<=255; i+=40){
    EngineGoes.Right(i, 0);
    delay(5000);
  }*/
  
}
