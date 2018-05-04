#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include "SerialInts.h"
#include "TripleMotors.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"
//this includes a bunch of setup code for the motors & defines 3 AccelSteppers
#include "gShieldSetup.h"
#include "TargetValues.h"
TripleMotors motors(&stepper1,&stepper2,&stepper3);
SerialInts si('\0',32,10000);
//Y RANGE: 0 -> 57436 (150 cm)
//X RANGE: 0 -> 53571 (140 cm)
//~~ 382.8 steps per cm
bool hasSentCurrPos, readyForNextAction, waitingOnInstruction;
long x, y, z;
unsigned long curr_time,delay_ms;
/* Target deterines the target action for the Motorcontroller
 * Negative targets are used internally, while positive targets can be sent
 * by the user.
 * Currently reserved targets:
 * 0 : no action pending
 * 1 : Set target for move after delay
 *   -2 : Waiting until delay is over to move
 *   -1 : Moving after delay
 * 2 : Set delay between moves
 * 3 : Move relative to current position without delay
 * -3 : Slow down and stop
 */
int target;


void setup() {
   //begin serial connection
   Serial.begin(9600);
   Serial.println("Steppers Ready");
   setupGShieldPins();
   motors.begin();
   TWBR = ((F_CPU /400000l) - 16) / 2;
   hasSentCurrPos = true;
   readyForNextAction = true;
   x = 0;
   y = 0;
   z = 0;
   target = ACTION_COMPLETE;
   curr_time = 0;
   delay_ms = 300;
}

void set_movement_target(){
  x = si.getInt();
  y = si.getInt();
  curr_time = millis();
  target = WAITING_TO_MOVE;
}

void set_z_movement_target(){
  z = si.getInt();
  //one dummy
  si.getInt();
  curr_time = millis();
  target = WAITING_TO_MOVE;
}

void move_if_ready(){
    if(((millis() - curr_time) > delay_ms)){
      motors.moveToCoords(x, y);
      motors.moveToZ(z);
      hasSentCurrPos = false;
      target= MOVING;
    }
}

void finish_movement_target(){
  if(motors.nRunning() == 0){
    target = ACTION_COMPLETE;
    readyForNextAction = true;
  }
}

void halt_motors(){
  si.clear();
  motors.stop();
}
void set_delay(){
  delay_ms = (unsigned long)si.getInt();
  si.getInt();
  Serial.print(" Delay set to ");
  Serial.print(delay_ms);
  readyForNextAction = true;
  target = ACTION_COMPLETE;
}

void set_incremental_movement_target(){
  //move a small amount instantly
  x = si.getInt();
  y = si.getInt();
  motors.moveToRelativeCoords(x, y);
  hasSentCurrPos = false;
  readyForNextAction = true;
  target = ACTION_COMPLETE;
}


void send_current_position(){
  if(hasSentCurrPos == false){
    hasSentCurrPos = true;
    Serial.print(" Arrived at ");
    Serial.print(motors.getX());
    Serial.print(", ");
    Serial.print(motors.getY());
  }
}
void loop() {

  //Step the motors if they need to be steppd, and read a character if there's
  //one to be read
  motors.run();
  si.scan();

  if((si.length()>0)&&(si.length()%3 == 0) && readyForNextAction){
    target = si.getInt();
    readyForNextAction = false;
  }
  if(si.getCharCode() == 's') halt_motors();
  if(target == SET_DELAY) set_delay();
  if(target == MOVE_RELATIVE) set_incremental_movement_target();
  if(target == MOVING) finish_movement_target();
  if(target == WAITING_TO_MOVE) move_if_ready();
  if((motors.nRunning() == 0)){
    send_current_position();
    if(target == SET_MOVEMENT_TARGET) set_movement_target();
    if(target == SET_Z_TARGET) set_z_movement_target();
  }

}
