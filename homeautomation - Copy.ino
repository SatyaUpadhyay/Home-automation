#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
int relay0 = D0;
int relay1 = D1;
int relay2 = D2;
int relay3 = D3;
int relay4 = D4;
//Your Domain name with URL path or IP address with path
String serverName = "http://15.207.217.5:8050/api";
String serverName1 = "http://15.207.217.5:8050/api/socket-switches-list?device_id=DVC112";



unsigned long lastTime = 0;
unsigned long timerDelay = 2000;
//Variables
int i = 0;
int statusCode;
const char* ssid = "text";
const char* passphrase = "text";
String st;
String content;

bool testWifi(void);
void launchWeb(void);
void setupAP(void);

//Establishing Local server at port 80 whenever required
ESP8266WebServer server(80);

void setup()
{

  Serial.begin(115200);
pinMode(relay0, OUTPUT);
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
digitalWrite(relay0, HIGH);
digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, HIGH);
  Serial.println();
  Serial.println("Disconnecting previously connected WiFi");
  WiFi.disconnect();
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");

  //---------------------------------------- Read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");

  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");

  String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);


  WiFi.begin(esid.c_str(), epass.c_str());
  if (testWifi())
  {
    Serial.println("Succesfully Connected!!!");
    return;
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    launchWeb();
    setupAP();// Setup HotSpot
  }

  Serial.println();
  Serial.println("Waiting.");
  
  while ((WiFi.status() != WL_CONNECTED))
  {
    Serial.print(".");
    delay(100);
    server.handleClient();
  }

}
void loop() {
   //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName;
      String serverPath1 = serverName1;
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      http.begin(serverPath1.c_str());
      http.addHeader("authorization","Kd/C0gqljjf6zmhBRb5SkL5mDZhXYfkr1EVxTbKwCxE=");
      // Send HTTP GET request
      int httpResponseCode = http.GET(); 
      if (httpResponseCode>0) {
        //Serial.print("HTTP Response code: ");
        String payload = http.getString();
     if(payload.substring(16,22)=="SWC016" && payload.substring(42,43)=="1")
      {
     digitalWrite(D0,LOW);
      }
       else if(payload.substring(16,22)=="SWC016" && payload.substring(42,43)=="0"){
       digitalWrite(D0,HIGH);
     }
      if(payload.substring(61,67)=="SWC017" && payload.substring(87,88)=="1")
       {
      digitalWrite(D1,LOW);
     }
      else if(payload.substring(61,67)=="SWC017" && payload.substring(87,88)=="0"){
      digitalWrite(D1,HIGH);
       }
      if(payload.substring(106,112)=="SWC018" && payload.substring(132,133)=="1")
       {
       digitalWrite(D2,LOW);
      }
       else if(payload.substring(106,112)=="SWC018" && payload.substring(132,133)=="0"){
       digitalWrite(D2,HIGH);
      }
       if(payload.substring(151,157)=="SWC019" && payload.substring(177,178)=="1")
       {
       digitalWrite(D3,LOW);
      }
       else if(payload.substring(151,157)=="SWC019" && payload.substring(177,178)=="0"){
       digitalWrite(D3,HIGH);
     }
       if(payload.substring(196,202)=="SWC015" && payload.substring(222,223)=="1")
      {
       ESP.reset();
      }
      }
      http.end();
    }
    lastTime = millis();
  }  


}


//----------------------------------------------- Fuctions used for WiFi credentials saving and connecting to it which you do not need to change 
bool testWifi(void)
{
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED)
    {
      return true;
    }
    delay(500);
    Serial.print("*");
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  createWebServer();
  // Start the server
  server.begin();
  Serial.println("Server started");
}

void setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  st = "<ol>";
  for (int i = 0; i < n; ++i)
  {
    // Print SSID and RSSI for each network found
    st += "<li>";
    st += WiFi.SSID(i);
    st += " (";
    st += WiFi.RSSI(i);

    st += ")";
    st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
    st += "</li>";
  }
  st += "</ol>";
  delay(100);
  WiFi.softAP("SE TECH DVC444", "");
  Serial.println("softap");
  launchWeb();
  Serial.println("over");
}

void createWebServer()
{
 {
    server.on("/", []() {

      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
       content = "<!DOCTYPE HTML><meta charset='utf-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><html><meta name='viewport' content='width=device-width, initial-scale=1'><body style='margin:0;padding:40px'><p style=text-align:left;font-size:24px;font-family:verdana;font-weight:500;width:100%;>SE TECH HOME</p><p style=text-align:left;font-size:18px;font-family:verdana;font-weight:500;width:100%;>Greetings from shunyaekai tech</p>";
      content += st;
      content += "<p>";
      content += "</p><form method='get' action='setting'><label style='font-size:14px;width:100%'>SSID: </label><input style='border-left:2px solid #000;border-top:2px solid #000;font-size:14px;width:100%;height:38px;margin-bottom:20px;border-radius:6px;margin-top:10px' name='ssid' length=32><label style='font-size:14px;width:100%'>PASSWORD: </label><input style='border-left:2px solid #000;border-top:2px solid #000;font-size:16px;width:100%;height:38px;margin-bottom:20px;border-radius:6px;margin-top:10px' name='pass' length=64><input style='font-size:14px;width:100%;border-radius:6px;background-color:#1fa3ec;height:38px;border-color:#1fa3ec;color:#fff;font-size:14px;margin-top:30px' type='submit'></form>";     
      content += "<form action=\"/scan\" method=\"POST\"><input style='text-align:center;font-size:14px;width:100%;border-radius:6px;background-color:#1fa3ec;height:38px;border-color:#1fa3ec;color:#fff;font-size:14px;margin-top:30px' type=\"submit\" value=\"scan\"></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    server.on("/scan", []() {
      //setupAP();
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

      content = "<!DOCTYPE HTML>\r\n<html><p style=text-align:left;font-size:28px;font-family:verdana;font-weight:500;width:100%;>SCAN DONE PLEASE GO BACK </p>";
      server.send(200, "text/html", content);
    });
   

    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) {
        Serial.println("clearing eeprom");
        for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
        }
        Serial.println(qsid);
        Serial.println("");
        Serial.println(qpass);
        Serial.println("");

        Serial.println("writing eeprom ssid:");
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
          Serial.print("Wrote: ");
          Serial.println(qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
          Serial.print("Wrote: ");
          Serial.println(qpass[i]);
        }
        EEPROM.commit();

        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        server.send(200, "text/html", content);
        statusCode = 200;
        ESP.reset();
      } else {
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);

    });
  } 
}
