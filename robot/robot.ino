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

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

//Drive a robot forward.
void drive_robot_forward(led ledA,led ledB, engine motorA, engine motorB, float desired_heading, float heading,int desviation){
  
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

//Drive a robot turning left.
void drive_robot_turn_left(led ledA,led ledB, engine motorA, engine motorB, float desired_heading, float heading,int desviation){

  desired_heading = (desired_heading - 90);
  if (desired_heading <= 0) {
    desired_heading = (desired_heading + 360);
  }

  //Move the robot.
  while ( abs(desired_heading - heading) >= desviation){
    heading = getAcimut();
        
    if (desired_heading >= 360){
      desired_heading = (desired_heading - 360);
    }
                                                                
    int x = (desired_heading-359);
    int y = (heading-x);
    int z = y-360;
    
    if (z <= 180){
      turnLeft(motorA,motorB);
    } else {
      turnRigth(motorA,motorB);
    }
  }

  //Pause car.
  pause(motorA);
  pause(motorB);

}

//Drive a robot turning rigth.
void drive_robot_turn_rigth(led ledA,led ledB, engine motorA, engine motorB, float desired_heading, float heading,int desviation){

  desired_heading = (desired_heading + 90);
  if (desired_heading >=360) {
    desired_heading = (desired_heading - 360);
  }

  //Move the robot.
  while ( abs(desired_heading - heading) >= desviation){
    heading = getAcimut();
        
    if (desired_heading >= 360){
      desired_heading = (desired_heading - 360);
    }
                                                                
    int x = (desired_heading-359);
    int y = (heading-x);
    int z = y-360;

    if ((z <= 180) && (z >= 0)){
      turnLeft(motorA,motorB);
    } else {
      turnRigth(motorA,motorB);
    }
  }

  //Pause car.
  pause(motorA);
  pause(motorB);

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

    //Drive commands.
    if (cmd=="lock"){
      active=false;
    }

    if (cmd=="unlock"){
      active=true;
    }

    //Chat msgs.
    if (cmd=="log"){
      bthBoard.serial.write(string2char("Acimut:"+(String)angulo));
    }

    if (cmd=="hi"){
      bthBoard.serial.write("Hi, from your robot!");
    }

  }

  //Drive.
  if (active==true){
    turnOn(led_front);
    turnOff(led_back);
    //drive_robot_forward(led_front,led_back,motorA,motorB,desired,angulo,5);
    //drive_robot_turn_left(led_front,led_back,motorA,motorB,desired,angulo,5);
    drive_robot_turn_rigth(led_front,led_back,motorA,motorB,desired,angulo,5);
  }else{
    turnOff(led_front);
    turnOn(led_back);
    pause(motorA);
    pause(motorB);
  }

}
