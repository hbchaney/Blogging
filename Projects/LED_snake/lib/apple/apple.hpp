#pragma once 
#include "Loop_Element.hpp"
#include "Adafruit_LEDBackpack.h"
#include "snake.hpp"


class Apple : public LoopElement, public Adafruit_BicolorMatrix
{ 
    Coord apple_location = {0,0}; 
    unsigned long eat_delay; 
    unsigned long last_eaten; 
    Snake* snk_ptr; 
    uint16_t apple_color = LED_RED; 
    bool spawned = false; 

    void spawn_apple(); 
    void check_collision(); 

    
    public:  

    Apple(uint16_t,unsigned long, Snake* ); 
    ~Apple(); 

    void Apple::loop_check() override;  



};