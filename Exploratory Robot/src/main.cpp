#include <SoftwareSerial.h> 
#include <Arduino.h>
#include "Actuators.hpp"
#include "Sensors.hpp"

////////////////////////////////////////////-Variables-///////////////////////////////////////////////////////
char date;                      //Comunicate variable
unsigned long int timeold[2];   //Measure last time
int pulseSpeed[2] = {0,0};      //Measure of quantity of speed pulse
int pinUltra[4] = {13,11,11,10};//Pins sensor ultrasonic
int pinEnco[2] = {2, 3};        //Pins sensor speed sensor

////////////////////////////////////////////-Objects-/////////////////////////////////////////////////////////
Actuator Engine(7, 8, 9, 6);          //Object - Enggine
SoftwareSerial HC12(4, 5);            //Object - Comunicate
Sensor mySensor(2,pinUltra,2,pinEnco);//Object - Sensors (Speed and Ultrasonic)
 
////////////////////////////////////////////-Startup-/////////////////////////////////////////////////////////
void setup() {
  mySensor.beginUltraS();  
  mySensor.beginSenSpeed();
  Serial.begin(9600);      //Baund rate 9600
  HC12.begin(19200);       //Baund rate 19200
}

////////////////////////////////////////////-Loop-////////////////////////////////////////////////////////////
void loop() {

  if (HC12.available() > 1)   //Read HC12 -> Variable 
    date = HC12.read();

  Serial.println(date);       //Print of date reciave         

  //Choice of action 
  if(date == 'K')
    Engine.Forward(255, 255); //Robot go to front
  
  else if(date == 'J')
    Engine.Backward(255, 255); //Robot go to back
  
  else if(date == 'E')
    Engine.Right(255, 255);    //Robot go to Right
  
  else if(date == 'F')
    Engine.Left(255, 255);     //Robot go to Left

  else if(date == 'R')
    Engine.Stop();       //Robot Stop
  
 /* 
 if (millis() - timeold[0] >= 1000)
    {
        Serial.print("Speed Sensor 01: ");
        Serial.print(mySensor.readSenSpeed(0, millis()-timeold[0]));
        Serial.print(" |Speed Sensor 02: ");
        Serial.println(mySensor.readSenSpeed(1, millis()-timeold[0]));
        timeold[0] = millis();
  }
  if (millis() - timeold[1] >= 500)
    {
      Serial.print("Sensor UltroSonic 01: ");
      Serial.print(mySensor.readUltraS(0));
      Serial.print(" | Sensor UltroSonic 02: ");
      Serial.println(mySensor.readUltraS(1));
      timeold[1] = millis();
  }
  */
}
