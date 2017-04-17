
#ifndef SerialInts_h

#include<Arduino.h>
#include<QueueList.h>

class SerialInts {
  public:
    SerialInts(char sep, int size);
    ~SerialInts();
    void start_serial();
    void scan();
    void print_values();
    int length();
    int getInt();
    void dump_values(char sep);
    void print_sum();
    void print_mean();
    void print_prod();
    void clear();
  private:
    char _bytes[100];
    QueueList<int> _values;
    int _curr_byte,_curr_int;
    char _sep,_in_byte;
    void parse_byte();
    void handle_output_request(char key);


};

#endif
