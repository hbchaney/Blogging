#include "EepromUploader.hpp"

times::times() {}
times::~times() {} 

void times::begin() 
{ 
    EEPROM.get(mem_address_diptime,mem_address_diptime);
    EEPROM.get(mem_address_holdtime,hold_time); 
    EEPROM.get(mem_address_up_time,up_time); 
}

void times::reset_times(uint32_t d_time, uint32_t h_time, uint32_t u_time)
{ 
    EEPROM.put(mem_address_diptime,d_time); 
    EEPROM.put(mem_address_holdtime,h_time); 
    EEPROM.put(mem_address_up_time,u_time); 
}



