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
        if (beep_length + last_beep < millis())
        {
            digitalWrite(pin_num,sound); 
            sound ^= 1; 
            last_beep = millis(); 
        }
    }
}

const bool& Buzzer::status() 
{ 
    return active; 
}