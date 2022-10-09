#include "AutoDim.hpp"


AutoDim::AutoDim(Adafruit_LEDBackpack* d, Adafruit_VCNL4010* ls) : disp{d}, sense{ls} {} 

void AutoDim::loop_check ()
{ 
    if (last_check + time_delay < millis())
    {
        uint16_t v = sense->readAmbient(); 

        if (v > 500) 
        { 
            disp->setBrightness(max_brightness);
        }
        else if (v > 100) 
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