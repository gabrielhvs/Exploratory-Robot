#include "Sensors.hpp"
#include "Arduino.h"

extern int pulseSpeed[2];//variavel de interrupção

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

void SensorSpeedCounte0(){
    pulseSpeed[0]++;
}
void SensorSpeedCounte1(){
    pulseSpeed[1]++;
}

void Sensor::beginSenSpeed(){

    for (int i =0; i<numSss; i++){
        pulseSpeed[i] = 0;
        rpm[i] = 0;
        pinMode(pinEnc[i], INPUT_PULLUP);
    }
    attachInterrupt(digitalPinToInterrupt(pinEnc[0]), SensorSpeedCounte0, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinEnc[1]), SensorSpeedCounte1, CHANGE);
}
  
int Sensor::readSenSpeed(int num, int delta){

        detachInterrupt(digitalPinToInterrupt(pinEnc[num]));
        rpm[num] = (60000/delta)*pulseSpeed[num];
        pulseSpeed[num] = 0;
        if(num==0)
            attachInterrupt(digitalPinToInterrupt(pinEnc[num]),SensorSpeedCounte0, CHANGE);
        else
            attachInterrupt(digitalPinToInterrupt(pinEnc[num]),SensorSpeedCounte1, CHANGE);

    return rpm[num];
}

int Sensor::readSenTemp(int num){

        return analogRead(num);
}