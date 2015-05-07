/*
  Sends a WellyNet packet once per second to the destination address specified, use with WellyNetDump to test connectivity
*/


#include <WellyNet.h>

#define COM_PIN 12
#define WN_ADDRESS 0xF

WellyNet myWelly(COM_PIN,WN_ADDRESS);

byte address = WN_ADDRESS;
byte destination = 0x5;

void setup(){
  myWelly.begin(9600);
}

int packet[10];

void loop(){
  packet[0] = destination;
  packet[1] = address;
  packet[2] = byte('T');
  packet[3] = 0x00;
  
  packet[4] = 0x00;
  packet[5] = 0x00;
  packet[6] = 0x00;
  packet[7] = 0x00;
  packet[8] = 0x00;
  
  packet[9] = myWelly.checksumCalc(packet);
  
  for (int i = 0; i < 10; i++)
  {
    myWelly.write(packet[i]);
  }
  delay(1000);
}

