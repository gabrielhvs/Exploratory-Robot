#include "Actuators.hpp"
#include "Arduino.h"

Actuator::Actuator(int pinC1 , int pinC2, int pinS1, int pinS2){
  pinSpe1=pinS1;
  pinSpe2=pinS2;
  pinCtr1=pinC1;
  pinCtr2=pinC2;
  pinMode(pinCtr1, OUTPUT);
  pinMode(pinCtr2, OUTPUT);
  analogWrite(pinSpe1, 0);
  analogWrite(pinSpe2, 0);
  digitalWrite(pinCtr1, 0);
  digitalWrite(pinCtr2, 0);
  }

void Actuator::Forward(int pwm1, int pwm2){
    digitalWrite(pinCtr1, 1);
    digitalWrite(pinCtr2, 0);
    analogWrite(pinSpe1, pwm1);
    analogWrite(pinSpe2, pwm2);
  }

void Actuator::Backward(int pwm1, int pwm2){
  digitalWrite(pinCtr1, 0);
  digitalWrite(pinCtr2, 1);
  analogWrite(pinSpe1, pwm1);
  analogWrite(pinSpe2, pwm2);
}

void Actuator::Right(int pwm1, int pwm2){
  digitalWrite(pinCtr1, 0);
  digitalWrite(pinCtr2, 0);
  analogWrite(pinSpe1, pwm1);
  analogWrite(pinSpe2, pwm2);
  }

void Actuator::Left(int pwm1, int pwm2){
  digitalWrite(pinCtr1, 1);
  digitalWrite(pinCtr2, 1);
  analogWrite(pinSpe1, pwm1);
  analogWrite(pinSpe2, pwm2);
  }

void Actuator::Stop(){
  digitalWrite(pinCtr1, 0);
  digitalWrite(pinCtr2, 0);
  analogWrite(pinSpe1, 0);
  analogWrite(pinSpe2, 0);
  }