#ifndef ACTUATORS_h
#define ACTUATORS_h

#include "Arduino.h"

class Actuator
{
  public:
    Actuator(int pinC1, int pinC2, int pinS1, int pinS2);
    void Forward(int pwm1, int pwm2);
    void Backward(int pwm1, int pwm2);
    void Right(int pwm1, int pwm2);
    void Left(int pwm1, int pwm2);

  private:
    int pinCtr1, pinCtr2;
    int pinSpe1, pinSpe2;
};

#endif
