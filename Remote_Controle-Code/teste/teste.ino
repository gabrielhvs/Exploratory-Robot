int readA0 = 0;
int readA1 = 0;
bool readA2 = 0;
int readA0map = 0;
char dado;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0){
    Serial.println(Serial.read(),BIN);
}
/*readA0 = analogRead(A0);
  readA1 = analogRead(A1);
  readA2 = digitalRead(2);

  readA0map = map(readA0,0,1023,0,99) | (readA2<<7);
  char x = 122;
  
  Serial.print("\nA0: ");
  Serial.println(x);
  Serial.print("A0: ");
  Serial.println(readA0map,BIN);
  delay(500);*/
}
