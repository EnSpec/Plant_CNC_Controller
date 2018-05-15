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
    long nRunning();
    void moveToX(long xt);
    void moveToY(long yt);
    void moveToZ(long zt);
    long getX();
    long getY();
    long getZ();
    float getXspeed();
    float getYspeed();
    void moveToCoords(long x, long y);
    void moveToRelativeCoords(long x, long y);
    void moveToRelativeZCoords(long z);
    void setMaxSpeed(int speed);
  private:
    void updateSpeeds(long x, long y);
    AccelStepper * stepper1;
    AccelStepper * stepper2;
    AccelStepper * stepper3;
    int xspeed;
};
#endif
