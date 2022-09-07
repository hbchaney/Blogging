#include "light.hpp"


LEDLight::LEDLight(int pin, unsigned long blink) : pin_num{pin} , blink_freq{blink} {
    flash_timer = millis(); 
    blink = 0; 
    state = 0; 
    blink_toggle = 0; 
}

LEDLight::~LEDLight() {} 

void LEDLight::setup(void) { 
    pinMode(pin_num,OUTPUT); 
} 

void LEDLight::on() { 
    state = 1; 
    digitalWrite(pin_num,HIGH); 
}

void LEDLight::off() { 
    state = 0; 
    digitalWrite(pin_num,LOW); 
}

void LEDLight::blink_on() { 
    blink = 1; 
}

void LEDLight::blink_off() { 
    blink = 0; 
    if (state) { 
        digitalWrite(pin_num,HIGH); 
    }
}

void LEDLight::loop_check() { 

    //check to see if blink is on and light is on 
    if (state && blink) { 
        //check to see if enough time has passed
        if (flash_timer + blink_freq < millis()) { 
            digitalWrite(pin_num,blink_toggle); 
            blink_toggle = blink_toggle ^ 1; 
            flash_timer = millis();  

        }
    }
}