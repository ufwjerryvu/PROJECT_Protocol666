#pragma once

#include <Systems.h>

#include <Moveable.h>

class Rollable : virtual public Moveable
{
private:
    bool rolling = false;
    int speed;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Rollable();
    ~Rollable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setRolling(bool rolling);
    bool isRolling();

    void setSpeed(int speed);
    int getSpeed();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void run() = 0;

    virtual void move() = 0;
    virtual void update() = 0;
};