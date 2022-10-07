#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Rotary_Encoder.hpp"
#include "RTClib.h"
#include <vector>
#include "Buzzer.hpp"
#include "AlarmClock.hpp"

Buzzer buzz {7}; 
RotaryEncoder re{12,11,13};
RTC_PCF8523 rtc;  
Adafruit_7segment disp; 

AlarmClock clc {&disp, &re, &rtc}; 

void setup() 
{
  disp.begin(); 
  buzz.begin(); 
  re.setup();
  rtc.begin(&Wire1); 
}

void loop() 
{
  // put your main code here, to run repeatedly:

  clc.loop_check(); 
  buzz.loop_check(); 
  re.loop_check();

}