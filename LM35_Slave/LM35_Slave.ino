#include <Wire.h>
 
float lmone,lmtwo;
//float resolution=((5/1024)*1000)/10;

char lmArrOne[6];
char lmArrTwo[6]; 

void setup(){
  Serial.begin(9600);
  Wire.begin(8);    //Slave ID
  Wire.onRequest(reqEvntOne); 
 }
 
void loop(){
    lmone = analogRead(A0);
    lmone=lmone*0.48828125;
    lmtwo = analogRead(A1);
    lmtwo=lmtwo*0.48828125;
  
    dtostrf(lmone,5,2,lmArrOne);
    dtostrf(lmtwo,5,2,lmArrTwo);
//    Serial.print(lmArrOne);
//    Serial.print(",");
//    Serial.println(lmArrTwo);
    delay(15000);//Wait 5 seconds before accessing sensor again. 
}

void reqEvntOne() {
    Wire.write(lmArrOne);
    Wire.write(lmArrTwo);
}
