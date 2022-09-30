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