#pragma once

#include <Systems.h>

#include <Moveable.h>

class Knockbackable : virtual public Moveable
{
private:
    bool knockbacked = false;
    int speed;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Knockbackable();
    ~Knockbackable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setKnockback(bool knockbacked);
    bool isKnockbacked();
    void setSpeed(int speed);
    int getSpeed();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void knockback() = 0;
    
    virtual void move() = 0;
    virtual void update() = 0;
};