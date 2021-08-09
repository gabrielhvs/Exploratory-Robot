// Main Code


Motors mot(0, 1, 2, 3);
 
void setup() {
  BeginHC12(9600);
  BeginUltrasonic(9,8,11,10);
 
  Serial.begin(9600);

  
}
void loop() {
  //Serial.println(Read(9,8));
  if(Receive() == 'A')
    Forward(255, 255);
  else if(Receive() == 'B')
    Backward(255, 255);
  else if(Receive() == 'C')
    Right(255, 255);
  else if(Receive() == 'D')
    Left(255, 255);
}
