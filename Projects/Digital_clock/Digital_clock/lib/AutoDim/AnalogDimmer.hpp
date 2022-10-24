#pragma once 

#include "Loop_Element.hpp"
#include "Adafruit_LEDBackpack.h"

class AnalogDimmer : public LoopElement 
{ 
    int max_brightness = 8; 
    int min_brightness = 0; 
    Adafruit_LEDBackpack* disp; 

    //analog pin 
    int analog_pin; 

    unsigned long last_check = 0; 
    unsigned long time_delay = 8000; 

    public: 

    /*!
     * @brief set the AutoDim
     * @param display 
     */
    AnalogDimmer (Adafruit_LEDBackpack* display); 
    ~AnalogDimmer (); 

    void loop_check() override; 
};