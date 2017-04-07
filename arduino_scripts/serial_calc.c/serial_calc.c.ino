#include<stdlib.h>
#include<string.h>
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); //set the baud rate
  Serial.print("Ready");
}

char numstr[64];
float nums[32];
char i = 0;
int j = 0;

float compute_mean(){
  int k;
  float sum=0;
  for(k = 0; k < j; k++){
    sum+=nums[k];
  }
  return sum/j;
}

void parse_byte(char inByte){
    if((!inByte)||inByte=='.'||((inByte >= '0')&&(inByte <='9'))){
      numstr[i++] = inByte;
      if(!inByte){
        digitalWrite(LED_BUILTIN, LOW);
        if(i>1) 
          nums[j++] = atof(numstr);
        i=0;
        
      }
    } else {
      switch(inByte){
        case 'm':
          Serial.print(compute_mean());
          break;
        case 'r':
          j = 0;
          break;  
      };
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  char inByte = ' ';
  if(Serial.available()){
    digitalWrite(LED_BUILTIN, HIGH);    
    inByte = Serial.read();
    parse_byte(inByte);
  }
}
