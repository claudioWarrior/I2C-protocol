#include "ThingSpeak.h"
#include<Wire.h>
#include <ESP8266WiFi.h>
 
//Replace your wifi credentials here
//const char* ssid = "JioFi_109F2C9";  
//const char* password = "m062f0b0l6"; 
const char* ssid = "TP-Link_F744";  
const char* password = "00264235";
 
//change your channel number here
unsigned long channel = 720852;
 
unsigned int led1=1;
 
WiFiClient  client;
 
void setup() {
  Serial.begin(9600);
  delay(100);
  
  pinMode(D3, OUTPUT);
  digitalWrite(D3, 0);
  
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);
  Wire.begin(D1,D2);
}

void loop() {
  //get the last data of the fields
  int led_1 = ThingSpeak.readFloatField(channel, led1);

  if(led_1 == 1){
    digitalWrite(D3, 1);
    Serial.println("D3 is On..!");
  }
  else if(led_1 == 0){
    digitalWrite(D3, 0);
    Serial.println("D3 is Off..!");
  }

  if(led_1 == 1){
    Serial.println("Wire is On..!");
    Wire.beginTransmission(3);
    Wire.write('H');
    Wire.endTransmission();
  }else if(led_1 == 0){
    Serial.println("Wire is Off..!");
    Wire.beginTransmission(3);
    Wire.write('L');
    Wire.endTransmission();
  }
  delay(2000);
}
