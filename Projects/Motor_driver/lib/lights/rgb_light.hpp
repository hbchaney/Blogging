#ifndef RGBLIGHT 
#define RGBLIGHT 

#include "Loop_elem.hpp" 
#include <Arduino.h>

struct rgb_color { 
    int r_col=125; 
    int g_col=125; 
    int b_col=125; 

    rgb_color (int,int,int); 
};

class RGBLight : public LoopElement { 
    int pin_num1, pin_num2, pin_num3; 
    unsigned long last_blink; 
    unsigned long blink_freq; 
    int brightness = 5; 
    rgb_color _color;
    bool state = 0; 
    bool blink = 0; 
    bool blink_toggle = 0; 


    public: 
    RGBLight (int,int,int,unsigned long); 
    ~RGBLight (); 
    
    //setup for the RGB light 
    void setup(); 

    //set the color of the light 
    void set_color(rgb_color);

    //set brightness from 1 to 10
    void set_brightness(int); 

    //turn light on/off
    void on(); 
    void off(); 

    //turn blink on and off 
    void blink_on(); 
    void blink_off(); 

    //loop check 
    void loop_check(void) override; 


};



#endif 