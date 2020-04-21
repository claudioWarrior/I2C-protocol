#include <Wire.h>
#include <ESP8266WiFi.h>

//const char* ssid = "JioFi_109F2C9";  
//const char* password = "m062f0b0l6"; 
const char* ssid = "TP-Link_F744";  
const char* password = "00264235";  
WiFiClient client;  
const char* server = "api.thingspeak.com";  
String apiWritekey = "93XDVJV55HFAFDLB"; 

//char aa[3];
void setup() {
  Wire.begin(D1,D2);        // join i2c bus
  Serial.begin(9600);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println(); 
}

void loop() {
  Wire.requestFrom(8,10);    
  String data,dataV,dataW;
  int x;
  do{
    char c=Wire.read();
    data=data+c;
    dataV=data.substring(0,5);
    dataW=data.substring(5);
  }while(Wire.available());
//    Serial.print(dataV);
//    Serial.print(dataW);

///////////////////////////////////////////////////
    if (client.connect(server,80))
    {  
      String tsData = apiWritekey;
      tsData +="&field1=";
      tsData += dataV;
      tsData +="&field2=";
      tsData += dataW;
      tsData += "\r\n\r\n";
 
       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(tsData.length());
       client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
       client.print(tsData);
 
      Serial.print(dataV);
      Serial.print(",");
      Serial.println(dataW);
      Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  delay(15000);//Wait 5 seconds before accessing sensor again. 
}
