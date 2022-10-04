#pragma once 
#include "Loop_Element.hpp"
#include "Adafruit_LEDBackpack.h"
#include "Rotary_Encoder.hpp"
#include "RTClib.h"

class AlarmClock : public LoopElement 
{   
    //typedef for the function ptr 
    typedef void (AlarmClock::*loop_ptr)(void); 
    loop_ptr current_loop; 
    //shared variables
    Adafruit_7segment* disp; 
    RotaryEncoder* re; 
    RTC_PCF8523* rtc; 
    int r_cache; 

    //current shown 
    int hour = 1; 
    int minute = 0; 
    bool am = 1; 

    //mode set 
    int set_mode; //a1,a2,clc

    //alarm 
    DateTime alarm1; 
    DateTime alarm2; 
    bool alarm1_on = 0; 
    bool alarm2_on = 0;

    //set mode blinker timers 
    unsigned long blink_time = 200; 
    unsigned long last_blink; 
    bool blink = false; 

    public: 

    //init function 
    AlarmClock(Adafruit_7segment*,RotaryEncoder*,RTC_PCF8523*); 

    //destructor function 
    ~AlarmClock(); 

    //mode set loop function 

    void modeSet_loop (); 
        void modeSet_readcache (); 

    //displays the current time from hour / minute and calls timeSet_readcache() 
    void timeSet_loop ();
        //pulls from the r_cache and adjusts the values of hour/ minute and calls save_time if button is pressed 
        void timeSet_readcache (); 
            void save_time(int); 

    void AlarmOn_loop(); 
        void AlarmOn_readcache(); 

    void showClock_loop(); 
        void showClock_readcache(); 

    //main loop checks to see if the re has called for mode set loop 
    void loop_check() override; 


};