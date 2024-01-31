#pragma once

#include <Systems.h>

#include <Moveable.h>
#include <Verticality.h>

class Fallable : virtual public Moveable, virtual public Verticality
{
private:
    bool falling = false;
    int acceleration;
    int terminal;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Fallable();
    ~Fallable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setFalling(bool falling);
    void setGravitationalAcceleration(int accel);
    void setTerminalVelocity(int terminal);

    bool isFalling();
    int getGravitationalAcceleration();
    int getTerminalVelocity();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void fall() = 0;
    
    virtual void move() = 0;
    virtual void update() = 0;
};