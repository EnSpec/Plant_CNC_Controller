#include<Arduino.h>
#include"SerialInts.h"
#include"QueueList.h"
/* Constructor
 */
SerialInts::SerialInts(char sep,int size){
  _sep = sep;
  _values = QueueList<int>();
  _curr_byte = 0;
  _curr_int = 0;
  _in_byte = 0;

};

/* Call this every cycle of loop
* Reads a character in from Serial if one exists
*/
void SerialInts::scan(){
  if(Serial.available()){
    _in_byte = Serial.read();
    parse_byte();
  }
};

void SerialInts::parse_byte(){
  if((_in_byte==_sep)||_in_byte=='.'||((_in_byte >= '0')&&(_in_byte <='9'))){
    _bytes[_curr_byte++] = _in_byte;
    if(!_in_byte){
      //FIXME this doesn't work if _sep .NE. '\0'
      if(_curr_byte>1)_values.push(atoi(_bytes));
      _curr_byte = 0;

    }
  } else {
    handle_output_request(_in_byte);
  }
};

void SerialInts::handle_output_request(char key){
  switch(key){
    case 'c':
      clear();
    case 'd':
//      dump_values('\n');
      break;
  }
}



int SerialInts::length(){
  return _values.count();
}

int SerialInts::getInt(){
  return _values.pop();
}
void SerialInts::clear(){
  _curr_int = 0;
}

SerialInts::~SerialInts(){

};
