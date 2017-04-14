#include <Arduino.h>
#include<stdlib.h>
#include<string.h>
#include"SerialInts.h"
#include"LedStepper.h"

SerialInts si('\0',32);
LedStepper ls(250);
void setup() {
  si.start_serial();
  ls.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  si.scan();
  ls.run();
  if(si.length() > 0){
    ls.setTarget(si.values()[0]);
    si.clear();
  }
}
