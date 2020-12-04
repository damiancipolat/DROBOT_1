#include <Arduino.h>
#include "pins.h"
#include "ligths.h"

void setup_leds(){
  pinMode(LED_FRONT,OUTPUT);
  pinMode(LED_BACK,OUTPUT);
}

void front_ligth(bool state){
  if (state==true)
    digitalWrite(LED_FRONT, HIGH);
  else
    digitalWrite(LED_FRONT, LOW);
}

void back_ligth(bool state){
  if (state==true)
    digitalWrite(LED_BACK, HIGH);
  else
    digitalWrite(LED_BACK, LOW);
}
