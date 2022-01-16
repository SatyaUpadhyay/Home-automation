#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#include <WiFi.h>
#include <EEPROM.h>
String receivedChar, num,data,ssid="",pass="",recivedData;   
int len,rcvLen;
void writeString(char add, String data);
char buff1[50];
long previousMillis = 0; 

void setup() {
  Serial.begin(115200);
    EEPROM.begin(512);
  SerialBT.begin("D4-0000000001"); //Bluetooth device name
   EEP();
   const char* Ssid;
   const char* password;
   Serial.print(ssid);
   Serial.print(pass);
   Ssid=ssid.c_str();
   password=pass.c_str();
   WiFi.begin(Ssid,password);
  while(WiFi.status() != WL_CONNECTED) {
    wifi_credentials();
    //SerialBT.println("{"+"latitude"+":"+"0.0000"+","+"longitude"+":"+"0.0000"+","+"speed"+":"+"10"+","+"ac"+":"+"1"+","+"rly"+":"+"1"+","+"rfd"+":"+"BR01cu1234"+","+"volt"+":"+"11.2"+";"+"}");
    delay(2000);
  }
SerialBT.println("Connected");
delay(100);
SerialBT.println("Connected");
delay(100);
SerialBT.println("Connected");
delay(100);
}
void loop() {
  unsigned long currentMillis = millis(); 
       if(currentMillis - previousMillis > 3000) {
        previousMillis = currentMillis;
        SerialBT.println("Connected");}
  wifi_credentials();          
SerialBT.print("hello,hello2,hello3");
}

void wifi_credentials(){           //function for message command response
  num="",data="";
  
 if(SerialBT.available()>0){
   num = SerialBT.readString();
   Serial.print(num);
   len=num.length();
   delay(500);           
  if(num!=" "){
     data=num;
    if(data.length()<=len){
     while(data.length()<=len){
     data+="&";
    }
    }
    //Serial.println(data);
   delay(500);
   writeString(1, data);  //writ IP or Port on eeprom ,Address 1 and String type data
   SerialBT.print("done");
   delay(1000);
   
   //ESP.restart();
  }}}

void writeString(char add, String data) //write data in eeprom
{ int i;
  int _size = data.length();
  for (i = 0; i < _size; i++)
  { EEPROM.write(add + i, '\0');
    EEPROM.write(add + i, data[i]);
  }
  EEPROM.commit();
  }

String read_String(char add)  //read data from eeprom
{ int i, len = 0;
  char data[78]; //Max 100 Bytes
  unsigned char k;
  k = EEPROM.read(add);
  while (k != '\0' && len < 78) //Read until null character
  {
    k = EEPROM.read(add + len);
    delay(100);
    data[len] = k;
    len++;
  }
  return String(data);
  }
void EEP()
    {
  char buff[100];
  int y1=0,g2=0,j1=0,i=0,z=0,h=0;
   recivedData = read_String(1);
  
    delay(500);
  recivedData.toCharArray(buff, 100); // all receive data store in buff and extract it in IP,port and apn
  rcvLen=recivedData.length();
  for (int j1 = 0; j1 < rcvLen; j1++)
  {
    if (buff[j1] == ',')
    { y1++;
      if (y1==1)
        g2=j1;
    }
    if (buff[j1] == '&')
    { z++;
      if (z==1)
        h=j1;
    }
    }
  ssid= recivedData.substring(0 ,g2); // ssid
  pass= recivedData.substring((g2 + 1), h); //pass

   }
