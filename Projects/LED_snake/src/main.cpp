#include <Arduino.h>
#include <Wire.h> 
#include "Rotary_Encoder.hpp"
#include "snake.hpp"


Snake snk {100,LED_YELLOW}; 
RotaryEncoder re {9,10,11}; 
int output; 

void setup() {
  // put your setup code here, to run once:
  snk.begin(0x70,&Wire1);
  snk.clear(); 
  snk.setBrightness(8);  

  re.setup(); 
}

void loop() {
  // put your main code here, to run repeatedly:
  output = re.pull_cache(); 
  if (output != 0 && abs(output) == 1) 
  { 
    snk.change_direction(static_cast<short>(output)); 
  }


  re.loop_check(); 
  snk.loop_check(); 
}