#include <SoftwareSerial.h>

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
  }
}

void setupBlueToothConnection()
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
}
