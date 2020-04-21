#include<Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin(3);
  Wire.onReceive(execFun);
}

void loop() {
  }

void execFun(int hm){
  while(Wire.available()){
    char c=Wire.read();
    if(c=='1')
      Serial.print("Transaction successful");
    if(c=='0')
      Serial.print("Transaction unsuccessful");
  }
}
