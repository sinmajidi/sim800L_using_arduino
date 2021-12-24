#include <SoftwareSerial.h>
 
//Create software serial object to communicate with SIM800L
SoftwareSerial gsmSerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #3 & #2
 
char incomingByte; 
String inputString;

void setup() 
{
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    digitalWrite(12,HIGH);
    digitalWrite(12,HIGH);
    delay(500);
    digitalWrite(12,LOW);
    digitalWrite(12,LOW);
    delay(500);
    Serial.begin(9600);
    gsmSerial.begin(9600); 


    gsmSerial.println("AT");
    delay(1000); 
    gsmSerial.println("AT+CMGF=1");
    delay(1000);  
    gsmSerial.println("AT+CNMI=1,2,0,0,0"); 
    delay(1000);
    gsmSerial.println("AT+CMGL=\"REC UNREAD\"");
    Serial.print("readyyy!!");
}

void loop()
{  
  if(gsmSerial.available()){
    inputString = "";
    delay(1000);
    while(gsmSerial.available()){
      incomingByte = gsmSerial.read();
      inputString += incomingByte; 
    }
    delay(100);      
    //inputString.replace("\n","");
    Serial.print("input : ");
    Serial.print(inputString);
    Serial.println("   end");
    
    inputString.toUpperCase();
    Serial.println("input up : " + inputString);
    if (inputString.indexOf("ON1") > 0){
      digitalWrite(12, HIGH);
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
    }
    if (inputString.indexOf("ON2") > 0){
      digitalWrite(13, HIGH);
    } 
    if (inputString.indexOf("OFF1") > 0){
      digitalWrite(12, LOW);
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
    }
    if (inputString.indexOf("OFF2") > 0){
      digitalWrite(13, LOW);
    }         
//    delay(50);
//    if (inputString.indexOf("OK") > -1){
//      gsmSerial.println("AT+CMGD=\"DEL ALL\"");
//      delay(1000);
//    } 
  }
}
