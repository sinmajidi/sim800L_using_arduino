#include <SoftwareSerial.h>
const String PHONE = "+989128559089"; 
//Create software serial object to communicate with SIM800L
SoftwareSerial gsmSerial(12, 14); //SIM800L Tx & Rx is connected to Arduino #12 & #14
 
char incomingByte; 
String inputString;
int status_relay_1,status_relay_2,status_relay_3,status_relay_4;
String status_total;
void Reply(String text)
{
    gsmSerial.print("AT+CMGF=1\r");
    delay(1000);
    gsmSerial.print("AT+CMGS=\""+PHONE+"\"\r");
    delay(1000);
    gsmSerial.print(text);
    delay(100);
    gsmSerial.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
    delay(1000);
    Serial.println("SMS Sent Successfully.");
}
void setup() 
{
    pinMode(5, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(15, OUTPUT);
    digitalWrite(5,HIGH);
    digitalWrite(16,HIGH);
    digitalWrite(13,HIGH);
    digitalWrite(15,HIGH);
    delay(500);
    digitalWrite(5,LOW);
    digitalWrite(16,LOW);
    digitalWrite(13,LOW);
    digitalWrite(15,LOW);
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
      digitalWrite(5, HIGH);
      status_relay_1=1;
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      Reply("Relay 1 has been ON");;
    }
    if (inputString.indexOf("OFF1") > 0){
      digitalWrite(5, LOW);
      status_relay_1=0;
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      Reply("Relay 1 has been OFF");
    }
    if (inputString.indexOf("ON2") > 0){
      digitalWrite(16, HIGH);
      status_relay_2=1;
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      Reply("Relay 2 has been ON");
    } 
    if (inputString.indexOf("OFF2") > 0){
      digitalWrite(16, LOW);
      status_relay_2=0;
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      Reply("Relay 2 has been OFF");
    }   
    if (inputString.indexOf("ON3") > 0){
      digitalWrite(13, HIGH);
      status_relay_3=1;
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      Reply("Relay 3 has been ON");
    }      
    if (inputString.indexOf("OFF3") > 0){
      digitalWrite(13, LOW);
      status_relay_3=0;
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      Reply("Relay 3 has been OFF");
    }   
    if (inputString.indexOf("ON4") > 0){
      digitalWrite(15, HIGH);
      status_relay_4=1;
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      Reply("Relay 4 has been ON");
    }      
    if (inputString.indexOf("OFF4") > 0){
      digitalWrite(15, LOW);
      status_relay_4=0;
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      Reply("Relay 4 has been OFF");
    }       
    if (inputString.indexOf("STATUS") > 0){
      status_total="";
      if(status_relay_1)
      status_total+="relay 1 is on ,";
      else
      status_total+="relay 1 is off ,";
      if(status_relay_2)
      status_total+="relay 2 is on ,";
      else
      status_total+="relay 2 is off ,";
      if(status_relay_3)
      status_total+="relay 3 is on ,";
      else
      status_total+="relay 3 is off ,";
      if(status_relay_4)
      status_total+="relay 4 is on ,";
      else
      status_total+="relay 4 is off ,";
      Reply(status_total);
      gsmSerial.println("AT+CMGDA=\"DEL ALL\"");
      
    }         
 
  }
}
