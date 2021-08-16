#ifndef SENSORS_h
#define SENSORS_h

#include "Arduino.h"
#include <PinChangeInterrupt-1.2.9/src/PinChangeInterrupt.h>
#include <PinChangeInterrupt-1.2.9/src/PinChangeInterruptBoards.h>
#include <PinChangeInterrupt-1.2.9/src/PinChangeInterruptPins.h>
#include <PinChangeInterrupt-1.2.9/src/PinChangeInterruptSettings.h>

int pulse[2];
class Sensor
{
  public:
    Sensor(int q, int *pinUS, int q1, int *pinSS);
    void beginUltraS();
    void beginSenSpeed();
    float readUltraS(int num);
    int readSenSpeed(int num);
    


  private:
    int numSus, numSss;
    int pinTrig[2], pinEcho[2], pinEnc[2];
    int rpm[2];
    unsigned long timeold;
};

#endif
