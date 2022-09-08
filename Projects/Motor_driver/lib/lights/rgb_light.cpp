#include "rgb_light.hpp"

RGBLight::RGBLight(int pin1, int pin2, int pin3, unsigned long blinkf) : 
                pin_num1{pin1}, 
                pin_num2{pin2}, 
                pin_num3{pin3}, 
                blink_freq{blinkf} {
                    last_blink = millis(); 

                } 

RGBLight::~RGBLight () {} 

void RGBLight::setup() { 
    pinMode(pin_num1,OUTPUT); 
    pinMode(pin_num2,OUTPUT); 
    pinMode(pin_num3,OUTPUT); 

}

void RGBLight::set_brightness(int bright) {
    brightness = bright; 
} 

void RGBLight::set_color (rgb_color _col) {
    _color = _col; 
}

void RGBLight::on() {
    state = 1; 
    analogWrite(pin_num1,(_color.r_col*brightness)/10);
    analogWrite(pin_num2,(_color.g_col*brightness)/10);
    analogWrite(pin_num3,(_color.b_col*brightness)/10);
} 
void RGBLight::off() {
    state = 0; 
    analogWrite(pin_num1,0); 
    analogWrite(pin_num2,0); 
    analogWrite(pin_num3,0); 
}

void RGBLight::blink_on() {
    blink = 1; 
} 

void RGBLight::blink_off() {
    blink = 0; 
    if (state) { 
        on(); 
    }
} 

void RGBLight::loop_check() { 
    //check to see if light is on and blink is on 
    if (state && blink) { 
        if (last_blink + blink_freq < millis()) { 
            if (blink_toggle) { 
                    analogWrite(pin_num1,(_color.r_col*brightness)/10);
                    analogWrite(pin_num2,(_color.g_col*brightness)/10);
                    analogWrite(pin_num3,(_color.b_col*brightness)/10); 
            }
            else { 
                    analogWrite(pin_num1,0); 
                    analogWrite(pin_num2,0); 
                    analogWrite(pin_num3,0); 
            }

            blink_toggle = blink_toggle^1; 
            last_blink = millis(); 


        }

    }
}




