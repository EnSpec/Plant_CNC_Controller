#include"TripleMotors.h"

Adafruit_MotorShield TripleMotors::AFMS1 = Adafruit_MotorShield(0x60);
Adafruit_MotorShield TripleMotors::AFMS2 = Adafruit_MotorShield(0x61);
Adafruit_StepperMotor * TripleMotors::motor1 = AFMS1.getStepper(200,2);
Adafruit_StepperMotor * TripleMotors::motor2 = AFMS1.getStepper(200,1);
Adafruit_StepperMotor * TripleMotors::motor3 = AFMS2.getStepper(200,2);

TripleMotors::TripleMotors(int xspeed, int xaccel, int yspeed, int yaccel){
  xstepper1 = AccelStepper(forwardstep1,backwardstep1);
  xstepper2 = AccelStepper(forwardstep2,backwardstep2);
  ystepper = AccelStepper(forwardstep3,backwardstep3);

  AFMS1.begin();
  AFMS2.begin();

  xstepper1.setSpeed(600.0);
  xstepper1.setAcceleration(900.0);
  xstepper2.setSpeed(600.0);
  xstepper2.setAcceleration(900.0);
  ystepper.setSpeed(100.0);
  ystepper.setAcceleration(500.0);
}

void TripleMotors::run(){
  xstepper1.run();
  xstepper2.run();
  ystepper.run();
}

void TripleMotors::moveToX(int xt){
  xstepper1.moveTo(xt);
  xstepper2.moveTo(xt);
}

void TripleMotors::moveToY(int yt){
  ystepper.moveTo(yt);
}

int TripleMotors::nRunning(){
  return(xstepper1.distanceToGo() != 0) + (ystepper.distanceToGo() != 0);
}

void TripleMotors::forwardstep1() {
  motor1->onestep(FORWARD, SINGLE);
}
void TripleMotors::backwardstep1() {
  motor1->onestep(BACKWARD, SINGLE);
}
void TripleMotors::forwardstep2() {
  motor2->onestep(FORWARD, SINGLE);
}
void TripleMotors::backwardstep2() {
  motor2->onestep(BACKWARD, SINGLE);
}
void TripleMotors::forwardstep3() {
  motor3->onestep(FORWARD, SINGLE);
}
void TripleMotors::backwardstep3() {
  motor3->onestep(BACKWARD, SINGLE);
}
