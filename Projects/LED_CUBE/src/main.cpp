#include <Arduino.h>
#include "Rotary_Encoder.hpp"
#include "Timer.hpp"
#include <Wire.h>

class E_toggle  { 
  
  RotaryEncoder Encoder;
  unsigned long long_press; 
  unsigned long press_start = 0; 
  unsigned long t_delay = 50; 
  unsigned long last_press = 0; 
  bool pressed = 0; 
  bool long_trigger = 0; 
  

  public: 
  E_toggle (RotaryEncoder basic, unsigned long long_push=2000) : Encoder{basic}, long_press{long_push} {} 

  int directions () { 


    unsigned long button_status = Encoder.check_button(); 
    if (button_status > 10 && button_status < long_press ) { 
      pressed = true; 
      long_trigger = false; 
    }
    else if (button_status == 0 && pressed) {
      //check to see if it has been pressed recently 
      if ((millis() - last_press) > t_delay) { 
         pressed = 0; 
         last_press = millis();
         return 5; 
      }
      pressed = 0; 
    }
    else if (button_status > long_press && long_trigger == false) {
      pressed = false; 
      long_trigger = true; 
      return 87;  
    }

    return Encoder.check_increment(); 
  }
}; 


RotaryEncoder Encode {9,10,11}; 
E_toggle toggler {Encode}; 
MatrixTimer timer {}; 

void setup() {
  // put your setup code here, to run once:
  timer.begin(0x70,&Wire1); 

}

void loop() {
  // put your main code here, to run repeatedly:

  int directions = toggler.directions();
  timer.update_timer(directions); 

}