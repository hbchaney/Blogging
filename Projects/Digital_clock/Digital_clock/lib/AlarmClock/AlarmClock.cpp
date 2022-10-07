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
    disp->clear(); 
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
        disp->writeDigitAscii(3,'C');
        disp->writeDisplay(); 
        break;
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
        disp->writeDigitAscii(1,'O'); 
        disp->writeDigitAscii(3,'n'); 
        disp->writeDisplay(); 
    }
    else 
    {   
        //printing that the alarm is off
        disp->clear(); 
        disp->writeDigitAscii(1,'O'); 
        disp->writeDigitAscii(3,'f'); 
        disp->writeDigitAscii(4,'f'); 
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
                current_loop = &AlarmClock::showClock_loop; 
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
        disp->writeDigitNum(3,minute / 10);
    }
    disp->writeDigitNum(4,minute % 10); 

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
    minute = static_cast<int>(rtc->now().minute()); 
    hour = static_cast<int>(rtc->now().twelveHour());
    am = (rtc->now().hour() / 12)^1; // set am true or not 

    //clear display 
    disp->clear();
    //add : 
    disp->writeColon(); 
    // write the am 
    if (am) 
    { 
        disp->writeDigitNum(4,minute % 10); 
    }
    else 
    { 
        disp->writeDigitNum(4,minute % 3, true); 
    }
    disp->writeDigitNum(3,minute / 10); 

    //write the pm 
    if (hour / 10) 
    { 
        disp->writeDigitNum(0,1); 
    }
    disp->writeDigitNum(1,hour % 10); 
    //send to display 
    disp->writeDisplay(); 


    //check to see if the alarm should trigger    
    check_alarm();
    showClock_readcache(); 
}

void AlarmClock::check_alarm() 
{ 
    //checks to see if the time has hit an alarm time 
    // has the alarm recently gone off 
    if (last_alarm_trigger + 60000 > millis()) 
    {
        return; // return if not enough time has past 

    }

    //alarm1 check if on 
    if (alarm1_on) 
    { 
        if (minute == alarm1.minute() && rtc->now().hour() == alarm1.hour())
        {
            last_alarm_trigger = millis(); 
            buz->on(); 

        }
    }

    if (alarm2_on) 
    { 
        if (minute == alarm2.minute() && rtc->now().hour() == alarm2.hour())
        {
            last_alarm_trigger = millis(); 
        }
    }
}


void AlarmClock::showClock_readcache() 
{ 
    if (r_cache != 0) 
    { 
        if (buz->status()) 
        { 
            if (r_cache == 5)
            {
                buz->off(); 
            }
        }

        r_cache = 0; 
    }
}


void AlarmClock::loop_check() 
{ 
    r_cache = re->pull_cache(); 
    if (r_cache == 7) 
    { 
        current_loop = &AlarmClock::modeSet_loop; 
        r_cache = 0; 
    }

    (this->*current_loop)(); 

    
}