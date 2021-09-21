#include <SoftwareSerial.h> 
#include <Arduino.h>
#include "Actuators.hpp"
#include "Sensors.hpp"

////////////////////////////////////////////-Variables-///////////////////////////////////////////////////////
char date; 
int x;                     //Comunicate variable
unsigned long int timeold[3];   //Measure last time
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
  pinMode(0, OUTPUT);
}

////////////////////////////////////////////-Loop-////////////////////////////////////////////////////////////
void loop() {

  if (HC12.available() > 0)  //Read HC12 -> Variable
    x = HC12.read();
  

  Serial.println(x);       //Print of date reciave         

  //Choice of action 
  if(date == 'G')
    Engine.Forward(255, 255); //Robot go to front
  
  else if(date == 'I')
    Engine.Backward(255, 255); //Robot go to back
  
  else if(date == 'Z')
    Engine.Right(255, 255);    //Robot go to Right
  
  else if(date == 'L')
    Engine.Left(255, 255);     //Robot go to Left

  else if(date == 'R')
    Engine.Stop();       //Robot Stop
  else 
    Engine.Stop();       //Robot Stop


  /*if (millis() - timeold[0] >= 1000){
    Serial.print("Speed Sensor 01: ");
    Serial.print(mySensor.readSenSpeed(0, millis()-timeold[0]));
    Serial.print(" |Speed Sensor 02: ");
    Serial.println(mySensor.readSenSpeed(1, millis()-timeold[0]));
    timeold[0] = millis();           
  }
  if (millis() - timeold[1] >= 500){
    Serial.print("Sensor UltroSonic 01: ");
    Serial.print(mySensor.readUltraS(0));
    Serial.print(" | Sensor UltroSonic 02: ");
    Serial.println(mySensor.readUltraS(1));
    timeold[1] = millis();
  }*/

  if (millis() - timeold[2] >= 100){
    int tM1 = mySensor.readSenTemp(4);
    int tM2 = mySensor.readSenTemp(5);
    if (tM1<=15 or tM2<=20)
      digitalWrite(0,HIGH);
    else
      digitalWrite(0,LOW);
    timeold[2] = millis();
    Serial.print(tM1);
  }
}
