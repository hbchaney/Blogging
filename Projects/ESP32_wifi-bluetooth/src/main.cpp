#include <Arduino.h>
#include <WiFi.h>
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel lightbulb {1,2};  


void setup() {
  // put your setup code here, to run once:
  lightbulb.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  lightbulb.setPixelColor(0,125,125,125);



}