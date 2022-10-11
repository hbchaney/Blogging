#include "EepromUploader.hpp"

times::times() {}
times::~times() {} 

void times::begin() 
{ 
    EEPROM.get(mem_address_diptime,mem_address_diptime);
    EEPROM.get(mem_address_holdtime,hold_time); 
    EEPROM.get(mem_address_up_time,up_time); 
}

void times::reset_times()
{ 
    EEPROM.put(mem_address_diptime,dip_time); 
    EEPROM.put(mem_address_holdtime,hold_time); 
    EEPROM.put(mem_address_up_time,up_time); 
}



