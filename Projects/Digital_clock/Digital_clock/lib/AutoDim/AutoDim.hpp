#pragma once 

#include "Loop_Element.hpp"
#include "Adafruit_VCNL4010.h"
#include "Adafruit_LEDBackpack.h"

class AutoDim : public LoopElement 
{ 
    int max_brightness = 8; 
    int min_brightness = 0; 
    Adafruit_LEDBackpack* disp; 
    Adafruit_VCNL4010* sense; 

    unsigned long last_check = 0; 
    unsigned long time_delay = 8000; 

    public: 

    AutoDim (Adafruit_LEDBackpack*,Adafruit_VCNL4010*); 
    ~AutoDim (); 

    void loop_check() override; 
};