#include<Arduino.h>
#include"SerialInts.h"

/* Constructor
 */
SerialInts::SerialInts(char sep,int size){
  _sep = sep;
  _value = (int*)malloc(size*sizeof(int));
  _curr_byte = 0;
  _curr_int = 0;
  _in_byte = 0;

};


void SerialInts::start_serial(){
  Serial.begin(9600); //set the baud rate
  Serial.print("Ready");
}
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
      if(_curr_byte>1)_value[_curr_int++] = atoi(_bytes);
      _curr_byte = 0;

    }
  } else {
    handle_output_request(_in_byte);
  }
};

void SerialInts::handle_output_request(char key){
  switch(key){
    case 's':
      print_sum();
      break;
    case 'm':
      print_mean();
      break;
    case 'p':
      print_prod();
      break;
    case 'c':
      clear();
    case 'd':
//      dump_values('\n');
      break;
  }
}

void SerialInts::print_sum(){
  int i,sum = 0;
  for(i=0; i < _curr_int; i ++){
    sum += _value[i];
  }
  Serial.print(sum);
}

void SerialInts::print_mean(){
  int i,sum = 0;
  for(i=0; i < _curr_int; i ++){
    sum += _value[i];
  }
  sum /=_curr_int;
  Serial.print(sum);
}

void SerialInts::print_prod(){
  int i,prod = 1;
  for(i=0; i < _curr_int; i ++){
    prod *= _value[i];
  }
  Serial.print(prod);
}

int SerialInts::length(){
  return _curr_int;
}

int * SerialInts::values(){
  return _value;
}
void SerialInts::clear(){
  _curr_int = 0;
}

SerialInts::~SerialInts(){
free(this->_value);
};
