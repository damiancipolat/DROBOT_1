#include "pins.h"
#include "ligths.h"
#include "engine.h"
#include "compass.h"
#include "bluetooth.h"

//Set leds.
led led_front=createLigth(LED_FRONT);
led led_back=createLigth(LED_BACK);

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
    turnOff(ledA);
    turnOff(ledB);
  } else {
      
    int x = (desired_heading - 359);
    int y = (heading - (x));
    int z = (y - 360);
                     
    if ((z <= 180) && (z >= 0)){
      turnLeft(motorA,motorB);
      turnOn(ledA);
      turnOff(ledB);
    }else{
      turnOff(ledA);
      turnOn(ledB);      
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
bool active=false;

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
      turnOn(led_front);
      turnOff(led_back);
    }

    if (cmd=="unlock"){
      active=true;      
      turnOff(led_front);
      turnOn(led_back);
    }

  }
  
  //Drive.
  if (active==true){
    drive_robot(led_front,led_back,motorA,motorB,desired,angulo,5);    
  }
  
  
  

  //forward(motorA);
  //forward(motorB);
  
  //Drive the robot.
  //if (in_pause==false)
  

}
