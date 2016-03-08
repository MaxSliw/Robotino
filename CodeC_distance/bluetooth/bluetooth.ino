#include <SoftwareSerial.h> 
#define RxD 7
#define TxD 6
#define PINLED 9
#define LEDON() digitalWrite(PINLED, HIGH)
#define LEDOFF() digitalWrite(PINLED, LOW)
#define DEBUG_ENABLED 1

SoftwareSerial blueToothSerial(RxD,TxD);
void setup(){
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(PINLED, OUTPUT);
  LEDON();
  setupBlueToothConnection();
}
void loop(){
  char ordre;
  while(1)
    {
    if(blueToothSerial.available())
    {
      ordre = blueToothSerial.read();
      Serial.print(ordre);
      if(ordre == 'ON'){
        LEDON();
      }
      else if(ordre == 'OFF'){
        LEDOFF();
      }
  }
}
}
void setupBlueToothConnection()
{
  blueToothSerial.begin(9600);
  blueToothSerial.print("AT");
  delay(400);
  blueToothSerial.print("AT+DEFAULT"); // Restore all setup value to factory setup
  delay(2000);
  blueToothSerial.print("AT+NAMERobotino"); // set the bluetooth name as "SeeedBTSlave" ,the length of bluetooth name must less than 12 characters.
  delay(400);
  blueToothSerial.print("AT+PIN0000"); //Changement du code pin
  delay(400);
  blueToothSerial.print("AT+AUTH1");
  delay(400);
  blueToothSerial.flush();
}
