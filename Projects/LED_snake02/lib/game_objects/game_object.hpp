#pragma once 
#include "Adafruit_LEDBackpack.h"
#include "Loop_Element.hpp"

struct Coord 
{ 
    short _x= -5;
    short _y= -5; 

    Coord(); 
    bool operator=(Coord); 
    Coord(int,int); 

};


class Object : public LoopElement
{
    protected:
    static Coord nullcoord;  //the non pointer  
    Coord display_buffer; 
    Coord off_buffer; 

    public: 
    uint16_t object_color;

    Object(); 
    
    Coord pull_display_buffer();  
    Coord pull_off_buffer();  

    virtual void update_display_buffer() = 0; 
    virtual void update_off_buffer() = 0; 

    virtual void loop_check() override; 

};