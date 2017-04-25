#ifndef TripleMotors_h
#define TripleMotors_h
#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


class TripleMotors{
  public:
    TripleMotors(AccelStepper * s1, AccelStepper * s2, AccelStepper * s3);
    void begin();
    void run();
    void stop();
    int nRunning();
    void moveToX(int xt);
    void moveToY(int yt);
    int getX();
    int getY();
    void moveToCoords(int x, int y);
    void moveToRelativeCoords(int x, int y);
  private:
    AccelStepper * stepper1;
    AccelStepper * stepper2;
    AccelStepper * stepper3;
};
#endif
