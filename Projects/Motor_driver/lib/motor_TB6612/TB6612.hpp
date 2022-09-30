#pragma once 
#include <Arduino.h>

class TB6612 
{ 
    int motor_pin_1; 
    int motor_pin_2; 
    int speed_pin; 
    int standby_pin; 

    int speed = 0; 

    bool running; 
    bool direction; //1 for motor_pin_1 high, 0 for motor_pin_2 high


    public: 
    //set pins for the motor driver 
    TB6612 (int mp1 = 2,int mp2 = 3,int spdpin = 5,int stby=4); 

    //intialize the motor 
    void begin(); 

    //pause the motor 
    void stop(); 

    //play the motor
    void start(); 

    //set motor speed
    void set_speed(int); //int between 0 and 255 

    //change motor direction 
    void reverse(); 


};