#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H


#include <Arduino.h> 
#include "Loop_Element.hpp"


class RotaryEncoder : public LoopElement { 
    int in_pin1, in_pin2, button_pin; 
    int8_t l,r,lrmem = 3;
    int TRANS[16];
    int lrsum = 0;

    bool button_toggle = 0;     
    bool two_second = 0; 
    bool five_second = 0; 
    int output_buffer = 0; //this buffer will be used with loop check to see if anything has been pressed 
    unsigned long press_start;  
    //checks to see if there was a increment +1 or -1 
    int check_increment();
    int check_button(); 

    public: 
    RotaryEncoder(int,int,int); 
    ~RotaryEncoder(); 

    void setup(void); 

    void loop_check (void) override; 

    int pull_cache (void); 
    int check_cache (void); 


    

};
 
#endif


