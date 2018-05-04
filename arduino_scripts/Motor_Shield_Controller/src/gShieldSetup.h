#ifndef gShieldSetup_h
#define gShieldSetup_h
#include <Arduino.h>
#include <AccelStepper.h>

#define ENABLE 8
#define XDIR 5
#define XSTEP 2
#define YDIR 6
#define YSTEP 3
#define ZDIR 7
#define ZSTEP 4


void setupGShieldPins(){
  //stepper enable pin
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);
  //stepper1 (x-axis) direction pin
  pinMode(XDIR, OUTPUT);
  digitalWrite(XDIR, LOW);
  //stepper1 step pin
  pinMode(XSTEP, OUTPUT);
  digitalWrite(XSTEP, LOW);

  //stepper2 (z-axis, unused) direction pin
  pinMode(ZDIR, OUTPUT);
  digitalWrite(ZDIR, LOW);
  //stepper2 step pin
  pinMode(ZSTEP, OUTPUT);
  digitalWrite(ZSTEP, LOW);

  //stepper3 (y-axis) direction pin
  pinMode(YDIR, OUTPUT);
  digitalWrite(YDIR, LOW);
  //stepper3 step pin
  pinMode(YSTEP, OUTPUT);
  digitalWrite(YSTEP, LOW);
};

//Define an accelstepper for each axis based on pins
AccelStepper stepper1(AccelStepper::DRIVER,XSTEP,XDIR);
AccelStepper stepper2(AccelStepper::DRIVER,ZSTEP,ZDIR);
AccelStepper stepper3(AccelStepper::DRIVER,YSTEP,YDIR);
#endif
