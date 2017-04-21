#include"StateHandler.h"
#include<Arduino.h>

StateHandler::StateHandler(){
  delay_ms = 1000;
  curr_time = 0;
  has_sent_curr_pos = true;
  is_waiting_to_move = false;
  x = 0;
  y = 0;
}

bool StateHandler::hasSentCurrPos(){
  return has_sent_curr_pos;
}
void StateHandler::setSentCurrPos(bool val){
  has_sent_curr_pos = val;
}
void StateHandler::setTargetCoordinates(SerialInts * si,TripleMotors * motors){
  if((si->length()>0)&&(si->length()%2 == 0 ) && readyToMove(motors)){
    x = si->getInt();
    y = si->getInt();
    curr_time = millis();
    has_sent_curr_pos = false;
  }
};

int StateHandler::targetX(){
  return x;
};
int StateHandler::targetY(){
  return y;
};
void StateHandler::parseStateRequest(SerialInts *si, TripleMotors * motors){
  char state_code = si->getCharCode();
  switch(state_code){
    case 'm':
      setTargetCoordinates(si, motors);
      break;
    default:
      setTargetCoordinates(si, motors);
      break;
  };
}

bool StateHandler::readyToMove(TripleMotors * motors){
  return (motors->nRunning() == 0) && ((millis() - curr_time) > delay_ms);
}
