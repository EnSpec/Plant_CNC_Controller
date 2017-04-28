#include"TripleMotors.h"
#define XSPEED 200
#define XACCELL 50
// define accelstepper objects with the step functions

TripleMotors::TripleMotors(AccelStepper * s1, AccelStepper * s2, AccelStepper * s3){
  stepper1 = s1;
  stepper2 = s2;
  stepper3 = s3;

}

void TripleMotors::begin(){

  //set speed, acceleration, amount to move for both accelsteppers
  //1 and 2 must be the same
  stepper1->setMaxSpeed(XSPEED);
  stepper1->setAcceleration(XACCELL);

  stepper2->setMaxSpeed(XSPEED);
  stepper2->setAcceleration(XACCELL);

  stepper3->setMaxSpeed(XSPEED);
  stepper3->setAcceleration(XACCELL);

}
void TripleMotors::run(){
  stepper1->run();
  stepper2->run();
  stepper3->run();
}

void TripleMotors::moveToX(int xt){
  stepper1->moveTo(xt);
  stepper2->moveTo(xt);
}

void TripleMotors::moveToY(int yt){
  stepper3->moveTo(yt);
}

int TripleMotors::getX(){
  return stepper1->currentPosition();
}

int TripleMotors::getY(){
  return stepper3->currentPosition();
}

float TripleMotors::getXspeed(){
  return stepper1->speed();
}

float TripleMotors::getYspeed(){
  return stepper3->speed();
}

void TripleMotors::stop(){
  //complete 1 full rotation in the correct direction then stop
  moveToRelativeCoords((int)(2*getXspeed()),
                       (int)(2*getYspeed()));
}
void TripleMotors::moveToCoords(int x, int y){
  moveToX(x);
  moveToY(y);
}

void TripleMotors::moveToRelativeCoords(int x, int y){
  moveToX(getX()+x);
  moveToY(getY()+y);
}


int TripleMotors::nRunning(){
  return(stepper1->distanceToGo() != 0) + (stepper2->distanceToGo() != 0)
                 + (stepper3->distanceToGo() != 0);
}
