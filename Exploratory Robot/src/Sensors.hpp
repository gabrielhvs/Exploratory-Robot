#ifndef SENSORS_h
#define SENSORS_h

#include "Arduino.h"

class Sensor
{
  public:
    Sensor(int qUS, int *pinUS, int qSS, int *pinSS, int qT, int *pinST);
    void beginUltraS();
    void beginSenSpeed();
    float readUltraS(int num);
    int readSenSpeed(int num, int delta);
    int readSenTemp(int num);
    int readSenLight(int num);


  private:
    int numSus, numSss, numSst;
    int pinTrig[3], pinEcho[3], pinEnc[2], pinTemp[2];
    int rpm[2];
   
};

#endif
