#include <SoftwareSerial.h> 
#include <Arduino.h>
#include "Actuators.hpp"
#include "Sensors.hpp"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

////////////////////////////////////////////-Variables-///////////////////////////////////////////////////////
char date; 
char Data[];
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

unsigned long timer = millis();                 // Delay Timer
int set=1;
char SerialByteIn;                              // Temporary variable
char HC12ByteIn;                                // Temporary variable
String HC12ReadBuffer = "";                     // Read/Write Buffer 1 for HC12
String SerialReadBuffer = "";                   // Read/Write Buffer 2 for Serial
boolean SerialEnd = false;                      // Flag to indicate End of Serial String
boolean HC12End = false;                        // Flag to indiacte End of HC12 String
boolean commandMode = false;  

String data_array = "";

////////////////////////////////////////////-Startup-/////////////////////////////////////////////////////////
void setup() {
  mySensor.beginUltraS();  
  mySensor.beginSenSpeed();
  Serial.begin(9600);      //Baund rate 9600
  HC12.begin(9600);       //Baund rate 19200
  pinMode(13, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(0,0);

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
  
    if (millis() - timeold[3] >= 500){
      data_array = "";
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

      //Serial.println(data_array);
      dataFile = SD.open("DATA"+fileName+".csv",FILE_WRITE);
    
      if(dataFile){
        dataFile.println(data_array);
        dataFile.close();
      }

      timeold[3] = millis();

    }

    if (millis() - timeold[4] >= 50){
        String data1 = "Data1";
        if(set){
          HC12.println("Robot->"+ data_array);  // Reset serial end of line flag
          set=!set;
        }
        else{
          while (HC12.available()) {                  // If Arduino's computer rx buffer has data
            SerialByteIn = HC12.read();               // Store each character in byteIn
            SerialReadBuffer += char(SerialByteIn);     // Write each character of byteIn to SerialReadBuffer
            if (SerialByteIn == '\n')                 // Check to see if at the end of the line
                SerialEnd = true;                         // Set SerialEnd flag to indicate end of line
          }

          if (SerialEnd) {                              // Check to see if SerialEnd flag is true
            if (SerialReadBuffer.startsWith("Control->") and SerialReadBuffer.endsWith("\n")) {    // Has a command been sent from local computer
              Serial.print("Receido Control: "); 
              SerialReadBuffer.remove(0,9);
              Serial.print(SerialReadBuffer);
              strcpy(Data, SerialReadBuffer.c_str());   
              set=!set;
            } 
            SerialReadBuffer = "";                      // Clear SerialReadBuffer
            SerialEnd = false;  
          }
          
        }
    }

    if (millis() - timeold[1] >= 100){
        for(int i= 0; i<3; i++){
          ReadDistance[i] = mySensor.readUltraS(i);
          delay(20);
        }

    }
    

    else{

      char  *Datas =  strtok(Data, ",");
      Serial.print(Datas);

      int pwm[] = {int(Datas[24]),int(Datas[25])};

      Engine.Forward(pwm[0], pwm[1]);

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