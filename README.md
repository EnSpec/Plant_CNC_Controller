# README
This project contains software to control a 3-axis CNC Machine.
It consists of two components: A C++ project designed to be compiled and 
run on Arduino (located at `arduino_scripts/Motor_Shield_Controller`),
and a Python 3 GUI to interface with the Arduino from a desktop
(located at `ardupy_gui/motor_text_gui`). The GUI can be run from either 
Linux or Windows, but has only been tested extensively on Linux.

## Arduino Software
This program reads integers as ASCII from the serial port, then moves
stepper motors along the x/y/z axes using a gShield.

#### Program Structure
The following steps are perfomed during each loop() of the program:  
1. Read a byte from serial. If it froms a complete integer, push that 
integer to a stack (Handled by `SerialInts.cpp`)  
2. Step motors 1 step towards their destination, if needed (handled by
`TripleMotors.cpp`)  
3. Update the current instruction if  a complete instruction 
has been passed (i.e. 3 complete ascii integers have been passed in). 
4. Perform an action based on the current instruction (see the next
section for details)
    * Some instructions (eg Move) create temporary states, these are not
    currently documented  
#### Serial Communication
Instructions to be sent over serial are formed 
from 3 null zero (indicated by `\0`) - separated ASCII integers.  
`1 \0 X \0 Y \0`: Move to `X,Y`   
`2 \0 MS \0 0 \0`: Wait `MS` milliseconds after each subsequent move   
`3 \0 dX \0 dY \0`: Move `dX,dY` relative to current position  
(don't wait)  
`4 \0 Z \0 0 \0`: Move vertical axis to `Z`   
`5 \0 dZ \0 0 \0`: Move vertical `dZ` relative to current position  
`6 \0 Spd \0 0 \0`: Set stepper speed to Spd cm/s.  
Messages returned by the program over serial:  
`Steppers Ready.` at the beginning of the program.   
`Arrived at X, Y` whenever both axes arrive at a new destination 
(such that they're both stopped)   
`Delay set to MS` whenever a new delay is set  

### Requirements
All required packages for the Arduino software are contained within the repository.

### Installation
The progam should be ready to compile and upload in
the Arduino IDE. Instructions can be found
[here](https://www.arduino.cc/en/Main/Software#download).

## Desktop Software
This program provides a graphical interface for control of the CNC machine. 

### Requirements
The graphical interface depends on two external Python packages, both of which
can be obtained from PyPI:
1. [PySerial](https://pypi.org/project/pyserial/)
2. [CefPython](https://pypi.org/project/cefpython3/)

### Installation
1. Download and install the latest version of 
[Python 3](https://www.python.org/), or install it from a package manager.
2. Clone this package, or download it as a zip and extract it.
3. Run the commands `pip install cefpython3` and `pip install pySerial`
from a command prompt.
4. `cd` into this package's directory from the command prompt.
5. Run the command `python setup.py install`. 
6. To invoke the GUI, run the `run_ardupy.cmd` batch file, or the
`run_ardupy.sh` shell script.
