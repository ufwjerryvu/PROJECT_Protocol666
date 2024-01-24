#pragma once

#include <Systems.h>

#include <Direction.h>

class Moveable
{
private:
    Direction facing;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Moveable();
    ~Moveable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setDirectionFacing(Direction direction);
    Direction getDirectionFacing();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void move() = 0;
    virtual void update() = 0;
};