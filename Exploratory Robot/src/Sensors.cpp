#include "Sensors.hpp"
#include "Arduino.h"

Sensor::Sensor(int q, int *pinUS, int qs, int *pinSS){
    numSus = q;
    numSss = qs;
    for(int i =0; i<numSus; i++){
        pinTrig[i]=pinUS[2*i];
        pinEcho[i]=pinUS[(2*i)+1];

    }
    for(int i =0; i<numSss; i++)
        pinEnc[i]=pinSS[i];

}

void Sensor::beginUltraS(){
    for (int i =0; i<numSus; i++){
        pinMode(pinTrig[i], OUTPUT);
        pinMode(pinEcho[i], INPUT);
        digitalWrite(pinTrig[i], LOW);
    }
}

float Sensor::readUltraS(int num){
  digitalWrite(pinTrig[num], HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig[num], LOW);
  return (pulseIn(pinEcho[num], HIGH)*0.034029/2); 
}

void SensorSpeedCounte(){
    pulse[1]++;
}

void Sensor::beginSenSpeed(){
    
    timeold = 0;
    for (int i =0; i<numSss; i++){
        pulse[i] = 0;
        rpm[i] = 0;
        pinMode(pinEnc[i], INPUT);
        attachPCINT(digitalPinToPCINT(pinEnc[i]), SensorSpeedCounte, FALLING);//Verificar!!
        
    }
}


   
int Sensor::readSenSpeed(int num){
    if (millis() - timeold >= 1000)
    {
        disablePinChangeInterrupt(digitalPinToPinChangeInterrupt(pinEnc[num]));
        rpm[num] = 60000/(millis() - timeold) * pulse[num];
        timeold = millis();
        pulse[num] = 0;
        enablePinChangeInterrupt(digitalPinToPinChangeInterrupt(pinEnc[num]));
    }
    return rpm[num];
}