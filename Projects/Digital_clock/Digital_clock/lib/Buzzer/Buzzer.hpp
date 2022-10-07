#pragma once 
#include <Arduino.h>
#include "Loop_Element.hpp"

class Buzzer : public LoopElement
{   
    //pin_num
    int pin_num; 

    //beeping settings 
    unsigned long times[4] = {50,100,50,400}; //beep,small pause, beep, long pause
    unsigned long last_switch = 0; 
    int timing_location = 0; 
    bool sound = 1; 

    //state 
    bool active = false; 

    //auto shut off 
    unsigned long on_start = 0; 
    unsigned long auto_shutoff = 30000; 

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