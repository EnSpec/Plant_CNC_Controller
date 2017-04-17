#include <Arduino.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include "SerialInts.h"
#include "TripleMotors.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"

//declare motor shield and steppers
// I can't for the life of me figure out how to declare these elsewhere
Adafruit_MotorShield AFMS1 = Adafruit_MotorShield(0x60);
Adafruit_StepperMotor *motor1 = AFMS1.getStepper(200, 2);
Adafruit_StepperMotor *motor2 = AFMS1.getStepper(200, 1);

Adafruit_MotorShield AFMS2 = Adafruit_MotorShield(0x61);
Adafruit_StepperMotor *motor3 = AFMS2.getStepper(200, 2);

//declare motor functions
void forwardstep1() {
  motor1->onestep(FORWARD, SINGLE);
}
void backwardstep1() {
  motor1->onestep(BACKWARD, SINGLE);
}
void forwardstep2() {
  motor2->onestep(FORWARD, SINGLE);
}
void backwardstep2() {
  motor2->onestep(BACKWARD, SINGLE);
}

void forwardstep3() {
  motor3->onestep(FORWARD, SINGLE);
}
void backwardstep3() {
  motor3->onestep(BACKWARD, SINGLE);
}


// define accelstepper objects with the step functions
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);
AccelStepper stepper3(forwardstep3, backwardstep3);
TripleMotors motors(&stepper1,&stepper2,&stepper3);
SerialInts si('\0',32);

bool hasSentCurrPos;
void setup() {
   //begin serial connection
   Serial.begin(9600);
   Serial.println("Stepper test!");
   AFMS1.begin();
   AFMS2.begin();
   motors.begin();
   hasSentCurrPos = false;

}

void loop() {
  motors.run();
  si.scan();
  if((motors.nRunning() == 0)){
    if(hasSentCurrPos == false){
      hasSentCurrPos = true;
      Serial.print("Arrived at ");
      Serial.print(motors.getX());
      Serial.print(", ");
      Serial.print(motors.getY());

    }
    if((si.length()>0)&&(si.length()%2 == 0 )){
      int x = si.getInt();
      int y = si.getInt();
      motors.moveToCoords(x, y);
      hasSentCurrPos = false;
    }
  }

}
