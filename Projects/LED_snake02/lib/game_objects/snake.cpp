#include "snake.hpp"

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

