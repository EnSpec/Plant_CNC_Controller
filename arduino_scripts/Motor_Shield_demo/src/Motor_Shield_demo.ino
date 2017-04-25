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
int x, y;
unsigned long curr_time,delay_ms;
/* Target deterines the target action for the Motorcontroller
 * Negative targets are used internally, while positive targets can be sent
 * by the user.
 * Currently reserved targets:
 * 0 - no action pending
 * 1 - Set target for move after delay
 *   -2 - Waiting until delay is over to move
 *   -1 - Moving after delay
 * 2 - Set delay between moves
 * 3 - Move relative to current position without delay
 * -3 - Slow down and stop
 */
int target;


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
  target=0;
}

void set_incremental_movement_target(){
  //move a small amount instantly
  x = si.getInt();
  y = si.getInt();
  motors.moveToRelativeCoords(x, y);
  hasSentCurrPos = false;
  readyForNextAction = true;
  target=0;
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
