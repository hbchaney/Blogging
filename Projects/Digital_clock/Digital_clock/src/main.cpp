#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Rotary_Encoder.hpp"
#include "RTClib.h"
#include <vector>
#include "Buzzer.hpp"
#include "AlarmClock.hpp"
#include "AutoDim.hpp"

Buzzer buzz {7}; 
RotaryEncoder re{12,11,13};
RTC_PCF8523 rtc;  
Adafruit_VCNL4010 Ls; 
Adafruit_7segment disp; 
AutoDim ad {&disp,&Ls}; 


AlarmClock clc {&disp, &re, &rtc, &buzz}; 

void setup() 
{
  disp.begin(); 
  buzz.begin(); 
  re.setup();
  rtc.begin(&Wire1); 
  Ls.begin(VCNL4010_I2CADDR_DEFAULT,&Wire1);

}

void loop() 
{
  // put your main code here, to run repeatedly:
   

  clc.loop_check(); 
  buzz.loop_check(); 
  re.loop_check();
  ad.loop_check(); 

}