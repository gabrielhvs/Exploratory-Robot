#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Motors
{
  public:
    Motors(int pinCtr1, int pinCtr2, int pinSpe1, int pinSpe2);
    void Forward(int pwm1, int pwm2);
    void Backward(int pwm1, int pwm2);
    void Right(int pwm1, int pwm2);
    void Left(int pwm1, int pwm2);
  private:
    int pC1; 
    int pC2; 
    int pS1; 
    int pS2;
    int pw1;
    int pw2;
};

#endif

Motors::Motors(int pinCtr1 , int pinCtr2, int pinSpe1, int pinSpe2){
  pS1=pinSpe1;
  pS2=pinSpe2;
  pC1=pinCtr1;
  pC2=pinCtr2;
  pinMode(pC1, OUTPUT);
  pinMode(pC2, OUTPUT);
  analogWrite(pS1, 0);
  analogWrite(pS2, 0);
  digitalWrite(pC1, 0);
  digitalWrite(pC2, 0);
  }

void Forward(int pwm1, int pwm2){
  digitalWrite(pC1, 1);
  digitalWrite(pC2, 1);
  analogWrite(pS1, pwm1);
  analogWrite(pS2, pwm2);
  }
/*
void Backward(int pwm1, int pwm2){
  digitalWrite(pinCtr1, 0);
  digitalWrite(pinCtr2, 0);
  analogWrite(pinSpe1, pwm1);
  analogWrite(pinSpe2, pwm2);
}

void Right(int pwm1, int pwm2){
  digitalWrite(pinCtr1, 1);
  digitalWrite(pinCtr2, 0);
  analogWrite(pinSpe1, pwm1);
  analogWrite(pinSpe2, pwm2);
  }

  void Left(int pwm1, int pwm2){
  digitalWrite(pinCtr1, 0);
  digitalWrite(pinCtr2, 1);
  analogWrite(pinSpe1, pwm1);
  analogWrite(pinSpe2, pwm2);
  }*/
