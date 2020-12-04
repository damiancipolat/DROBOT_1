#include "pins.h"
#include "ligths.h"
#include "engine.h"
#include "compass.h"
#include "bluetooth.h"
#include "driver.h"

//Set leds.
led led_front=createLigth(LED_FRONT);
led led_back=createLigth(LED_BACK);

//Set engines.
engine motorA=createEngine(ENA,IN1,IN2);
engine motorB=createEngine(ENB,IN3,IN4);

//Set boards.
bth bthBoard=createBoard(TX,RX);

String DATO="0";

void setup(){
  enableCompass();
  Serial.begin(9600);
  Serial.println("Listo!");
}

void loop() {

 // turnRigth(motorA,motorB);
  /*turnOn(led_front);
  turnOn(led_back);
  forward(motorA);
  forward(motorB);
*/
  float angulo = getAcimut();
  Serial.println("°°°"+(String)angulo);
  /*
  if (bthBoard.serial.available()){
    DATO = bthBoard.serial.readString();
    Serial.println(DATO);
  }*/
    drive(motorA, motorB, 90,angulo,5);
}
