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
Messages returned by the program over serial:  
`Steppers Ready.` at the beginning of the program.   
`Arrived at X, Y` whenever both axes arrive at a new destination 
(such that they're both stopped)   
`Delay set to MS` whenever a new delay is set  

### Installation
The progam should be ready to compile and upload in either
the Arduino IDE or PlatformIO. Instructions for using these tools
can be found here:  
* [Arduino IDE](https://www.arduino.cc/en/Main/Software#download)
* [PlatformIO]

## Python Part



#### Installation
##### Windows  
1. Download and install the latest version of 
[Python 3](https://www.python.org/) (Not Python 2!!)  
Make sure to check the option "Add Python 3 to path" in the installer.
2. Download this package as a zip file from
[github](https://github.com/westphallm1/ardupy_gui), 
then extract to a directory of your choice.
3. Open a command prompt and run the commands `pip install cefpython3`
and `pip install pySerial`
4. `cd` into this package's directory from the command prompt.
5. Run the command `python setup.py install` 
6. To invoke the GUI, run the `run_ardupy.cmd` batch file either from the Windows explorer or from the command line
