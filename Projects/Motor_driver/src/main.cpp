#include <Arduino.h>
#include "State_button.hpp"
#include "light.hpp"
#include "rgb_light.hpp"
#include "TB6612.hpp"

/*
GLOBALS
*/

TB6612 motor_drive; 

StateButton sb1 {0,2}; //button on pin 0 
StateButton sb2 {1,2}; //button on pin 1 
StateButton sb3 {6,2}; //button on pin 6
StateButton sb4 {7,2}; //button on pin 7

LEDLight rl1 {12,150}; //light on pin 12 
RGBLight rgb1 {11,10,9,150}; 

const int loops = 6; 
LoopElement* loop_call[loops]; 

short last_state1 = 0; 
short last_state2 = 2; 
short last_state3 = 2; 
short last_state4 = 2; 

bool running = 0; 
bool blink_toggle = 0; 

rgb_color red {255,0,0}; 
rgb_color green {0,255,0}; 
rgb_color blue {0,0,255}; 

void setup() {
  // put your setup code here, to run once:

  loop_call[0] = &sb1; 
  loop_call[1] = &sb2; 
  loop_call[2] = &sb3; 
  loop_call[3] = &sb4; 
  loop_call[4] = &rl1;
  loop_call[5] = &rgb1;

  motor_drive.begin(); 
  motor_drive.set_speed(255); 
  motor_drive.stop(); 

  sb1.setup(); 
  sb2.setup(); 
  sb3.setup(); 
  sb4.setup(); 

  rl1.setup(); 
  rl1.on(); 
  rl1.blink_on(); 
  rgb1.setup(); 
  rgb1.set_brightness(2); 
  rgb1.on(); 

  Serial.begin(9600); 

}


void loop() {
  // put your main code here, to run repeatedly:
  
  //code for the start/stop 
  if (sb1.current_state() != last_state1) {  
    last_state1 = sb1.current_state(); 
    if (running) 
    { 
      motor_drive.stop(); 
      rl1.off();
      running = 0;
    }
    else 
    { 
      motor_drive.start(); 
      rl1.on(); 
      running = 1;
    }
  }

  //reverse and forward
  if (sb2.current_state() != last_state2) { 
    last_state2 = sb2.current_state(); 
    if (blink_toggle == 0) 
    { 
      rl1.blink_off(); 
      blink_toggle = 1; 
    }
    else 
    { 
      rl1.blink_on(); 
      blink_toggle = 0; 
    }
    motor_drive.reverse(); 
  }


  if (sb3.current_state() != last_state3) { 
    last_state3 = sb3.current_state(); 
    rgb1.set_color(blue); 
  }

  //
  if (sb4.current_state() != last_state4) { 
    last_state4 = sb4.current_state(); 
  }


  for (int i = 0; i < loops; i++) { 
    loop_call[i]->loop_check(); 
  }
}