const byte HC12RxdPin = 4;                      // "RXD" Pin on HC12
const byte HC12TxdPin = 5;                      // "TXD" Pin on HC12
const byte HC12SetPin = 6;                      // "SET" Pin on HC12

unsigned long timer = millis();                 // Delay Timer
int set=1;
char SerialByteIn;                              // Temporary variable
char HC12ByteIn;                                // Temporary variable
String HC12ReadBuffer = "";                     // Read/Write Buffer 1 for HC12
String SerialReadBuffer = "";                   // Read/Write Buffer 2 for Serial
boolean SerialEnd = false;                      // Flag to indicate End of Serial String
boolean HC12End = false;                        // Flag to indiacte End of HC12 String
boolean commandMode = false;                    // Send AT commands

#include <SoftwareSerial.h>
//Define os pinos para conexao serial do modulo wireless HC-12
SoftwareSerial mySerial(4,5); // RX, TX

void setup() {


  delay(80);                                    // 80 ms delay before operation per datasheet
  Serial.begin(9600);                           // Open serial port to computer
  mySerial.begin(9600);                           // Open serial port to computer

}

void loop() {
  String data1 = "Data1";
  if(set){
    mySerial.println("Robot->"+data1);  // Reset serial end of line flag
  set=!set;
  }
  else{
  while (mySerial.available()) {                  // If Arduino's computer rx buffer has data
    SerialByteIn = mySerial.read();               // Store each character in byteIn
    SerialReadBuffer += char(SerialByteIn);     // Write each character of byteIn to SerialReadBuffer
    if (SerialByteIn == '\n') {                 // Check to see if at the end of the line
      SerialEnd = true;                         // Set SerialEnd flag to indicate end of line
    }
    
  }

  if (SerialEnd) {                              // Check to see if SerialEnd flag is true
  
    
    if (SerialReadBuffer.startsWith("Control->") and SerialReadBuffer.endsWith("\n")) {    // Has a command been sent from local computer
       Serial.print("Receido Control: "); 
       SerialReadBuffer.remove(0,9);
       Serial.print(SerialReadBuffer);  
       set=!set;
    } 
    SerialReadBuffer = "";                      // Clear SerialReadBuffer
    SerialEnd = false; 
    
    
  }
    
  }
  
  
}
