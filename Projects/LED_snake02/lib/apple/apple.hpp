#pragma once 
#include "game_object.hpp"

class Apple: public Object  
{ 
    Coord apple_position = Coord::nullCoord; 
    bool apple_spawn = 0; 
    unsigned long last_spawn = 0; 
    unsigned long spawn_delay; 

    public: 

    Apple(); 
    void spawn_apple(); //spawns an apple if the time is right 
    bool check_collision (Coord); //checks collision with the snake head 


    //override functions 
    void update_display_buffer() override; 
    void update_off_buffer() override; 

    void loop_check() override; 

};