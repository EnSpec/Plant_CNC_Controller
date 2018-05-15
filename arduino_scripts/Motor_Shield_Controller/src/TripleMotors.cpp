#include"TripleMotors.h"
#define XSPEED 1500
#define XACCELL 1000
// define accelstepper objects with the step functions

TripleMotors::TripleMotors(AccelStepper * s1, AccelStepper * s2, AccelStepper * s3){
  stepper1 = s1;
  stepper2 = s2;
  stepper3 = s3;
  xspeed = XSPEED;
}

void TripleMotors::begin(){

  //set speed, acceleration, amount to move for both accelsteppers
  //1 and 2 must be the same
  stepper1->setMaxSpeed(xspeed);
  stepper1->setAcceleration(XACCELL);

  stepper2->setMaxSpeed(xspeed);
  stepper2->setAcceleration(XACCELL);

  stepper3->setMaxSpeed(xspeed);
  stepper3->setAcceleration(XACCELL);

}
void TripleMotors::run(){
  stepper1->run();
  stepper2->run();
  stepper3->run();
}

void TripleMotors::moveToX(long xt){
  stepper1->moveTo(xt);
}

void TripleMotors::moveToY(long yt){
  stepper3->moveTo(yt);
}

void TripleMotors::moveToZ(long zt){
  stepper2->moveTo(zt);
}

long TripleMotors::getX(){
  return stepper1->currentPosition();
}

long TripleMotors::getY(){
  return stepper3->currentPosition();
}

long TripleMotors::getZ(){
  return stepper2->currentPosition();
}

float TripleMotors::getXspeed(){
  return stepper1->speed();
}

float TripleMotors::getYspeed(){
  return stepper3->speed();
}


void TripleMotors::stop(){
  //complete 1 full rotation in the correct direction then stop
  moveToRelativeCoords((long)(2*getXspeed()),
                       (long)(2*getYspeed()));
}


void TripleMotors::setMaxSpeed(int speed){
  xspeed = speed;
}

void TripleMotors::moveToCoords(long x, long y){
  updateSpeeds(x,y);
  moveToX(x);
  moveToY(y);
}

void TripleMotors::updateSpeeds(long x, long y){
  long dx = getX() - x;
  long dy = getY() - y;
  if(dx == 0){
    stepper1->setMaxSpeed(xspeed);
    stepper2->setMaxSpeed(xspeed);
    return;
  }
  if(dy == 0){
    stepper3->setMaxSpeed(xspeed);
    return;
  }
  float spd_ratio = (float)dx/(float)dy;
  if(spd_ratio > 1){
    stepper1->setMaxSpeed(xspeed);
    stepper2->setMaxSpeed(xspeed);
    stepper3->setMaxSpeed(xspeed/spd_ratio);
  } else {
    stepper1->setMaxSpeed(xspeed*spd_ratio);
    stepper2->setMaxSpeed(xspeed*spd_ratio);
    stepper3->setMaxSpeed(xspeed);
  }

}
void TripleMotors::moveToRelativeCoords(long x, long y){
  stepper1->setMaxSpeed(xspeed);
  stepper2->setMaxSpeed(xspeed);
  stepper3->setMaxSpeed(xspeed);
  moveToX(getX()+x);
  moveToY(getY()+y);
}
void TripleMotors::moveToRelativeZCoords(long z){
  stepper1->setMaxSpeed(xspeed);
  stepper2->setMaxSpeed(xspeed);
  stepper3->setMaxSpeed(xspeed);
  moveToZ(getZ()+z);
}


long TripleMotors::nRunning(){
  return(stepper1->distanceToGo() != 0) + (stepper2->distanceToGo() != 0)
                 + (stepper3->distanceToGo() != 0);
}
