#include "ligths.h"

void setup() {  
  Serial.begin(9600);  
  
  //Set leds.
  setup_leds();
}

void loop() {
  front_ligth(true);
  back_ligth(false);    
  delay(500);
  front_ligth(false);
  back_ligth(true);
  delay(500);
}
