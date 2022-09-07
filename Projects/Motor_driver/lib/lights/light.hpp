#ifndef GEN_LIGHT 
#define GEN_LIGHT 
#include "Loop_elem.hpp"
#include <Arduino.h>

class LEDLight : public LoopElement {
    int pin_num; 
    bool state;
    bool blink;
    unsigned long flash_timer; 
    unsigned long blink_freq; 
    bool blink_toggle; 

    public: 
    LEDLight(int,unsigned long); 
    ~LEDLight(); 

    //setup the LED light 
    void setup (void);

    //check on blink timer 
    void loop_check(void) override;

    //turn on the LED
    void on(); 

    //turn off LED
    void off(); 

    //turn on blink 
    void blink_on(); 

    //turn off blink 
    void blink_off(); 





}; 



#endif 