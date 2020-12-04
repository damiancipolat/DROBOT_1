#include <Arduino.h>
#include "engine.h"

//Speeds.
int forwardSpeed = 250;
int turnSpeed = 170;

//Create an engine data type.
engine createEngine(int pwmPin,int in1, int in2){

  //Define values.
  engine newEngine;
  newEngine.enPin = pwmPin;
  newEngine.in1= in1;
  newEngine.in2= in2;

  //Bind pins.
  pinMode(pwmPin, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  return newEngine;
    
}

//Move the motor forward.
void forward(engine paramEngine){

  //Set pwm signal.
  analogWrite(paramEngine.enPin, forwardSpeed);

  //Set pin values.
  digitalWrite(paramEngine.in1, HIGH);
  digitalWrite(paramEngine.in2, LOW);

}

//Move the motor in reverse.
void reverse(engine paramEngine){

  //Set pwm signal.
  analogWrite(paramEngine.enPin, forwardSpeed);

  //Set pin values.
  digitalWrite(paramEngine.in1, LOW);
  digitalWrite(paramEngine.in2, HIGH);

}

//Pause the robot.
void pause(engine paramEngine){

  //Set pwm signal.
  analogWrite(paramEngine.enPin, 0);

  //Set pin values.
  digitalWrite(paramEngine.in1, LOW);
  digitalWrite(paramEngine.in2, LOW);

}
