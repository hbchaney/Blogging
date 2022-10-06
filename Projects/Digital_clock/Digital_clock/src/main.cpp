#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Rotary_Encoder.hpp"
#include "RTClib.h"
#include <vector>
#include "Buzzer.hpp"

Buzzer buzz {7}; 
RotaryEncoder re{11,12,13}; 
int puller; 

void setup() 
{
  buzz.begin(); 
  re.setup();
}

void loop() 
{
  // put your main code here, to run repeatedly:

  puller = re.pull_cache();
  if (puller == 5) 
  { 
      if (buzz.status()) 
      { 
        buzz.off();
      }
      else 
      { 
        buzz.on(); 
      }
  }
  buzz.loop_check(); 
  re.loop_check();

}