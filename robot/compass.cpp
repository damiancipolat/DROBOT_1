#include <Wire.h>
#include <MechaQMC5883.h>
#include "compass.h"

MechaQMC5883 qmc;

void enableCompass(){
  Wire.begin(A1);
  qmc.init();
}

float getAcimut(){
  int x,y,z;
  float acimut,geografico;
  float declinacion = -9.13;
  qmc.read(&x,&y,&z,&acimut);
  geografico = acimut + declinacion;
  
  if(geografico < 0)
    geografico = geografico + 360;

  return geografico;
}
