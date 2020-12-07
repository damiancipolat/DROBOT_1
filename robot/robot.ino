#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include "pins.h"
#include "engine.h"
#include "ligths.h"
#include "compass.h"
#include "keys.h"

//Screeen.
LiquidCrystal_I2C lcd(0x27,12,6);

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

void clear_screen(int line){               
  lcd.setCursor(0,line);
  for(int n = 0; n < 20; n++)
   lcd.print(" ");
}

int command=0;
float desired = 180;
float angulo=0;
int diff=0;
String label;

void draw_screen(int angle, int diff,String label, int desired, int command){
  //clear_screen(0);
  //clear_screen(1);
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("Acim:"+(String)angle+"  "+label+" S:"+(String)command); 
  lcd.setCursor (0,1);
  lcd.print("Diff:"+(String)diff+"  "+"D:"+(String)desired);
  lcd.noDisplay();
}

//Arduino events.
void setup(){    
  Serial.begin(9600);
  Serial.println("Listo!");
  enableCompass();
  irrecv.enableIRIn();
  lcd.init();
  lcd.backlight();
  lcd.clear();  
}

void turn_left_angle(int acimut, int desired){
  diff = acimut-desired;
  if ((acimut>=desired)&&(diff>=0)){
    turnLeft(motorA,motorB);
    label="X";
  }else{
    label="N";
    pause(motorA);
    pause(motorB);
  }
}

void turn_rigth_angle(int acimut, int desired){
  diff = desired-acimut;
  if ((acimut<=desired)&&(diff>=0)){
    turnRigth(motorA,motorB);
    label="X";
  }else{
    label="N";
    pause(motorA);
    pause(motorB);
  }
}

int state = 0;

void loop() {
  
  //Get the heading angle.
  angulo = getAcimut();
  //Serial.println("Acimut:"+(String)angulo+"°");  
  
  //Get IR data.
  int command = getIrData();
  Serial.println("Key:"+(String)command+"State:"+(String)state);

  if (command==LEFT){
    state=1;
    desired=45;
  }
  
  if (command==RIGTH){
    state=2;
    desired=180;
  }

  if (command==UP){
    state=3;
  }  

  if (command==DOWN){
    state=4;
  }  

  if (command==OK){
    state=5;
  }    

  if (state==1)
    turn_left_angle(angulo,desired);

  if (state==2)
    turn_rigth_angle(angulo,desired);

  if (state==3){
    forward(motorA);  
    forward(motorB);
  }

  if (state==4){
    reverse(motorA);  
    reverse(motorB);
  } 
    
  if (state==5){
    pause(motorA);  
    pause(motorB);
  }
  
  //Draw values.
  draw_screen(angulo,diff,label,desired,state);

/*
  //Forward
  if (command==UP){
    forward(motorA);
    forward(motorB);
    desired=angulo;
    drive_robot_forward(led_front,led_back,motorA,motorB,desired,angulo,5);    
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
  }*/
  

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
