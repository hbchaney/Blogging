#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"
#include "Rotary_Encoder.hpp"

RotaryEncoder R1 {18,19,20}; 

void setup() {
  // put your setup code here, to run once:
  R1.setup(); 
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int pull = R1.pull_cache(); 
  if (pull != 0) { 
    Serial.print("button press : "); 
    switch (pull) {
      case 5: 
        Serial.println("Short"); 
        break;
      case 7: 
        Serial.println("2 second");
        break; 
      case 10: 
        Serial.println("5 second");
        break; 
      case 1: 
        Serial.println("turned CC"); 
        break; 
      case -1: 
        Serial.println("turned CCW"); 
        break;

    }
  }

  R1.loop_check(); 
}