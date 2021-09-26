#include <SoftwareSerial.h> 
#include <Arduino.h>
#include "Actuators.hpp"
#include "Sensors.hpp"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

////////////////////////////////////////////-Variables-///////////////////////////////////////////////////////
char date; 
int x;                     //Comunicate variable
unsigned long int timeold[5];   //Measure last time
int pulseSpeed[2] = {0,0};      //Measure of quantity of speed pulse
int pinUltra[6] = {14,15,14,16,18,17};//Pins sensor ultrasonic
int pinEnco[2] = {2, 3};        //Pins sensor speed sensor
int pinTemp[2] = {6, 7};        //Pins sensor speed sensor
int Slight = 0;
int ReadDistance[3] = {0,0,0};
int ReadSpeed[2]={0,0};
int ReadTemp[2]={0,0};
const int chipSelect = 10; 
int prev_file_indx = 0;
String fileName = "000";
String sd_saver(File dir);

////////////////////////////////////////////-Objects-/////////////////////////////////////////////////////////
Actuator Engine(7, 8, 6, 9);          //Object - Enggine
SoftwareSerial HC12(4, 5);            //Object - Comunicate
Sensor mySensor(3, pinUltra, 2, pinEnco, 2, pinTemp);//Object - Sensors (Speed and Ultrasonic)
File main_folder; 
File dataFile;

////////////////////////////////////////////-Startup-/////////////////////////////////////////////////////////
void setup() {
  mySensor.beginUltraS();  
  mySensor.beginSenSpeed();
  Serial.begin(9600);      //Baund rate 9600
  HC12.begin(19200);       //Baund rate 19200
  pinMode(13, OUTPUT);

  if (!SD.begin(chipSelect)) {
      return;
  }
  
  main_folder = SD.open("/");
  fileName = sd_saver(main_folder);
  String Title = "Time, Temp - S1,Temp - S2, Light, Dist-Left, Dist-Center, Dist-Right, Speed-Left, Speed-Right"; 
  dataFile = SD.open("DATA"+fileName+".csv",FILE_WRITE);  
  
  if(dataFile){
      dataFile.println(Title);
      dataFile.close();
  }
  
}

////////////////////////////////////////////-Loop-////////////////////////////////////////////////////////////
void loop() {

  if (millis() - timeold[0] >= 1000){
    for(int i=0;i<2; i++)
      ReadSpeed[i]=mySensor.readSenSpeed(0, millis()-timeold[0]);
    timeold[0] = millis();           
  }

  if (millis() - timeold[1] >= 500){
    for(int i= 0; i<3; i++){
      ReadDistance[i] = mySensor.readUltraS(i);
      delay(10);
    }
    
    timeold[1] = millis();
  }

  if (millis() - timeold[2] >= 200){

     Slight = mySensor.readSenLight(5);
     for(int i=0;i<2; i++)
      ReadTemp[i]=mySensor.readSenTemp(i);
    
    if (ReadTemp[0]<=15 or ReadTemp[1]<=20)
      digitalWrite(0,HIGH);
    else
      digitalWrite(0,LOW);
    
    timeold[2] = millis();

  }
 
  if (millis() - timeold[3] >= 100){
    String data_array = "";
    data_array += String(millis()); 
    data_array += ",";
    data_array += String(ReadTemp[0]);
    data_array += ",";
    data_array += String(ReadTemp[1]);
    data_array += ",";
    data_array += String(Slight);
    data_array += ",";
    data_array += String(ReadDistance[0]);
    data_array += ",";
    data_array += String(ReadDistance[1]);
    data_array += ",";
    data_array += String(ReadDistance[2]);
    data_array += ",";
    data_array += String(ReadSpeed[0]);
    data_array += ",";
    data_array += String(ReadSpeed[1]);

    Serial.println(data_array);
    dataFile = SD.open("DATA"+fileName+".csv",FILE_WRITE);
  
    if(dataFile){
      dataFile.println(data_array);
      dataFile.close();
    }

    timeold[3] = millis();

  }

  if (millis() - timeold[4] >= 50){
    if (HC12.available() > 0)  //Read HC12 -> Variable
      x = HC12.read();
  
    //Serial.println(x);       //Print of date reciave         

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

    timeold[4] = millis();

  }
  



}

String sd_saver(File dir){
  while(true){
    
    File entry = dir.openNextFile();
    if (!entry){
      break;
    }
    // rotina de nomenclatura
    String entry_name = entry.name();
    if ((entry_name.substring(4,7)).toInt()>=prev_file_indx){
      prev_file_indx = (entry_name.substring(4,7)).toInt()+1;
      if (prev_file_indx>=100){
        fileName = String(prev_file_indx);
      } else if (prev_file_indx>=10){
        fileName = "0"+String(prev_file_indx);
      } else{
        fileName = "00"+String(prev_file_indx);
      }
    }
    entry.close();
  }
  return fileName;
}