#pragma once 
#include "Loop_Element.hpp"
#include "Adafruit_LEDBackpack.h"

class Mode : public LoopElement 
{
    protected: 
    Adafruit_7segment* disp; 
    public: 
    
    //static image to write to display and flash 
    void preview(Adafruit_7segment*);
};