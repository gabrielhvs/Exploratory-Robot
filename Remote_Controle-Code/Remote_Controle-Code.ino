//Programa : Controle servo motor com joystick
//Autor : FILIPEFLOP


#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void BeginHC12(int baundRate) {
  mySerial.begin(baundRate);
}


String out,date,out2;
int pino_x1 = A0; //Pino ligado ao X do joystick
int pino_y1 = A1; //Pino ligado ao Y do joystick
int val_x1;   //Armazena o valor do eixo X
int val_y1;   //Armazena o valor do eixo X
int Ant_val_x1 = 0; //Armazena o valor do eixo X
int Ant_val_y1 = 0; //Armazena o valor do eixo X
int pino_x2 = A2; //Pino ligado ao X do joystick
int pino_y2 = A3; //Pino ligado ao Y do joystick
int val_x2;   //Armazena o valor do eixo X
int val_y2;   //Armazena o valor do eixo X
int Ant_val_x2 = 0; //Armazena o valor do eixo X
int Ant_val_y2 = 0; //Armazena o valor do eixo X
int pinb1 = 0;
int pinb2 = 0;
int pinb3 = 0;
int pinb4 = 0;


void setup()
{
  BeginHC12(19200);
  Serial.begin(9600);
  for (int i = 6; i <= 9; i++)
    pinMode(i, INPUT_PULLUP);
}
//1-160   1-160
void loop()
{

  val_x1 = analogRead(pino_x1);
  val_y1 = analogRead(pino_y1);
  val_x2 = analogRead(pino_x2);
  val_y2 = analogRead(pino_y2);
  pinb1 = digitalRead(6);
  pinb2 = digitalRead(7);
  pinb3 = digitalRead(8);
  pinb4 = digitalRead(9);

  if (pinb1 == 0)
    out = 'A';
  else if (pinb2 == 0)
    out = 'B';
  else if (pinb3 == 0)
    out = 'C';
  else if (pinb4 == 0)
    out = 'D';
  else if (val_y2 >= 600)
    out = 'E';
  else if (val_y2 <= 400)
    out = 'F';
  else if (val_y1 >= 600)
    out = 'G';
  else if (val_y1 <= 400)
    out = 'I';
  else if (val_x2 >= 600)
    out = 'J';
  else if (val_x2 <= 400)
    out = 'K';
  else if (val_x1 >= 600)
    out = 'L';
  else if (val_x1 <= 400)
    out = 'Z';
  else
    out = 'R';

  mySerial.println(out);
  delay(10);

 
  
  
  
}
