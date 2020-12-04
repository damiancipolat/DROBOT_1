#include "pins.h"
#include "ligths.h"
#include "engine.h"

//Set leds.
led led_front=createLigth(LED_FRONT);
led led_back=createLigth(LED_BACK);

//Set engines.
engine motorA=createEngine(ENA,IN1,IN2);
engine motorB=createEngine(ENB,IN3,IN4);

void setup(){
  Serial.begin(9600);    
}

void loop() {
  turnOn(led_front);
  turnOn(led_back);
  forward(motorA);
  forward(motorB);
}
