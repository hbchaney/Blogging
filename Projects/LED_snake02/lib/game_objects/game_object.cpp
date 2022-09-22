#include "game_object.hpp"

bool Coord::operator=(Coord other) 
{ 
    if (other._x == _x && other._y == _y) 
    { 
        return 1; 
    }
    else 
    { 
        return 0; 
    }
}

Coord::Coord(int x_val, int y_val) 
{ 
    _x = static_cast<short>(x_val); 
    _y = static_cast<short>(y_val); 
}

Object::Object() 
{ 
    nullcoord = {-5,-5}; 
    display_buffer = nullcoord; 
    off_buffer = nullcoord; 
    
}

Coord Object::pull_display_buffer() 
{ 
    Coord Coord_new = display_buffer; 
    display_buffer = nullcoord; 
    return Coord_new; 
}

Coord Object::pull_off_buffer() 
{ 
    Coord Coord_new = off_buffer; 
    off_buffer = nullcoord; 
    return Coord_new; 
}

void Object::loop_check() 
{ 
    update_display_buffer(); 
    update_off_buffer(); 
}
