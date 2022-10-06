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

void AlarmClock::modeSet_loop2() 
{ 
    //check which alarm 
    bool val; 
    if (set_mode == 1) 
    { 
        val = alarm1_on; 
    }
    else 
    { 
        val = alarm2_on; 
    }

    //printing that the alarm is on
    if (val) 
    { 
        disp->clear(); 
        disp->writeDigitAscii(2,'O'); 
        disp->writeDigitAscii(3,'n'); 
        disp->writeDisplay(); 
    }
    else 
    {   
        //printing that the alarm is off
        disp->clear(); 
        disp->writeDigitAscii(1,'O'); 
        disp->writeDigitAscii(2,'f'); 
        disp->writeDigitAscii(3,'f'); 
        disp->writeDisplay(); 

    }

    //reading the cache 
    if (r_cache != 0)
    { 
        int pulled = r_cache; 
        r_cache = 0; 

        if (abs(pulled) == 1) 
        { 
            if (set_mode == 1) 
            {
                alarm1_on ^= 1; 
            }
            else 
            { 
                alarm2_on ^= 1;
            }
        }
        else 
        { 
            if (val) 
            { 

            }
        }
    }
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
            else 
            { 
                current_loop = &AlarmClock::modeSet_loop2; 
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

    disp->writeDisplay(); 
    timeSet_readcache(); 

}

void AlarmClock::timeSet_readcache() 
{ 
    //pulls the value from r_cache and either sets the time or changes the hour/minute values 
    if (r_cache != 0) 
    { 
        int pulled = r_cache; 
        r_cache = 0; 

        // knob turned positively / negatively
        if (abs(pulled) == 1) 
        { 
            minute += pulled;

            //minute overflow condition
            if (minute > 59) 
            {
                minute = 0; 
                hour += 1; 
                //hour overflow condition
                if (hour > 12) 
                { 
                    hour = 1; 
                    am ^= 1; 
                }
            }
            if (minute < 0) 
            { 
                minute = 59; 
                hour -= 1; 
                if (hour < 1) 
                { 
                    hour = 12; 
                    am ^= 1; 
                }
            }
        }

        if (pulled == 5) 
        { 
            //set time and go to clock mode 

            //set time 
            DateTime new_time {2022,10,4,
            static_cast<uint8_t>(hour + (am^1)*12),
            static_cast<uint8_t>(minute),
            static_cast<uint8_t>(0)};
            //set clock 
            if (set_mode == 2) 
            {
                rtc->adjust(new_time); 
            }
            //set alarm 2
            if (set_mode == 1) 
            { 
                alarm2 = new_time; 
            }
            //set alarm 1
            else
            { 
                alarm1 = new_time; 
            }

            current_loop = &AlarmClock::showClock_loop; 
        }
        
    }
}

void AlarmClock::showClock_loop() 
{ 
    //update the time 
    minute = static_cast<uint8_t>(rtc->now().minute()); 
    hour = static_cast<uint8_t>(rtc->now().twelveHour());
    am = (rtc->now().hour() / 13)^1; 
    //if pm 


    //check to see if the alarm should trigger 


    showClock_readcache(); 
}