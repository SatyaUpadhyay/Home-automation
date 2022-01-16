#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SETech1";
const char* password = "qwer1234";
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
String id="DVC114";
int button1=0;
int button2=0;
int button3=0;
int button4=0;
static int taskCore = 0;

 
void coreTask( void * pvParameters ){
 
   
 
    while(true){
        //Serial.println(taskMessage);
         if(digitalRead(26) == HIGH) {
    button1=button1+1;
    if(button1==1){
    digitalWrite(2, HIGH);
    Serial.println("HIGHvxhdhvdvdhvhdvdvdhvhdv0");
    delay(500);
  } 
  else if(button1==2) {
    button1=0;
    Serial.println("LOWfyftydtdtdtdtdtdtdtrdtdt");
    digitalWrite(2, LOW);
    delay(500);
  }}
  if(digitalRead(16) == HIGH) {
    button2=button2+1;
    if(button2==1){
    digitalWrite(4, HIGH);
    Serial.println("HIGH1");
    delay(500);
  } 
  else if(button2==2) {
    button2=0;
    Serial.println("LOW1");
    digitalWrite(4, LOW);
    delay(500);
  }}
   if(digitalRead(17) == HIGH) {
    button3=button3+1;
    if(button3==1){
    digitalWrite(21, HIGH);
    Serial.println("HIGH1");
    delay(500);
  } 
  else if(button3==2) {
    button3=0;
    Serial.println("LOW1");
    digitalWrite(21, LOW);
    delay(500);
  }}
   if(digitalRead(18) == HIGH) {
    button4=button4+1;
    if(button4==1){
    digitalWrite(22, HIGH);
    Serial.println("HIGH1");
    delay(500);
  } 
  else if(button4==2) {
    button4=0;
    Serial.println("LOW1");
    digitalWrite(22, LOW);
    delay(500);
  }}
 
    }
 
}

 
void setup() {
 
  Serial.begin(112500);
  delay(1000);
 pinMode(26, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
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
  digitalWrite(17,LOW);
  digitalWrite(26,LOW);
  digitalWrite(16,LOW);
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
   WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
}
 
void loop() {
 
  Serial.println("Starting main loop...");
  while (true){
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
 delay(600);

 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://15.207.217.5:8050/api/socket-switches-list?device_id="+id);  
    http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");//Specify request destination
    int httpCode = http.GET();                                  //Send the request
    
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);
      Serial.println(payload.substring(16,22));
if(payload.substring(16,22)=="SWC001" && payload.substring(42,43)=="1")
      {
       Serial.println("switch1 on");
     digitalWrite(2,LOW);
      }
      
       else if(payload.substring(16,22)=="SWC001" && payload.substring(42,43)=="0"){
       digitalWrite(2,HIGH);
      Serial.println("switch1 off");
       
     }
      if(payload.substring(61,67)=="SWC002" && payload.substring(87,88)=="1")
       {
      digitalWrite(4,LOW);
     Serial.println("switch2 on");
     }
      else if(payload.substring(61,67)=="SWC002" && payload.substring(87,88)=="0"){
      digitalWrite(4,HIGH);
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
