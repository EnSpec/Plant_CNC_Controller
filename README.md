# ARDUPY GUI
Python serial interface with arduino. The project contains 2 components:
a C++ project designed to be compiled and run on Arduino
(located at `arduino_scripts/Motor_Shield_Controller`), and a python-based
GUI to interface with the compiled Arduino code
(located at `ardupy_gui/motor_text_gui`)

## C++ Part
This program reads integers as ASCII from the serial port, then moves
stepper motors along x/y axes using an Adafruit MotorShield or gShield
(Final hardware specs are not yet determined)



#### Program Structure
The following steps are perfomed during each loop() of the program:  
1. Read a byte from serial. If it froms a complete integer, push that integer to a stack
(Handled by `SerialInts.cpp`)
#### Serial Communication
Instructions to be sent over serial are formed 
from 3 null zero (indicated by `\0`) - separated ASCII integers.
`1 \0 X \0 Y \0`: Move to `X,Y`   
`2 \0 MS \0 0 \0`: Wait `MS` milliseconds after each subsequent move   
`3 \0 dX \0 dY \0`: Move `dX,dY` relative to current position  
(don't wait)  
Messages returned by the program over serial:
`Steppers Ready.` at the beginning of the program.   
`Arrived at X, Y` whenever both axes arrive at a new destination 
(such that they're both stopped)   
`Delay set to MS` whenever a new delay is set  
