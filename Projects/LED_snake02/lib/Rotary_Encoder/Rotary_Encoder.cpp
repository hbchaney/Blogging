#include "Rotary_Encoder.hpp"

RotaryEncoder::RotaryEncoder(int pin1, int pin2, int sw) : in_pin1{pin1}, in_pin2{pin2}, button_pin{sw}, TRANS{0,-1,1,14,1,0,14,-1,-1,14,0,1,14,1,-1,0} 
{
    /*
    first and second are the turn pins, last is the button pin 
    */
} 

RotaryEncoder::~RotaryEncoder() {} 

void RotaryEncoder::setup() { 

    pinMode(in_pin1,INPUT_PULLUP); 
    pinMode(in_pin2,INPUT_PULLUP); 
    pinMode(button_pin,INPUT_PULLUP); 

    l = digitalRead(in_pin1);
    r = digitalRead(in_pin2);  

}

int RotaryEncoder::check_increment() { 
    //returns 1 or -1 
    l = digitalRead(in_pin1);
    r = digitalRead(in_pin2);
    lrmem = ((lrmem & 0b00000011) << 2) + 2*l + r;
    lrsum = lrsum + TRANS[lrmem];
    /* encoder not in the neutral state */
    if(lrsum % 4 != 0) return(0);
    /* encoder in the neutral state */
    if (lrsum == 4) {
        lrsum=0;
        return(1);
        }
    if (lrsum == -4) {
        lrsum=0;
        return(-1);
        }
    /* lrsum > 0 if the impossible transition */
    lrsum=0;
    return(0);
}

int RotaryEncoder::check_button() { 
    //returns how long the button has been held down for 
    //might add in a delay after button presses of a certain length 

    //5 for short press, 7 for long press of two seconds, 10 for press held down for more than 5 seconds 

    //short button press triggered on the release of  
    //a button press less than 2000mills and greater than 25mills 
    if (digitalRead(button_pin) == LOW && button_toggle == false) { //button pushed down and toggle not triggered yet (starts timer)
        press_start = millis(); 
        button_toggle = true; 
        return 0; 
    }
    else if (digitalRead(button_pin) == HIGH && button_toggle == true) { // button released timer reset
        button_toggle = false;
        if (two_second == true ) { 
            two_second = false; 
            return 0; 
        }
        else if (five_second == true) { 
            five_second = false; 
            return 0; 
        }
        else if (press_start + 25 < millis()) { 
            return 5; 
        }

    }
    else if (press_start + 2000 < millis() && button_toggle == true) { 

        if (two_second == false && five_second == false) { 
            two_second = true; 
            return 7; 
        }
        else if (press_start + 5000 < millis() && five_second == false) { 
            //reset the time and untoggle the button 
            two_second = false; 
            five_second = true; 
            return 10; 
        }

    }
    return 0; 

}


void RotaryEncoder::loop_check() { 
    int button = check_button(); 
    int rotate = check_increment(); 
    if (button != 0) { 
        output_buffer = button;  
    }
    else if (rotate != 0) { 
        output_buffer = rotate; 
    }
}


int RotaryEncoder::pull_cache() { 
    int out = output_buffer; 
    output_buffer = 0; 
    return out; 
}

int RotaryEncoder::check_cache() { 
    return output_buffer; 
}