#include "AlarmClock.hpp"

AlarmClock::AlarmClock(Adafruit_7segment* sev,RotaryEncoder* rot,RTC_PCF8523* r) : disp{sev}, re{rot}, rtc{r} {}

AlarmClock::~AlarmClock() {} 

void AlarmClock::modeSet_loop() 
{ 
    /* 
    0 = a1
    1 = a2 
    2 = clc
    */
   //shown the modes
   switch(set_mode) 
   {
    case 0: 
        disp->writeDigitAscii(0,'A'); 
        disp->writeDigitNum(1,1); 
        disp->writeDisplay(); 
        break; 
    case 1: 
        disp->writeDigitAscii(0,'A'); 
        disp->writeDigitNum(1,2); 
        disp->writeDisplay(); 
        break;
    case 2: 
        disp->writeDigitAscii(0,'C');
        disp->writeDigitAscii(1,'L');
        disp->writeDigitAscii(2,'C');
        disp->writeDisplay(); 
   }

   modeSet_readcache(); 

}

void AlarmClock::modeSet_readcache() 
{ 
    if (r_cache != 0)
    { 
        //reset the cache 
        int pulled = r_cache; 
        r_cache = 0; 

        //go throught the options 
        if (abs(pulled) == 1) 
        {
            //the cycling the select mode 
            set_mode = (set_mode + pulled + 3) % 3; 
        }
        else
        {
            //button pressed 
            if (set_mode == 2) 
            { 
                current_loop = &AlarmClock::timeSet_loop; 
            }
        }
        
    }
}

void AlarmClock::timeSet_loop() 
{ 
    //display the current time 

    disp->clear(); 

    //writing the hour 
    if (hour / 10) 
    { 
        disp->writeDigitNum(0,1); 
    }
    disp->writeDigitNum(1,hour % 10); 

    //writing minute 
    if (minute / 10) 
    { 
        disp->writeDigitNum(2,minute / 10);
    }
    disp->writeDigitNum(3,minute % 10); 

}

void AlarmClock::timeSet_readcache() 
{ 
    //pulls the value from r_cache and either sets the time or changes the hour/minute values 
    if (r_cache != 0) 
    { 
        int pulled = r_cache; 
        r_cache = 0; 

        if (abs(pulled) == 1) 
        { 
            int  = minute + pulled; 
        }
    }
}