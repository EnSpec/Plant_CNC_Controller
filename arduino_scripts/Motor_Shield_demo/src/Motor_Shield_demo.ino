#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include "SerialInts.h"
#include "TripleMotors.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"
//this includes a bunch of setup code for the motors & defines 3 AccelSteppers
#include "MotorShieldSetup.h"

TripleMotors motors(&stepper1,&stepper2,&stepper3);
SerialInts si('\0',32,10000);

bool hasSentCurrPos, readyForNextAction, waitingOnInstruction;
int x, y, target;
unsigned long curr_time,delay_ms;


void setup() {
   //begin serial connection
   Serial.begin(9600);
   Serial.println("Steppers Ready");
   AFMS1.begin();
   AFMS2.begin();
   motors.begin();
   TWBR = ((F_CPU /400000l) - 16) / 2;
   hasSentCurrPos = true;
   readyForNextAction = true;
   x = 0;
   y = 0;
   target = 0;
   curr_time = 0;
   delay_ms = 2000;
}
void set_movement_target(){
  x = si.getInt();
  y = si.getInt();
  curr_time = millis();
  hasSentCurrPos = false;
  target=-2;
}

void finish_movement_target(){
  if(motors.nRunning() == 0){
    target = 0;
    readyForNextAction = true;
  }
}
void set_delay(){
  delay_ms = (unsigned long)si.getInt();
  si.getInt();
  Serial.print(" Delay set to ");
  Serial.print(delay_ms);
  readyForNextAction = true;
}

void set_incremental_movement_target(){
  //move a small amount instantly
  Serial.print("I'm incrementing!");
  x = si.getInt()+motors.getX();
  y = si.getInt()+motors.getY();
  //curr_time = millis() - delay_ms;
  motors.moveToCoords(x, y);
  hasSentCurrPos = false;
  readyForNextAction = true;
}
void loop() {
  motors.run();
  si.scan();

  if((si.length()>0)&&(si.length()%3 == 0 ) && readyForNextAction){
    target = si.getInt();
    readyForNextAction = false;
  }

  if(target == 2) set_delay();
  if(target == 3) set_incremental_movement_target();
  if(target == -1) finish_movement_target();
  if((motors.nRunning() == 0)){
    if(hasSentCurrPos == false){
      hasSentCurrPos = true;
      Serial.print(" Arrived at ");
      Serial.print(motors.getX());
      Serial.print(", ");
      Serial.print(motors.getY());
    }
    if(target == 1) set_movement_target();
  }

  if(((millis() - curr_time) > delay_ms) && target == -2){
    motors.moveToCoords(x, y);
    target= -1;
  }

}
