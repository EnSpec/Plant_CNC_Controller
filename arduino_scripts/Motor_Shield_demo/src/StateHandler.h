#ifndef StateHandler_h
#include<Arduino.h>
#include"SerialInts.h"
#include"TripleMotors.h"
class StateHandler{
  public:
    StateHandler();
    bool readyToMove(TripleMotors * motors);
    int targetX();
    int targetY();
    void parseStateRequest(SerialInts * si,TripleMotors * motors);
    bool hasSentCurrPos();
    void setSentCurrPos(bool val);
  private:
    unsigned long delay_ms,curr_time;
    int x,y;
    bool has_sent_curr_pos,is_waiting_to_move;
    void setTargetCoordinates(SerialInts * si,TripleMotors * motors);
};

#endif
