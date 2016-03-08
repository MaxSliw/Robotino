#include <SoftwareSerial.h> 
#define RxD 7
#define TxD 6
#define PINLED 9
#define LEDON() digitalWrite(PINLED, HIGH)
#define LEDOFF() digitalWrite(PINLED, LOW)
#define DEBUG_ENABLED 1

<<<<<<< HEAD
#define RxD         7
#define TxD         6
#define DEBUG_ENABLED  1
#define led 9
char msg; //ou char
//+ cs 0,1

SoftwareSerial blueToothSerial(RxD,TxD);
void setup() {
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(led, OUTPUT);
  setupBlueToothConnection();
}

void loop() {
  char msg;
  while(1){
    if(blueToothSerial.available()){
        msg = blueToothSerial.read();
        Serial.print(msg);
        if(msg == '0'){
          digitalWrite(led, HIGH);
        }else if(msg == '1'){
           digitalWrite(led, LOW);
        }
        delay(10);
    }
=======
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
>>>>>>> 64cb08f675b4a8776c539c55a70560f87fd85166
  }
}
}
void setupBlueToothConnection()
<<<<<<< HEAD
{	
	blueToothSerial.begin(9600);  
	
	blueToothSerial.print("AT");
	delay(400); 

	blueToothSerial.print("AT+DEFAULT"); //Reset
	delay(2000); 
	
	blueToothSerial.print("AT+NAMESeeedBTSlave");  
	delay(400);
	
	
	blueToothSerial.print("AT+AUTH1"); 
	delay(400);    
	blueToothSerial.flush();
=======
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
>>>>>>> 64cb08f675b4a8776c539c55a70560f87fd85166
}
