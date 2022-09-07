#include <Arduino.h>
#include "State_button.hpp"

StateButton sb1 {0,2}; //button on pin 0 
StateButton sb2 {1,2}; //button on pin 1 
StateButton sb3 {6,2}; //button on pin 6
StateButton sb4 {7,2}; //button on pin 7

const int loops = 4; 
LoopElement* loop_call[loops]; 

short last_state1 = 2; 
short last_state2 = 2; 
short last_state3 = 2; 
short last_state4 = 2; 

void setup() {
  // put your setup code here, to run once:

  loop_call[0] = &sb1; 
  loop_call[1] = &sb2; 
  loop_call[2] = &sb3; 
  loop_call[3] = &sb4; 
  sb1.setup_button(); 
  sb2.setup_button(); 
  sb3.setup_button(); 
  sb4.setup_button(); 

  Serial.begin(9600); 

}


void loop() {
  // put your main code here, to run repeatedly:

  if (sb1.current_state() != last_state1) {  
    last_state1 = sb1.current_state(); 
  }
  if (sb2.current_state() != last_state2) { 
    last_state2 = sb2.current_state(); 
  }
  if (sb3.current_state() != last_state3) { 
    last_state3 = sb3.current_state(); 
  }
  if (sb4.current_state() != last_state4) { 
    last_state4 = sb4.current_state(); 
  }


  for (int i = 0; i < loops; i++) { 
    loop_call[i]->loop_check(); 
  }
}