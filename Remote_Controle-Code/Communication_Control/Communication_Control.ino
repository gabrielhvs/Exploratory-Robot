#include <PS2X_lib.h>  //for v1.6

#define PS2_DAT        9  //PURPLE 
#define PS2_CMD        11  //ORANGE
#define PS2_SEL        10  //WHITE
#define PS2_CLK        12  //GREEN
#define pressures   false
#define rumble      false

String FDATA;

const byte HC12RxdPin = 4;                      // "RXD" Pin on HC12
const byte HC12TxdPin = 5;                      // "TXD" Pin on HC12
const byte HC12SetPin = 6;                      // "SET" Pin on HC12


unsigned long timer = millis();                 // Delay Timer
char SerialByteIn;                              // Temporary variable
int set =0;
String SerialReadBuffer= "";                   // Read/Write Buffer 2 for Serial
boolean SerialEnd = false;                      // Flag to indicate End of Serial String


PS2X ps2x;

int error= 0;
byte type = 0;
byte vibrate = 0;

void setup(){
  
  delay(80);                                    
  Serial.begin(9600);                           
  Serial1.begin(9600);     
                       
  error= ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

}

void loop() { //DualShock Controller
   ps2x.read_gamepad(false, vibrate);
    if(ps2x.Button(PSB_START))      
      FDATA =  "ST";
    else if(ps2x.Button(PSB_SELECT))
      FDATA =  "SL";   
    else
       FDATA = "W";  
      
    if(ps2x.Button(PSB_PAD_UP))
     FDATA += ",U";
    else if(ps2x.Button(PSB_PAD_RIGHT))
     FDATA += ",R";
    else if(ps2x.Button(PSB_PAD_LEFT))
    FDATA += ",L";
    else if(ps2x.Button(PSB_PAD_DOWN))
     FDATA += ",D";
    else
      FDATA += ",W";
    
    if(ps2x.Button(PSB_L3))
       FDATA += ",3";
    else if(ps2x.Button(PSB_L2))
       FDATA += ",2";
    else if(ps2x.Button(PSB_L1))
       FDATA += ",1";
    else
      FDATA += ",W";   
        
    if(ps2x.Button(PSB_R3))
       FDATA += ",3";
    else if(ps2x.Button(PSB_R2))
       FDATA += ",2";  
    else if(ps2x.Button(PSB_R1))
       FDATA += ",1";
    else
      FDATA += ",W";
          
    if(ps2x.Button(PSB_TRIANGLE))
      FDATA += ",T";       
    else if(ps2x.Button(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
      FDATA += ",C";
    else if(ps2x.Button(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
      FDATA += ",X";
    else if(ps2x.Button(PSB_SQUARE))              //will be TRUE if button was JUST released
      FDATA += ",S";   
    else
      FDATA += ",W";
      
    FDATA += "," +String(ps2x.Analog(PSS_LY));  
    FDATA += "," +String(ps2x.Analog(PSS_LX));
    FDATA += "," +String(ps2x.Analog(PSS_RX));
    FDATA += "," +String(ps2x.Analog(PSS_RY));
    
    if(set){
      Serial1.println("Control->"+FDATA);  // Reset //Serial end of line flag
    set=!set;
    }
    else{
      while (Serial1.available()) {                  // If Arduino's computer rx buffer has data
        SerialByteIn = Serial1.read();               // Store each character in byteIn
        SerialReadBuffer += char(SerialByteIn);     // Write each character of byteIn to //SerialReadBuffer
        if (SerialByteIn == '\n') {                 // Check to see if at the end of the line
          SerialEnd = true;                         // Set //SerialEnd flag to indicate end of line
        }
        
      }
    
      if (SerialEnd) {                              // Check to see if //SerialEnd flag is true
      
        
        if (SerialReadBuffer.startsWith("Robot->") and SerialReadBuffer.endsWith("\n")) {    // Has a command been sent from local computer
           Serial.print("Receido Robot: "); 
           SerialReadBuffer.remove(0,7);
           Serial.print(SerialReadBuffer);  
           set=!set;
        } 
        SerialReadBuffer = "";                      // Clear //SerialReadBuffer
        SerialEnd = false; 
        
        
      }
      
    }
  
}
