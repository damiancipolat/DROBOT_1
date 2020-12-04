#include <Arduino.h>
#include "engine.h"

//Create an engine data type.
robot_engine createEngine(int pwmPin,int in1, int in2){

  robot_engine  newEngine;
  newEngine.enPin = pwmPin;
  newEngine.in1= in1;
  newEngine.in2= in2;

  return newEngine;
    
}

//Move the motor forward.
void forward(robot_engine paramEngine){

  //Set pwm signal.
  analogWrite(paramEngine.enPin, forwardSpeed);

  //Set pin values.
  digitalWrite(paramEngine.in1, HIGH);
  digitalWrite(paramEngine.in2, LOW);

}

//Move the motor in reverse.
void reverse(robot_engine paramEngine){

  //Set pwm signal.
  analogWrite(paramEngine.enPin, forwardSpeed);

  //Set pin values.
  digitalWrite(paramEngine.in1, LOW);
  digitalWrite(paramEngine.in2, HIGH);

}

//Pause the robot.
void pause(robot_engine paramEngine){

  //Set pwm signal.
  analogWrite(paramEngine.enPin, 0);

  //Set pin values.
  digitalWrite(paramEngine.in1, LOW);
  digitalWrite(paramEngine.in2, LOW);

}
