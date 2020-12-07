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

//Turn left.
void turnLeft(engine paramEngineA, engine paramEngineB){

  //MOTOR A - Set pwm signal.
  analogWrite(paramEngineA.enPin, turnSpeed);

  //Set pin values.
  digitalWrite(paramEngineA.in1, LOW);
  digitalWrite(paramEngineA.in2, HIGH);

  //MOTOR B - Set pwm signal.
  analogWrite(paramEngineB.enPin, turnSpeed);

  //Set pin values.
  digitalWrite(paramEngineB.in1, HIGH);
  digitalWrite(paramEngineB.in2, LOW);

}

//Turn rigth.
void turnRigth(engine paramEngineA, engine paramEngineB){

  //MOTOR A - Set pwm signal.
  analogWrite(paramEngineA.enPin, turnSpeed);

  //Set pin values.
  digitalWrite(paramEngineA.in1, HIGH);
  digitalWrite(paramEngineA.in2, LOW);

  //MOTOR B - Set pwm signal.
  analogWrite(paramEngineB.enPin, turnSpeed);

  //Set pin values.
  digitalWrite(paramEngineB.in1, LOW);
  digitalWrite(paramEngineB.in2, HIGH);

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
  //digitalWrite(paramEngine.in1, LOW);
  //digitalWrite(paramEngine.in2, LOW);

}
