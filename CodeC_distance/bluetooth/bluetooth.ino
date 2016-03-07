#include <SoftwareSerial.h>

#define RxD         7
#define TxD         6
#define DEBUG_ENABLED  1
String msg; //ou char
//+ cs 0,1

SoftwareSerial bluetooth(RxD,TxD);
void setup() {
  Serial.begin(9600);
  while (!Serial){
    ;
  }
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  delay(1000);
  Serial.flush();
  bluetooth.flush();
}

void loop() {
  while(Serial.available()){
      delay(10);
      msg = Serial.read();
      if(msg.length() > 0){
        Serial.write(msg);
      }
  }
}

void setupBlueToothConnection()
{	
	bluetooth.begin(9600);  
	
	bluetooth.print("AT");
	delay(400); 

	bluetooth.print("AT+DEFAULT"); //Reset
	delay(2000); 
	
	bluetooth.print("AT+NAMESeeedBTSlave");  
	delay(400);
	
	
	bluetooth.print("AT+AUTH1"); 
	delay(400);    
	bluetooth.flush();
}
