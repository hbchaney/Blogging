#include "snake.hpp"
#include <Arduino.h>

Snake::Snake() 
{
    object_color = LED_GREEN; //set the snake color 
    for (int i = 0; i < 5; i++) 
    {
        Body[i] = {0,0};  //move all the body parts to be at 0,0
    }
}

void Snake::change_direction(int change) 
{ 
    short x; 
    short y;  
    
    if (change == -1) //ccw turn 
    {
        x = direction._y; 
        y = -direction._x; 
        direction = {x,y}; 
    }
    else if (change == 1) 
    { 
        x = -direction._y; 
        y = direction._x;
        direction = {x,y}; 
    }
}

const Coord& Snake::head_position() 
{ 
    return Body[0]; 
}

bool Snake::increase_length() 
{ 
    if (ext_length < 18) 
    { 
        ext_length += 1; 
        return 0;
    }
    else 
    { 
        return 1; 
    }
}

bool Snake::check_body_collision() 
{   
    //collision with the base body 
    for (int i = 1; i < 5; i++) 
    { 
        if (Body[i] == Body[0]) 
        { 
            return 1; 
        }
    }
    //collision with the extension 
    for (int i = 0; i < ext_length - 1; i++) 
    { 
        if (Extension[i] == Body[0]) 
        { 
            return 1; 
        }
    }
    return 0; 
}

void Snake::update_position()
{ 
    //going backwards thorough the snake 
    for (int i = ext_length; i > 0; i--)
    { 
        Extension[i] = Extension[i-1]; 
    }
    Extension[0] = Body[4]; 
    for (int i = 4; i > 0; i--) 
    { 
        Body[i] = Body[i-1]; 
    }
    //moving the snake head now 
    Body[0]._x = (direction._x + Body[0]._x + 8) % 8; 
    Body[0]._y = (direction._y + Body[0]._y + 8) % 8;  

}

void Snake::update_display_buffer() 
{ 
    display_buffer = Body[0]; 
}

void Snake::update_off_buffer() 
{ 
    update_position(); 
    off_buffer = Extension[ext_length]; 
}

