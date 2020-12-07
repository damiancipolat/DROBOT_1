#include <IRremote.h>
#include "pins.h"
#include "engine.h"
#include "ligths.h"
#include "compass.h"
#include "keys.h"

//Setup Ir sensor.
IRrecv irrecv(IR);
decode_results irCode;

//Set leds.
led led_front=createLigth(LED_FRONT);
led led_back=createLigth(LED_BACK);
led led_signal_left=createLigth(LED_SIGNAL_LEFT);
led led_signal_rigth=createLigth(LED_SIGNAL_RIGTH);

//Set engines.
engine motorA=createEngine(ENA,IN1,IN2);
engine motorB=createEngine(ENB,IN3,IN4);

//VARIABLES
float desired = 90;
float angulo=0;
bool active=true;

//------------------------------------------------------------------

//Drive a robot forward.
void drive_robot_forward(led ledA,led ledB, engine motorA, engine motorB, float desired_heading, float heading,int desviation){

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
      turnOn(ledA);
      turnOff(ledB);
      turnLeft(motorA,motorB);
    }else{
      turnOff(ledA);
      turnOn(ledB);      
      turnRigth(motorA,motorB);
   }
 }
}

int getIrData(){
  if (irrecv.decode(&irCode)) {
    int value = irCode.value;
    irrecv.resume();
    return value;
  }  
}

  
//String converter.
char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}

//Arduino events.
void setup(){    
  Serial.begin(9600);
  Serial.println("Listo!");
  enableCompass();
  irrecv.enableIRIn();
}

int old_command=0;
int new_command=0;
int command=0;

void loop() {
  
  //Get the heading angle.
  angulo = getAcimut();
  //Serial.println("Acimut:"+(String)angulo+"°");

  //Get IR data.
  int new_command = getIrData();

  if (old_command!=new_command){
    command=new_command;
    old_command=new_command;
  }else{
    command=0;
  }
  
  if (command!=-1){
    Serial.println("Command"+(String)command);
  }    

  //Forward
  if (command==UP){
    forward(motorA);
    forward(motorB);
  }

  //Reverse
  if (command==DOWN){
    reverse(motorA);
    reverse(motorB);
  }

  //Left
  if (command==LEFT){
    turnLeft(motorA,motorB);
  }

  //Rigth
  if (command==RIGTH){
    turnRigth(motorA,motorB);
  }

  //Stop
  if (command==OK){
    pause(motorA);
    pause(motorB);
  }

  //Serial.println();
    //delay(1500);
  //Drive.
 // drive_robot_forward(led_front,led_back,motorA,motorB,desired,angulo,5);

  //left 4335
  //up 6375
  //down 19125
  //rigth 23205
  //ok 14535
 
}
