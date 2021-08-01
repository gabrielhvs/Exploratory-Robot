// Main Code
                      
void setup() {
  BeginHC12(9600);
  BeginUltrasonic(9,8,11,10);
  Serial.begin(9600);
}
void loop() {
  Serial.println(Read(9,8));
  delay(200);
  if(Receive() == 'A')
    Send('A');
}
