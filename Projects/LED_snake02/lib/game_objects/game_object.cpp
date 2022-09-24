#include "game_object.hpp"


Object::Object() 
{ 
    display_buffer= {-5,-5}; 
    off_buffer = {-5,-5}; 
    
}

Coord Object::pull_display_buffer() 
{ 
    Coord Coord_new = display_buffer; 
    display_buffer = Coord::nullcoord(); 
    return Coord_new; 
}

Coord Object::pull_off_buffer() 
{ 
    Coord Coord_new = off_buffer; 
    off_buffer = Coord::nullcoord(); 
    return Coord_new; 
}

void Object::loop_check() 
{ 
    update_display_buffer(); 
    update_off_buffer(); 
}
