/*************************************************************
   Commande du robot via Bluetooth
   Anthony et Paul
   Projet Robotino
*************************************************************/
#include <SoftwareSerial.h>
#include <NewPing.h>
#define RxD 7
#define TxD 6
#define TRIGGER_PIN 5
#define ECHO_PIN 4
#define sens 12
#define frein 9
#define vitesse 3
#define DEBUG_ENABLED 1
#define MAX_DISTANCE 200

SoftwareSerial blueToothSerial(RxD,TxD);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

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
  unsigned int uS_cm;
  while(1){
    uS_cm = sonar.ping_cm();
    Serial.println(uS_cm);
    if(blueToothSerial.available()) {
      msg = blueToothSerial.readString();
      Serial.println("Ordre: " + msg);
      if(msg.length() >= 5 && msg.substring(0,1) == "1"){
        if(msg.substring(1,3) == "m1"){
          Serial.println("Avant");
          digitalWrite(sens , HIGH);
          digitalWrite(frein, LOW);
          vit = msg.substring(3,6).toInt();
          analogWrite(vitesse, vit);
        }else if(msg.substring(1,3) == "m0"){
          Serial.println("Arret");
          digitalWrite(frein, HIGH);
          analogWrite(vitesse, 0);
        }else if(msg.substring(1,3) == "m2"){
          Serial.println("derriere");
          digitalWrite(sens , LOW);
          digitalWrite(frein, LOW);
          vit = msg.substring(3,6).toInt();
          analogWrite(vitesse, vit);
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
