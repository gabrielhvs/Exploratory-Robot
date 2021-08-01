
void BeginUltrasonic(int pinT1, int pinE1, int pinT2, int pinE2 ){
  pinMode(pinT1, OUTPUT);
  pinMode(pinE1, INPUT);
  pinMode(pinT2, OUTPUT);
  pinMode(pinE2, INPUT);
  digitalWrite(pinT1, LOW);
  digitalWrite(pinT2, LOW);
  }

float Read(int pinT, int pinE){
  digitalWrite(pinT, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinT, LOW);
  return pulseIn(pinE, HIGH)*0.034029/2; 
}
