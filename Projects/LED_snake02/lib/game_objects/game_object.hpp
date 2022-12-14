#pragma once 
#include "Adafruit_LEDBackpack.h"
#include "Loop_Element.hpp"
#include "Coords.hpp"


class Object : public LoopElement
{
    protected:
    Coord display_buffer; 
    Coord off_buffer; 

    public:  
    uint16_t object_color;

    Object(); 
    
    Coord pull_display_buffer();  
    Coord pull_off_buffer();  

    //this game has a max of 1 pixel update and 1 pixel delete per frame for each object 
    virtual void update_display_buffer() = 0; 
    virtual void update_off_buffer() = 0; 

    virtual void loop_check() override;  //override from loop check 

};