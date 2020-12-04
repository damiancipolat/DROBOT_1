#include <Arduino.h>
#include "ligths.h"

led createLigth(int pinParam){
  
  //Define.
  led newLed;
  newLed.pin= pinParam;

  //Bind pin.
  pinMode(newLed.pin,OUTPUT);

  return newLed;
}

void turnOn(led tmpLed){
  digitalWrite(tmpLed.pin, HIGH);
}

void turnOff(led tmpLed){
  digitalWrite(tmpLed.pin, LOW);
}
