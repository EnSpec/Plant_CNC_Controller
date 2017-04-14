#ifndef LedStepper_h
#include<Arduino.h>

class LedStepper{
  public:
    LedStepper(unsigned long speed);
    void setSpeed(unsigned long speed);
    void setup();
    void run();
    void xpos();
    void ypos();
    void setTarget(int target);
  private:
    unsigned long _speed;
    int _curr_step;
    int _target;
    int _ledstate;

    unsigned long _prev_time;
};
#endif
