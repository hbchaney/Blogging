#include "TB6612.hpp"

TB6612::TB6612(int mp1,int mp2,int spdpin,int stby) : motor_pin_1{mp1}, 
                                                    motor_pin_2{mp2} , 
                                                    speed_pin{spdpin},
                                                    standby_pin{stby} {}


void TB6612::begin()
{ 
    pinMode(motor_pin_1,OUTPUT); 
    pinMode(motor_pin_2,OUTPUT); 
    pinMode(speed_pin,OUTPUT); 
    pinMode(standby_pin,OUTPUT);


    digitalWrite(motor_pin_1,HIGH); 
    digitalWrite(motor_pin_2,LOW); 
    analogWrite(speed_pin,0); 
    digitalWrite(standby_pin,HIGH); 
}

void TB6612::stop() 
{ 
    if (running) 
    { 
        analogWrite(speed_pin,0); 
        running = false; 
    }
}

void TB6612::start()
{ 
    if(~running) 
    { 
        analogWrite(speed_pin,speed);
        // Serial.println("stopping");
        running = true; 
    }
}

void TB6612::set_speed(int spd) 
{ 
    speed = spd; 
    if (running = true)
    {
      analogWrite(speed_pin,speed);  
    }
    
}

void TB6612::reverse() 
{ 
    if (direction) 
    { 
        digitalWrite(motor_pin_1,LOW); 
        digitalWrite(motor_pin_2,HIGH); 
        direction = 0; 
    }
    else 
    { 
        digitalWrite(motor_pin_1,HIGH); 
        digitalWrite(motor_pin_2,LOW); 
        direction = 1; 
    }
}