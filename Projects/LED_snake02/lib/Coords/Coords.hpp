#pragma once 

struct Coord 
{ 
    short _x= -5;
    short _y= -5; 

    static const Coord nullCoord; 
    Coord(); 
    void operator=(const Coord&); 
    bool operator==(const Coord&) const; 
    bool operator!=(const Coord&) const; 
    Coord(int,int); 

};