// Send and Receive of data

#include <SoftwareSerial.h> 
 SoftwareSerial mySerial(2,3); 

void BeginHC12(int baundRate){
  mySerial.begin(baundRate);
}

void Send (char output){
  mySerial.println(output);
}

char Receive (){
    if (mySerial.available() > 0) 
      return mySerial.read();       
}
