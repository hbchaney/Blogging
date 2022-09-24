#include <Arduino.h>
#include <Wire.h> 
#include "snake.hpp"
#include "Rotary_Encoder.hpp" 

class SnakeGame : public LoopElement , Adafruit_BicolorMatrix
{ 
    RotaryEncoder* re; 
    Snake snk; 
    unsigned long last_update = 0, frame_delay= 150; 

    void draw_Coords(Object*);

    public: 

    
    SnakeGame(RotaryEncoder*); 
    bool begin(uint8_t, TwoWire *); 
    void loop_check() override; 
    void debug() 
    { 
      drawPixel(5,5,LED_RED); 
      writeDisplay(); 
    }

};

SnakeGame::SnakeGame(RotaryEncoder* re1) : re{re1} 
{
  snk.object_color = LED_GREEN; 
  setBrightness(7); 
  clear(); 
} 

bool SnakeGame::begin(uint8_t _addr = 0x70, TwoWire *theWire = &Wire) 
{ 
    return Adafruit_BicolorMatrix::begin(_addr,&Wire); 
}

void SnakeGame::draw_Coords(Object* ob_ptr) 
{ 
    //off values
    Coord off = ob_ptr->pull_off_buffer();
    //on values
    Coord on = ob_ptr->pull_display_buffer(); 

    drawPixel(off._x,off._y,LED_OFF);
    drawPixel(on._x,on._y,ob_ptr->object_color);  
    writeDisplay(); 
} 

void SnakeGame::loop_check() 
{ 
  //first check to see if the snakes position needs to be updated 
  if (last_update + frame_delay < millis())
  { 
    draw_Coords(&snk); 
    snk.loop_check(); 
    last_update = millis(); 
  }

  //check for re inputs 
  int in = re->pull_cache();
  if (in == 1 || in == -1) 
  { 
      snk.change_direction(in); 
  }
  re->loop_check(); 

}
RotaryEncoder re1 {9,10,11};
SnakeGame sg{&re1}; 



void setup() 
{ 
    sg.begin(); 
}

void loop() 
{
  // put your main code here, to run repeatedly:
  sg.loop_check();
  sg.debug(); 
   

}