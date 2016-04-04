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

void setup() {
  Serial.begin(9600);
  pinMode(captor_trig, OUTPUT);
  pinMode(captor_echo, INPUT);
  digitalWrite(captor_trig, LOW);
  pinMode(sens, OUTPUT); //Direction du moteur
  pinMode(frein, OUTPUT); //Frein du moteur
  pinMode(bt_avant, INPUT); //Bouton pour faire avancer le robot
  pinMode(bt_arriere, INPUT); //Bouton pour faire reculer et tourner le robot
}

void loop(){
  digitalWrite(captor_trig, HIGH);
  delay(500);
  digitalWrite(captor_trig, LOW);
  unsigned long duree = pulseIn(captor_echo, HIGH);
  Serial.println(duree);
  etat_bt_avant = digitalRead(bt_avant);
  etat_bt_arriere = digitalRead(bt_arriere);
    if (etat_bt_avant ==  HIGH){
    Serial.println("avant");
    digitalWrite(sens , HIGH);
    digitalWrite(frein, LOW);
    analogWrite(vitesse, 255);
  }else if (etat_bt_arriere == HIGH){
    Serial.println("arriere");
    digitalWrite(sens , LOW);
    digitalWrite(frein, LOW);
    analogWrite(vitesse, 255);
  }
  if (duree < 800) {
    analogWrite(vitesse, 0);
  }
  if (duree > 800) {
    analogWrite(vitesse, 255) ;
  }
  
}
