#include "AnalogDimmer.hpp"

AnalogDimmer::AnalogDimmer(Adafruit_LEDBackpack* d) : disp{d} {} 

void AnalogDimmer::loop_check ()
{ 
    if (last_check + time_delay < millis())
    {
        int v = analogRead(analog_pin); 

        if (v > 100) 
        { 
            disp->setBrightness(max_brightness);
        }
        else if (v > 18) 
        { 
            disp->setBrightness(max_brightness/2); 
        }
        else 
        { 
            disp->setBrightness(min_brightness); 
        }
        last_check = millis(); 
    }
        
}