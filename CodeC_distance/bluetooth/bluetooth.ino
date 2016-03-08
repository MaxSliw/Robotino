#include <SoftwareSerial.h> 
#define RxD 7
#define TxD 6
#define PINLED 9
#define LEDON() digitalWrite(PINLED, HIGH)
#define LEDOFF() digitalWrite(PINLED, LOW)
#define DEBUG_ENABLED 1
SoftwareSerial blueToothSerial(RxD,TxD);
void setup()
{
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(PINLED, OUTPUT);
  LEDON();
  setupBlueToothConnection();
}
void loop()
{
  char recvChar;
  while(1)
    {
    if(blueToothSerial.available())
    {
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);
      if(recvChar == '1')
      {
      LEDON();
      }
      else if(recvChar == '0')
      {
      LEDOFF();
      }
    }
  }
}
{
  blueToothSerial.begin(9600);
  blueToothSerial.print("AT");
  delay(400);
  blueToothSerial.print("AT+DEFAULT"); // Restore all setup value to factory setup
  delay(2000);
  blueToothSerial.print("AT+NAMESeeedBTSlave"); // set the bluetooth name as "SeeedBTSlave" ,the length of bluetooth name must less than 12 characters.
  delay(400);
  blueToothSerial.print("AT+PIN0000"); // set the pair code to connect
  delay(400);
  blueToothSerial.print("AT+AUTH1"); //
  delay(400);
  blueToothSerial.flush();
}
