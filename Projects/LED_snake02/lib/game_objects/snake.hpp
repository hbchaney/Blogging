#pragma once 
#include "game_object.hpp"


class Snake : public Object 
{ 
    Coord Body[5]; 
    Coord Extension[10]; 
    int ext_length = 1; 

    //might add a direction delay feature to eat multi inputs between frames 
    //direction toggled 
    Coord direction{0,1};

    public: 

    Snake(); 
    ~Snake(); 

    void change_direction(int); //-1 or 1 for ccw or cw 
    const Coord& head_position(); //returns the head position for collision checking 
    void increase_length(); //increases length by one  
    bool check_body_collision(); //returns if the snake collided with itself 

    //override functions 
    void update_display_buffer() override; 
    void update_off_buffer() override; 

};