#pragma once

#include <Systems.h>

class Coordinates
{
private:
    int x;
    int y;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Coordinates();
    Coordinates(int x, int y);
    ~Coordinates();

    /*
    SECTION 2A: SETTERS
    */
    void setX(int x);
    void setY(int y);
    void setCoordinates(int x, int y);

    /*
    SECTION 2B: GETTERS
    */
    int getX() const;
    int getY() const;
};