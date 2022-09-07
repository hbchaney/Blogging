
#ifndef STATE_BUTTON 
#define STATE_BUTTON 

#include "Loop_elem.hpp"
#include <Arduino.h>

class StateButton : public LoopElement {

    int pin_num; // pin that the button is attached to 
    short states; // how many states you want the button to cycle through 
    short current; // the current state of the button 
    unsigned long last_push; // to manage how often the button is pushed 
    bool down; //whether or not the button was held down 

    //increases the state by one 
    void increment_state (void); 

    public: 

    //initialize with the pin and the number of states 
    StateButton (int pin, short num_states); 
    ~StateButton ();

    //intialize the button 
    void setup (void); 

    //return the current state
    short current_state (void); 

    //check for button press and incrament the state if the press has happened recently 
    void loop_check(void) override; 
};



#endif