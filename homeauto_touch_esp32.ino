#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
//15.207.217.5
//const char* ssid = "SETech_airtel";
//const char* password = "Airtel@9999";
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
String deviceid;//"D4-0000000003 _SEHOME";//"D2-HAD45M3NB45DD";
int button1=0;
int button2=0;
int button3=0;
int button4=0;
static int taskCore = 0;
String receivedChar, num,data,ssid="",pass="",recivedData;   
int len,rcvLen;
void writeString(char add, String data);
 
void coreTask( void * pvParameters ){
 
    while(true){
      HTTPClient http;
        //Serial.println(taskMessage);
         if(digitalRead(26) == HIGH) {
    button1=button1+1;
    if(button1==1){
    digitalWrite(4, HIGH);
    Serial.println("HIGH0");
     HTTPClient http;  //Declare an object of class HTTPClient
    http.begin("http://supro.shunyaekai.tech:8050/api/switche-on-off-by-device?switch_id=SWC003&device_id="+deviceid+"&switche_status=1");
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
    http.GET();
    delay(1000);
  } 
  else if(button1==2) {
    button1=0;
    Serial.println("LOW0");
    digitalWrite(4, LOW);
    http.begin("http://supro.shunyaekai.tech:8050/api/switche-on-off-by-device?switch_id=SWC003&device_id="+deviceid+"&switche_status=2");
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
    http.GET();
    delay(1000);
  }}
  if(digitalRead(25) == HIGH) {
    button2=button2+1;
    if(button2==1){
    digitalWrite(2, HIGH);
    Serial.println("HIGH1");
    http.begin("http://supro.shunyaekai.tech:8050/api/switche-on-off-by-device?switch_id=SWC002&device_id="+deviceid+"&switche_status=1");
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
    http.GET();
    delay(1000);
  } 
  else if(button2==2) {
    button2=0;
    Serial.println("LOW1");
    digitalWrite(2, LOW);
    http.begin("http://supro.shunyaekai.tech:8050/api/switche-on-off-by-device?switch_id=SWC002&device_id="+deviceid+"&switche_status=2");
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
    http.GET();
    delay(1000);
  }}
   if(digitalRead(23) == HIGH) {
    button3=button3+1;
    if(button3==1){
    digitalWrite(21, HIGH);
    Serial.println("HIGH2");
    http.begin("http://supro.shunyaekai.tech:8050/api/switche-on-off-by-device?switch_id=SWC003&device_id="+deviceid+"&switche_status=1");
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
    http.GET();
    delay(1000);
  } 
  else if(button3==2) {
    button3=0;
    Serial.println("LOW2");
    digitalWrite(21, LOW);
    http.begin("http://supro.shunyaekai.tech:8050/api/switche-on-off-by-device?switch_id=SWC003&device_id="+deviceid+"&switche_status=2");
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
    http.GET();
    delay(1000);
  }}
   if(digitalRead(18) == HIGH) {
    button4=button4+1;
    if(button4==1){
    digitalWrite(22, HIGH);
    Serial.println("HIGH3");
    http.begin("http://supro.shunyaekai.tech:8050/api/switche-on-off-by-device?switch_id=SWC004&device_id="+deviceid+"&switche_status=1");
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
    http.GET();
    delay(1000);
    
  } 
  else if(button4==2) {
    button4=0;
    Serial.println("LOW3");
    digitalWrite(22, LOW);
    http.begin("http://supro.shunyaekai.tech:8050/api/switche-on-off-by-device?switch_id=SWC004&device_id="+deviceid+"&switche_status=2");
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
    http.GET();
    delay(1000);
  }}
 
    }
 
}

 
void setup() {
 
  Serial.begin(112500);
  delay(1000);
 pinMode(26, INPUT);
  pinMode(25, INPUT);
  pinMode(23, INPUT);
  pinMode(18, INPUT);
  pinMode(2,OUTPUT);
  //pinMode(12,OUTPUT);
  pinMode(4,OUTPUT);
  //pinMode(14,OUTPUT);
  pinMode(21,OUTPUT);
  pinMode(22,OUTPUT);
  //pinMode(12,OUTPUT);
  //pinMode(13,OUTPUT);
  digitalWrite(2,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(21,HIGH);
  digitalWrite(22,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(23,LOW);
  digitalWrite(26,LOW);
  digitalWrite(25,LOW);
  digitalWrite(18,LOW);
  
  Serial.print("Starting to create task on core ");
  Serial.println(taskCore);
  xTaskCreatePinnedToCore(
                    coreTask,   /* Function to implement the task */
                    "coreTask", /* Name of the task */
                    10000,      /* Stack size in words */
                    NULL,       /* Task input parameter */
                    0,          /* Priority of the task */
                    NULL,       /* Task handle. */
                    taskCore);  /* Core where the task should run */
 
 
  Serial.println("Task created...");
  EEPROM.begin(512);
  Serial.println(WiFi.macAddress());
  SerialBT.begin("D6-"+String(WiFi.macAddress())+"_HOM2"); //Bluetooth device name
  //SerialBT.begin("D4-0000000003_SEHOME");
   EEP();
   const char* Ssid;
   const char* password;
   Serial.print(ssid);
   Serial.print(pass);
   deviceid="D6-"+String(WiFi.macAddress())+"_HOM2";
   Ssid=ssid.c_str();
   password=pass.c_str();
   WiFi.begin(Ssid,password);
  //Serial.println("connected");
   while(WiFi.status() != WL_CONNECTED) {
    wifi_credentials();
    SerialBT.println("NOT Connected");
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
 wifi_credentials();
  Serial.println("Starting main loop...");
  while (true){
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
 delay(600);

 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://supro.shunyaekai.tech:8050/api/socket-switches-list?device_id="+deviceid);  
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");//Specify request destination
    int httpCode = http.GET();                                  //Send the request
    
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);
      //Serial.println(payload.substring(16,22));
if(payload.substring(16,22)=="SWC001" && payload.substring(42,43)=="1")
      {
       Serial.println("switch1 on");
     digitalWrite(4,LOW);
      }
      
       else if(payload.substring(16,22)=="SWC001" && payload.substring(42,43)=="0"){
       digitalWrite(4,HIGH);
      Serial.println("switch1 off");
       
     }
      if(payload.substring(61,67)=="SWC002" && payload.substring(87,88)=="1")
       {
      digitalWrite(2,LOW);
     Serial.println("switch2 on");
     }
      else if(payload.substring(61,67)=="SWC002" && payload.substring(87,88)=="0"){
      digitalWrite(2,HIGH);
     Serial.println("switch2 off");
      
       }
      if(payload.substring(106,112)=="SWC003" && payload.substring(132,133)=="1")
       {
       digitalWrite(21,LOW);
      Serial.println("switch3 on");
      }
       else if(payload.substring(106,112)=="SWC003" && payload.substring(132,133)=="0"){
       digitalWrite(21,HIGH);
      Serial.println("switch3 off");
       
      }
       if(payload.substring(151,157)=="SWC004" && payload.substring(177,178)=="1")
       {
       digitalWrite(22,LOW);
      Serial.println("switch4 on");
      }
       else if(payload.substring(151,157)=="SWC004" && payload.substring(177,178)=="0"){
       digitalWrite(22,HIGH);
      Serial.println("switch4 off");
     }
    /* if(payload.substring(196,202)=="SWC005" && payload.substring(222,223)=="1")
     {
      digitalWrite(12,LOW);
     Serial.println("switch5 on");
     }
     else if(payload.substring(196,202)=="SWC005" && payload.substring(222,223)=="0"){
      digitalWrite(12,HIGH);
     Serial.println("switch5 off");
    }
    if(payload.substring(241,247)=="SWC006" && payload.substring(267,268)=="1")
     {
      digitalWrite(13,LOW);
     Serial.println("switch6 on");
     }
     else if(payload.substring(241,247)=="SWC006" && payload.substring(267,268)=="0"){
      digitalWrite(13,HIGH);
     Serial.println("switch6 off");
    }
    if(payload.substring(286,292)=="SWC007" && payload.substring(312,313)=="1")
     {
      digitalWrite(4,LOW);
     Serial.println("switch7 on");
     }
     else if(payload.substring(286,292)=="SWC007" && payload.substring(312,313)=="0"){
      digitalWrite(4,HIGH);
     Serial.println("switch7 off");
    }
    if(payload.substring(331,337)=="SWC008" && payload.substring(357,358)=="1")
     {
      digitalWrite(5,LOW);
     Serial.println("switch8 on");
     }
     else if(payload.substring(331,337)=="SWC008" && payload.substring(357,358)=="0"){
      digitalWrite(5,HIGH);
     Serial.println("switch8 off");
    }*/
    }
 
    http.end();   //Close connection

    }  }}
   void wifi_credentials(){           //function for message command response
  num="",data="";
 if(SerialBT.available()>0){
   num = SerialBT.readString();
   //Serial.print(num);
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
   delay(1000);
   ESP.restart();
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
