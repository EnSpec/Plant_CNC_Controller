#ifndef TripleMotors_h

#include<Arduino.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


class TripleMotors{
  public:
    TripleMotors(int xspeed, int xaccel, int yspeed, int yaccel);
    void run();
    int nRunning();
    void moveToX(int xt);
    void moveToY(int yt);
    void moveToCoords(int x, int y);
  private:
    //all these declarations need to be static so that they can be passed into
    //AccelStepper's constructor properly
    static Adafruit_MotorShield AFMS1;
    static Adafruit_MotorShield AFMS2;
    static Adafruit_StepperMotor *motor1;
    static Adafruit_StepperMotor *motor2;
    static Adafruit_StepperMotor *motor3;
    static void forwardstep1();
    static void backwardstep1();
    static void forwardstep2();
    static void backwardstep2();
    static void forwardstep3();
    static void backwardstep3();

    AccelStepper xstepper1;
    AccelStepper xstepper2;
    AccelStepper ystepper;

};
#endif
