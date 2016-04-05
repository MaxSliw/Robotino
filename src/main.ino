/*************************************************************
Deplacement du robot
Anthony et Paul
Projet Robotino
*************************************************************/
const int sens = 12;
const int frein = 9;
const int vitesse = 3;
const int bt_avant = 2;
const int bt_arriere = 4;
const int captor_echo = 11;
const int captor_trig = 8;
int etat_bt_avant;
int etat_bt_arriere;
int time = 30;
void setup() {
  pinMode(captor_trig, OUTPUT);
  pinMode(captor_echo, INPUT);
  digitalWrite(captor_trig, LOW);
  pinMode(sens, OUTPUT); //Direction du moteur
  pinMode(frein, OUTPUT); //Frein du moteur
  pinMode(bt_avant, INPUT); //Bouton pour faire avancer le robot
  pinMode(bt_arriere, INPUT); //Bouton pour faire reculer et tourner le robot
  digitalWrite(sens , LOW);
}

void loop(){
  digitalWrite(captor_trig, HIGH);
  delay(300);
  digitalWrite(captor_trig, LOW);
  unsigned long dist = pulseIn(captor_echo, HIGH);
  etat_bt_avant = digitalRead(bt_avant);
  etat_bt_arriere = digitalRead(bt_arriere);

  if (dist < 900) {
    digitalWrite(sens , LOW);
    analogWrite(vitesse, 255);
    time = 1000;
  }else{
    digitalWrite(sens , HIGH);
    analogWrite(vitesse, 255);
    time= 30;
  } 
}
