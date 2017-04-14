#include<Arduino.h>
#include"LedStepper.h"

LedStepper::LedStepper(unsigned long speed){
  _speed = speed;
  _curr_step = 0;
  _ledstate = LOW;
  _prev_time = 0;
}

void LedStepper::setup(){
  pinMode(LED_BUILTIN,OUTPUT);
}

void LedStepper::setTarget(int target){
  _target = 2*target; //it takes an ON and an OFF for a single step
}

void LedStepper::run(){
  if(_curr_step == _target) return;
  unsigned long curr_time = millis();
  if(curr_time - _prev_time > _speed){
    _curr_step +=(_curr_step >_target)?-1:1;
    _prev_time = curr_time;
    _ledstate = (_ledstate == LOW)?HIGH:LOW;
    digitalWrite(LED_BUILTIN,_ledstate);
  }
}
