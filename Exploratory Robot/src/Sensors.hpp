#ifndef SENSORS_h
#define SENSORS_h

#include "Arduino.h"

class Sensor
{
  public:
    Sensor(int q, int *pinUS, int q1, int *pinSS);
    void beginUltraS();
    void beginSenSpeed();
    float readUltraS(int num);
    int readSenSpeed(int num, int delta);
    


  private:
    int numSus, numSss;
    int pinTrig[2], pinEcho[2], pinEnc[2];
    int rpm[2];
   
};

#endif
