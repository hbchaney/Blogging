#pragma once 
#include "Loop_Element.hpp"
#include "Adafruit_LEDBackpack.h"

struct Coord 
{ 
    short _x = 0; 
    short _y = 0; 

    bool operator==(Coord); 
};

class Snake : public LoopElement, public Adafruit_BicolorMatrix
{ 
    Coord snake_body[5]; 
    Coord snake_extension[20]; 
    int ext_length = 0; 
    Coord direction {-1,0}; //initial direction is to the right 
    unsigned long update_rate; 
    unsigned long last_update = 0;
    uint16_t snake_color =  LED_YELLOW; 

    void update_position(); 
    bool check_collision(); 

    public: 

    Snake (unsigned long,uint16_t); 
    ~Snake (); 


    void change_direction(short); 
    void loop_check() override; 

    Coord head_position (); 
    void increase_length(int); 



};