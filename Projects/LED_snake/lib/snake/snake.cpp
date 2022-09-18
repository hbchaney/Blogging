#include "snake.hpp"

Snake::Snake(unsigned long update,uint16_t col) : update_rate {update}, snake_color{col} {} 

Snake::~Snake () 
{
    //setting all snakes body at 0,0 
    snake_body[0] = {0,0};
    for (int i = 1; i < 5 ; i++) 
    { 
        snake_body[i] = snake_body[0]; 
    }
} 


void Snake::change_direction(short change) 

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

void Snake::update_position() 
{
    //updating the snake tail 
    for(int i = 4; i > 0; i--)
    {
        snake_body[i] = snake_body[i-1]; 
    }
    short x = (snake_body[0]._x + direction._x + 8) % 8; 
    short y = (snake_body[0]._y + direction._y + 8) % 8; 
    snake_body[0] = {x,y}; 

}


void Snake::loop_check() 
{ 
    //first determine if there has been enought time 
    if (last_update + update_rate < millis()) 
    { 
        //update the position 
        update_position(); 

        //turn off the led at the tail position 
        drawPixel(snake_body[4]._x,snake_body[4]._y,LED_OFF); 

        //turn on the other LEDS 
        for (int i = 0; i < 4; i++) 
        { 
            drawPixel(snake_body[i]._x,snake_body[i]._y,snake_color); 
        }

        writeDisplay(); 

        last_update = millis(); 

    }
}