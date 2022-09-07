
#ifndef STATE_BUTTON 
#define STATE_BUTTON 

class StateButton {

    int pin_num; // pin that the button is attached to 
    short states; // how many states you want the button to cycle through 
    short current; // the current state of the button 
    unsigned long last_push; // to manage how often the button is pushed 

    public: 

    //initialize with the pin and the number of states 
    StateButton (int pin, short num_states); 
    ~StateButton ();

    //increases state by one and returns the new state 
    short incrament_state (void); 

    //return the current state
    short current_state (void); 

    //check for button press and incrament the state if the press has happened recently 
    void loop_check(void); 


    
};



#endif