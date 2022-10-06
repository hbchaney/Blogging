#pragma once 
#include "Loop_Element.hpp"
#include "Adafruit_LEDBackpack.h"
#include "Rotary_Encoder.hpp"
#include "RTClib.h"
#include "Buzzer.hpp"

class AlarmClock : public LoopElement 
{   
    //typedef for the function ptr 
    typedef void (AlarmClock::*loop_ptr)(void); 
    loop_ptr current_loop; 
    //shared variables
    Adafruit_7segment* disp; 
    RotaryEncoder* re; 
    RTC_PCF8523* rtc; 
    Buzzer* buz; 
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
    //alarm beepin 
    bool alarm_beep = 0;
    unsigned long alarm_shutoff_length = 30000; 
    unsigned long alarm_shutoff_timer = 0; 

    //set mode blinker timers 
    unsigned long blink_time = 200; 
    unsigned long last_blink = 0; 
    bool blink = false; 

    public: 

    //init function 
    AlarmClock(Adafruit_7segment*,RotaryEncoder*,RTC_PCF8523*); 

    //destructor function 
    ~AlarmClock(); 

    //mode set loop function 

    void modeSet_loop (); //asks for setting the alarms and clc 
        void modeSet_readcache (); 
            void modeSet_loop2(); 

    //displays the current time from hour / minute and calls timeSet_readcache() 
    void timeSet_loop ();
        //pulls from the r_cache and adjusts the values of hour/ minute and calls save_time if button is pressed 
        void timeSet_readcache (); 

    void showClock_loop(); 
        void showClock_readcache(); //for turning off alarm 

    //main loop checks to see if the re has called for mode set loop 
    void loop_check() override; 


};