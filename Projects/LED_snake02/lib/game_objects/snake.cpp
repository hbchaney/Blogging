#include "snake.hpp"

Snake::Snake() 
{
    object_color = LED_GREEN; //set the snake color 
    for (int i = 0; i < 5; i++) 
    {
        Body[i] = {0,0};  //move all the body parts to be at 0,0
    }
}

