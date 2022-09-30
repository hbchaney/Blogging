#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Rotary_Encoder.hpp"
#include "RTClib.h"
#include <vector>

RTC_PCF8523 rtc; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  rtc.begin(&Wire);

}

void loop() {
  // put your main code here, to run repeatedly:

}