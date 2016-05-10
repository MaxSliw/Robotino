/*************************************************************
   Commande du robot via Bluetooth
   Anthony et Paul
   Projet Robotino
*************************************************************/
#include <SoftwareSerial.h> //Librairie pour communication série
#include <NewPing.h> //Librairie pour le capteur télémètre à ultrason
#define RxD 7
#define TxD 6
#define TRIGGER_PIN 5
#define ECHO_PIN 4
#define MAX_DISTANCE 200
#define sens 12
#define frein 9
#define vitesse 3 //Vit min du moteur -> 60 / Vit max -> 255 
#define analog_sim A3
#define DEBUG_ENABLED 1

SoftwareSerial blueToothSerial(RxD,TxD); //Définition des pins RxD et TxD de la liaison série voulu
NewPing captor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); //Définition des pins TRIGGER et ECHO du capteur et de la distance max(delay)

void setup(){
  Serial.begin(115200); //Initialisation de liaison série entre l'ordinateur et l'Arduino (moniteur) à 115200 bits/seconde
  pinMode(RxD, INPUT); //RxD -> entrée (R = receive)
  pinMode(TxD, OUTPUT); //TxD -> sortie (T = transmission)
  pinMode(sens, OUTPUT); //Direction du moteur
  pinMode(frein, OUTPUT); //Frein du moteur
  pinMode(vitesse, OUTPUT); //Vitesse du moteur de 0 à 255 (PWM)
  pinMode(analog_sim, OUTPUT);
  setupBlueToothConnection(); //Configuration module Bluetooth
  blueToothSerial.setTimeout(60);
}

void loop(){
  int value_anal;
  String msg;
  unsigned int uS_cm;
  int vit;
  while(1){
    dist_cm = captor.ping_cm();
    delay(60);
    value_anal = analogRead(analog_sim);
    Serial.println(dist_cm);
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
        }else if(msg.substring(1,3) == "d1"){
          blueToothSerial.write(dist_cm);
        }
      }
    }
  }
}

void setupBlueToothConnection()
{
        blueToothSerial.begin(57600);
        blueToothSerial.print("AT");
        delay(400);
        blueToothSerial.print("AT+NAMERobotino");
        delay(400);
        blueToothSerial.print("AT+UART701");
        delay(400);
        blueToothSerial.print("AT+AUTH1");
        delay(400);
        blueToothSerial.flush();
}
