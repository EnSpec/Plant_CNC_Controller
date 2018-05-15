#include<Arduino.h>
#include"SerialInts.h"
#include"QueueList.h"
/* Constructor
 */
SerialInts::SerialInts(char sep,long size, unsigned long wait){
  _sep = sep;
  _wait = wait;
  _values = QueueList<long>();
  _curr_byte = 0;
  _curr_int = 0;
  _in_byte = 0;
  _got_byte = false;
  _char_code = '\0';
};

/* Call this every cycle of loop
* Reads a character in from Serial if one exists
*/
void SerialInts::scan(){
  if(Serial.available()){
    _got_byte = true;
    _in_byte = Serial.read();
    parse_byte();
  } else if((!_got_byte) && (_wait) && millis() > _wait){
    _wait = 0;
    //"read in" some example values if no input is detected after a certain time
    Serial.print("Input timed out. Starting demo.");
    demo();
  }
};

void SerialInts::parse_byte(){
  if((_in_byte==_sep)||_in_byte=='.'||_in_byte=='-' ||
                ((_in_byte >= '0')&&(_in_byte <='9'))){
    _bytes[_curr_byte++] = _in_byte;
    if(!_in_byte){
      //FIXME this doesn't work if _sep .NE. '\0'
      if(_curr_byte>1)_values.push(atol(_bytes));
      _curr_byte = 0;

    }
  } else {
    handle_output_request(_in_byte);
  }
};

void SerialInts::handle_output_request(char key){
  //'n' is reserved for a no-op
  if(key == 'n') return;
  else _char_code = key;
}

char SerialInts::getCharCode(){
  return _char_code;
}

long SerialInts::length(){
  return _values.count();
}

long SerialInts::getInt(){
  return _values.pop();
}
void SerialInts::clear(){
  //empty queue of stored values
  while(_values.count()) _values.pop();
  //reset _char_code
  _char_code = '\0';
}
void SerialInts::demo(){
  long example_length = 15;
  long example_values[] = {1,800,0, /**/ 1,0,0, /**/ 2,0,0,/**/ 1,800,0, /**/ 1,0,0};
  //long example_values[] = {3,200,0, /**/ 3,200,0, /**/ 3,200,0, /**/ 3,200,0, /**/ 3,200,0};
  long i;
  for(i = 0; i < example_length; _values.push(example_values[i++]));
}
SerialInts::~SerialInts(){

};
