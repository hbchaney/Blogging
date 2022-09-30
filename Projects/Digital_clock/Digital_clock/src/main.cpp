#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Rotary_Encoder.hpp"
#include "RTClib.h"
#include <vector>


DateTime ct{2022,9,26,(6+12),14,0};
RTC_PCF8523 rtc; 
uint8_t second; 

Adafruit_7segment svdisp; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  rtc.begin(&Wire);
  svdisp.begin(0x70,&Wire1);
  svdisp.setBrightness(1);
  rtc.adjust(ct); 


}

void loop() {
  // put your main code here, to run repeatedly:

}