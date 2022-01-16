#include "WiFi.h"
#include <HTTPClient.h>
#include <WiFi.h>
const char* ssid = "Satya";
const char* password =  "Airtel@9999";
int i=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    i=i+1;
    Serial.println(i);
    delay(1000);
    if (i>=5){break;}
    }

}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("NOT CONNECTED");
    //delay(2000);
    //WiFi.begin(ssid, password);
    ESP.restart();
    
  }
  else {
 Serial.println("Connected");
}}
