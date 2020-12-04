#include <Arduino.h>
#include "engine.h"
#include "compass.h"

void drive(engine motorA, engine motorB, float desired_heading, float heading,int desviation){
  
  if (abs(desired_heading-heading)<=desviation){
    forward(motorA);
    forward(motorB);
  } else {
      
    int x = (desired_heading - 359);
    int y = (heading - (x));
    int z = (y - 360);
                     
    if ((z <= 180) && (z >= 0)){
      turnLeft(motorA,motorB);
    }else{
      turnRigth(motorA,motorB);
   }
 }
}
