#include "Buzzer.hpp"

Buzzer::Buzzer(int pin) : pin_num{pin} {} 

Buzzer::~Buzzer() {} 

void Buzzer::begin() 
{ 
    pinMode(pin_num,OUTPUT); 
}

void Buzzer::on() 
{ 
    active = true; 
    on_start = millis(); 
}

void Buzzer::off()
{ 
    active = false; 
    digitalWrite(pin_num,LOW); 
}

void Buzzer::loop_check() 
{ 
    if (active) 
    { 
        if (last_switch + times[timing_location] < millis())
        {
            sound ^= 1; 
            digitalWrite(pin_num,sound); 

            last_switch = millis(); 
            timing_location = (timing_location + 1) % 4; 
            
        }
    }
    if (on_start + auto_shutoff < millis()) 
    { 
        active = false; 
    }
}

const bool& Buzzer::status() 
{ 
    return active; 
}