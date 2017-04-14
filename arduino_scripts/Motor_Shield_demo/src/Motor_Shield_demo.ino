#include <Arduino.h>

#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Wire.h>
#include <SerialInts.h>
#include "TripleMotors.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"

//declare serial port reader
SerialInts si('\0',32);
void setup() {
   //begin serial connection
   Serial.begin(9600);
   Serial.println("Fast! Stepper test!");
   TripleMotors motors = TripleMotors(600,900,100,500);
}



void loop() {
   //motors.run();
   si.scan();
   if(si.length() == 2){
     //motors.moveToX(si.values()[0]);
     //motors.moveToY(si.values()[1]);
     si.clear();
   }
}
