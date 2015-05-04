/*
  Acts as a bridge and allows a computer connected to a device with a hardware serial port to send data onto WellyNet
*/



#include <WellyNet.h>

#define COMM_PIN 4
#define WN_ADDRESS 8

WellyNet myWelly(COMM_PIN,WN_ADDRESS);

void setup(){
  myWelly.begin(9600);         // to connect with other devices
  Serial.begin(9600);            // to see who's connected
}

void loop(){
  if( myWelly.available() ){
    char c = myWelly.read();
    Serial.write(c);
  }
  if( Serial.available()){
    int i = int(Serial.read())-48;
    myWelly.write(i);
  }
}



