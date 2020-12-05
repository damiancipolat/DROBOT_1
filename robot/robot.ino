#include "pins.h"
#include "ligths.h"
#include "engine.h"
#include "compass.h"
#include "bluetooth.h"

//Set leds.
led led_front=createLigth(LED_FRONT);
led led_back=createLigth(LED_BACK);
led led_signal_left=createLigth(LED_SIGNAL_LEFT);
led led_signal_rigth=createLigth(LED_SIGNAL_RIGTH);

//Set engines.
engine motorA=createEngine(ENA,IN1,IN2);
engine motorB=createEngine(ENB,IN3,IN4);

//Set boards.
bth bthBoard=createBoard(TX,RX);

//Drive a robot.
void drive_robot(led ledA,led ledB, engine motorA, engine motorB, float desired_heading, float heading,int desviation){
  
  if (abs(desired_heading-heading)<=desviation){
    forward(motorA);
    forward(motorB);
    turnOff(led_signal_left);
    turnOff(led_signal_rigth);    
  } else {
      
    int x = (desired_heading - 359);
    int y = (heading - (x));
    int z = (y - 360);
                     
    if ((z <= 180) && (z >= 0)){
      turnOn(led_signal_left);
      turnOff(led_signal_rigth);
      turnLeft(motorA,motorB);
    }else{
      turnOff(led_signal_left);
      turnOn(led_signal_rigth);      
      turnRigth(motorA,motorB);
   }
 }
}

//Arduino events.
void setup(){
  enableCompass();
  Serial.begin(9600);
  Serial.println("Listo!");
}

//States.
float desired = 90;
bool active=true;

void loop() {

  //Get the heading angle.
  float angulo = getAcimut();
  Serial.println("Acimut:"+(String)angulo+"°");

  //Bluetooth controller.
  if (bthBoard.serial.available()){

    //Get the command from the board.
    String cmd = bthBoard.serial.readString();
    Serial.println("Received command:"+cmd);

    if (cmd=="lock"){
      active=false;
    }

    if (cmd=="unlock"){
      active=true;
    }

  }
  
  //Drive.
  if (active==true){
    turnOn(led_front);
    turnOff(led_back);
    drive_robot(led_front,led_back,motorA,motorB,desired,angulo,5);
  }else{
    turnOff(led_front);
    turnOn(led_back);    
    pause(motorA);
    pause(motorB);
  }

}
