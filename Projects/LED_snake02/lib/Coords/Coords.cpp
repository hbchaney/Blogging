#include "Coords.hpp"

const Coord Coord::nullCoord {-5,-5};

Coord::Coord() 
{ 

}

bool Coord::operator==(const Coord& A) const
{ 
    if (A._x == _x && A._y == _y) 
    { 
        return 1; 
    }
    else 
    { 
        return 0; 
    }
}

bool Coord::operator!=(const Coord& A) const 
{    
    return ~(*this == A); 
}

Coord::Coord(int x_val, int y_val) 
{ 
    _x = static_cast<short>(x_val); 
    _y = static_cast<short>(y_val); 
}

void Coord::operator=(const Coord& A) 
{ 
    _x = A._x;
    _y = A._y;
}
