// Main Code
                      
void setup() {
  BeginHC12(9600);
  
}
void loop() {

  if(Receive() == 'A')
    Send('A');
}
