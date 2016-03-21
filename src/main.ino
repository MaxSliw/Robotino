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
  Serial.begin(115200);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(PINLED, OUTPUT);
  LEDON();
  setupBlueToothConnection();
  blueToothSerial.setTimeout(50);
}

void loop(){
  String msg;
  while(1){
    if(blueToothSerial.available()) {
      msg = blueToothSerial.readString();
      Serial.println(msg);
      if(msg.length() >= 5 && msg.substring(0,1) == "1"){
        
      }
    }
  }
}

void setupBlueToothConnection()
{
  blueToothSerial.begin(9600);
        blueToothSerial.print("AT");
        delay(400);
        blueToothSerial.print("AT+DEFAULT");
        delay(2000);
        blueToothSerial.print("AT+NAMERobotino");
        delay(400);
        blueToothSerial.print("AT+UART115200,1,0");
        delay(400);
        blueToothSerial.print("AT+AUTH1");
        //blueToothSerial.print("AT+BAUD8");
        delay(400);
        blueToothSerial.flush();

}
