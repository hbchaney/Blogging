#pragma once 

//the EEPROM Uploader goes through the cycles of dip coating (dip time, hold time, up time) and
//stores the amount of times for each of these phases 

//after these are stored than a full cycle button can be pressed and the motor can go through each stage 

#include <EEPROM.h>

struct times
{ 
    unsigned long dip_time = 0; 
    unsigned long hold_time = 0; 
    unsigned long up_time = 0; 

    times(); 
    ~times(); 

    void begin();
    void reset_times(uint32_t, uint32_t, uint32_t);

    private: 
    //memory address locations for eeprom // should take up 4 locations 
    int mem_address_diptime = 0; //0,1,2,3 
    int mem_address_holdtime = 4; //4,5,6,7
    int mem_address_up_time = 8; //8,9,10,11

};