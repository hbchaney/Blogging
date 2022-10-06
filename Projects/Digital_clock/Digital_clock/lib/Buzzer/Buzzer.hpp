#pragma once 
#include <Arduino.h>
#include "Loop_Element.hpp"

class Buzzer : public LoopElement
{   
    int pin_num; 
    unsigned long beep_length = 500; 
    unsigned long last_beep = 0; 
    bool sound = 0; 

    bool active = false; 

    public: 
    Buzzer(int); 
    ~Buzzer();

    //initialize the pins
    void begin(); 

    const bool& status (); 

    void off(); 
    void on(); 

    void loop_check() override; 
};