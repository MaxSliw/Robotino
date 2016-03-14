/*************************************************************
Commande du robot via Bluetooth
Anthony et Paul
Projet Robotino
*************************************************************/
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
  String msg;
  while(1)
  {
    if(blueToothSerial.available()){
      msg = blueToothSerial.readString();
      Serial.println(msg);
      if(msg.substring(0,1) == "1"){
        if(msg.substring(1,2)== "9"){
          if(msg.substring(2,3) == "1"){
            LEDON();
          }else {
            LEDOFF();
          }
        }
      }
      msg = "";
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
