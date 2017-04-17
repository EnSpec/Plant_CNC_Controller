#include"TripleMotors.h"

// define accelstepper objects with the step functions

TripleMotors::TripleMotors(AccelStepper * s1, AccelStepper * s2, AccelStepper * s3){
  stepper1 = s1;
  stepper2 = s2;
  stepper3 = s3;

}

void TripleMotors::begin(){

  //set speed, acceleration, amount to move for both accelsteppers
  //1 and 2 must be the same
  stepper1->setSpeed(600.0);
  stepper1->setAcceleration(900.0);

  stepper2->setSpeed(600.0);
  stepper2->setAcceleration(90.0);

  stepper3->setSpeed(100.0);
  stepper3->setAcceleration(500.0);

}
void TripleMotors::run(){
  stepper1->run();
  stepper2->run();
}

void TripleMotors::moveToX(int xt){
  stepper1->moveTo(xt);
  stepper2->moveTo(xt);
}

void TripleMotors::moveToY(int yt){
  //stepper3->moveTo(yt);
}

int TripleMotors::getX(){
  return stepper1->currentPosition();
}

int TripleMotors::getY(){
  return stepper3->currentPosition();
}
void TripleMotors::moveToCoords(int x, int y){
  moveToX(x);
  moveToY(y);
}


int TripleMotors::nRunning(){
  return(stepper1->distanceToGo() != 0);// + (ystepper.distanceToGo() != 0);
}
