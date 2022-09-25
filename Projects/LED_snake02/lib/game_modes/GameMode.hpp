#pragma once 
#include "Loop_Element.hpp"
#include "Adafruit_LEDBackpack.h"

/* 
Game mode abstract base 
at the highest level it requires that a mode has a start up function
requries a game to take in non zero inputs and requries the use of loops 

a mode manager will be responsible for switching between modes 
and placing the non mode switch inputs into the mode 
*/

class GameMode : public LoopElement,
{
    protected:
    Adafruit_BicolorMatrix* disp; //pointer to the display all 
};