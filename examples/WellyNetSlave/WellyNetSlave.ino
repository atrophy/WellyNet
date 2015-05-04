/*
  Simple WellyNet implementation, responds with it's ID to a single byte containing it's address.
*/


#include <WellyNet.h>

#define COM_PIN 4
#define WN_ADDRESS 6

WellyNet myWelly(comPin,WN_ADDRESS);

void setup(){
  myWelly.begin(9600);
}

void loop(){
  if( myWelly.available() ){
    int i = int(myWelly.read());
    if( i == WN_ADDRESS ){
      myWelly.print("I am ");
      myWelly.println(WN_ADDRESS);
    }
  }
}

