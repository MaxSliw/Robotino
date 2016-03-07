#include <SoftwareSerial.h>
//Moteur DC --> shield motor
const int pwm_A = 3;
const int pwm_B = 11;
const int dir_A = 12;
const int brake_A = 9;
const int brake_B = 8;
const int led_verif = 13;
String voice;
//+ cs 0,1

//SoftwareSerial bluetooth(7,6);
void setup() {
  Serial.begin(9600);
  while (!Serial){
    ;
  }
  //pinMode(led_verif, OUTPUT);
  //pinMode(dir_A, OUTPUT);
  //pinMode(brake_A, OUTPUT);
  //pinMode(pwm_A, OUTPUT);
  //bluetooth.begin(9600);

}

void loop() {
  while(Serial.available()){
      delay(10);
      voice = Serial.read();
      if(voice.length() > 0){
        Serial.println(voice);
      }
  }
}
