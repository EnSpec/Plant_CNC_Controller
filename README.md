## ARDUPY GUI
Python serial interface with arduino. The project contains 2 components:
a C++ project designed to be compiled and run on Arduino
(located at `arduino_scripts/Motor_Shield_Controller`), and a python-based
GUI to interface with the compiled Arduino code
(located at `ardupy_gui/motor_text_gui`)

### C++ Part
This program reads integers as ASCII from the serial port, then moves
stepper motors along x/y axes using an Adafruit MotorShield or gShield
(Final hardware specs are not yet determined)
#### Serial Instruction set
Instructions are formed from 3 null zero (indicated by`\0`) - separated
integers.
`0 \0 X \0 Y \0`: Move to `X,Y` 
`1 \0 MS \0 0 \0`: Wait `MS` milliseconds after each subsequent move  

