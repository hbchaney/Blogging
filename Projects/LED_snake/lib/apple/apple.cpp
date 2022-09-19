#include "apple.hpp"

Apple::Apple(uint16_t col, unsigned long time, Snake* snk ) : apple_color{col}, eat_delay{time}, snk_ptr{snk}
{ 
    
}

void Apple::spawn_apple() 
{
     //spawns an apple not on the head of the snake 

    Coord snk_head = snk_ptr->head_position(); 
    do
    {
        short x = static_cast<short>(random(0,7)); 
        short y = static_cast<short>(random(0,7));
    
        apple_location = {x,y}; 
    }
    while(apple_location == snk_head); 

    drawPixel(apple_location._x,apple_location._y,apple_color); 

}

void Apple::loop_check() 
{ 
    //loop checks the snake first than spawns the apple 
    //also checks if enough time has passed 
}

