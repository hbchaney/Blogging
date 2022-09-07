
#include "State_button.hpp"

StateButton::StateButton (int pin, short num_states) : pin_num{pin}, states{num_states} { 
    current = 0; 
    last_push = millis(); 
} 

StateButton::~StateButton () {} 

void StateButton::setup_button (void) { 
    pinMode(pin_num,INPUT_PULLUP); 
}


void StateButton::increment_state(void) { 
    current = (current + 1) % states; 
}

short StateButton::current_state(void) { 
    return current; 
}

void StateButton::loop_check(void) { 
    //determine if the button has been pressed recently 

    if (last_push + 100 < millis()) { 
        
        //check if the button is down
        if (digitalRead(pin_num) == HIGH && down == true) { 
                last_push = millis(); 
                increment_state(); 
                down = false; 
        }
        else if (digitalRead(pin_num) == LOW && down == false)
        {
            down = true; 
        }

    }
}