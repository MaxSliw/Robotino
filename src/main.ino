/*************************************************************
   Commande du robot via Bluetooth
   Anthony et Paul
   Projet Robotino
*************************************************************/
#include <SoftwareSerial.h>
#define RxD 7
#define TxD 6
//#define LEDON() digitalWrite(PINLED, HIGH)
//#define LEDOFF() digitalWrite(PINLED, LOW)
#define DEBUG_ENABLED 1

SoftwareSerial blueToothSerial(RxD,TxD);
const int sens = 12;
const int frein = 9;
const int vitesse = 3;

void setup(){
  Serial.begin(115200);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(sens, OUTPUT); //Direction du moteur
  pinMode(frein, OUTPUT); //Frein du moteur
  setupBlueToothConnection();
  blueToothSerial.setTimeout(50);
}

void loop(){
  String msg;
  while(1){
    if(blueToothSerial.available()) {
      msg = blueToothSerial.readString();
      Serial.println("Ordre: " + msg);
      if(msg.length() >= 5 && msg.substring(0,1) == "1"){
        if(msg.substring(1,3) == "m1"){
          Serial.println("Avant");
          digitalWrite(sens , HIGH);
          digitalWrite(frein, LOW);
          analogWrite(vitesse, msg.substring(3,5));
        }else if(msg.substring(1,3) == "m0"){
          Serial.println("Arret");
          digitalWrite(frein, HIGH);
          analogWrite(vitesse, 0);
        }else if(msg.substring(1,3) == "m2"){
          Serial.println("derriere");
          digitalWrite(sens , LOW);
          digitalWrite(frein, LOW);
          analogWrite(vitesse, msg.substring(3,5));
        }
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
        blueToothSerial.print("AT+UART115200");
        delay(400);
        blueToothSerial.print("AT+AUTH1");
        //blueToothSerial.print("AT+BAUD8");
        delay(400);
        blueToothSerial.flush();

}
