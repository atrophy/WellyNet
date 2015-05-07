/*
  WellyNet Network Monitor
  Will receive WellyNet packets addressed to it and dump over hardware serial
*/


#include <WellyNet.h>

#define COM_PIN 12
#define WN_ADDRESS 0x5

WellyNet myWelly(COM_PIN,WN_ADDRESS);

void setup(){
  myWelly.begin(9600);
  Serial.begin(9600);
}

void loop(){
  int command[10];
  
  if (myWelly.getPacket(command))
  {
    Serial.println("WellyNet Packet Received!");
    
    Serial.print("Addressed to:");
    Serial.println(command[0]);
    
    Serial.print("From: ");
    Serial.println(command[1]);
    
    Serial.print("Code: ");
    Serial.write(command[2]);
    Serial.println();
    
    Serial.print("Number: ");
    Serial.println(command[3]);
    
    for (int i = 4; i < 9; i++)
    {
      Serial.print("Payload byte ");
      Serial.print(i-4);
      Serial.print(": ");
      Serial.println(command[i]);
    }
    
    int checksum = myWelly.checksumCalc(command);
    Serial.print("Checksum: ");
    if (checksum == command[9])
    {
      Serial.println("OK");
    }
    else
    {
      Serial.println("Error!");
    }
    Serial.println();
    
  }
}

