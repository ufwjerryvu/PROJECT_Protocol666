#pragma once

#include <Systems.h>

class Verticality
{
private:
    int velocity;
    int counter = 0;
    int interval;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Verticality();
    ~Verticality();
    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setVelocity(int velocity);
    int getVelocity();

    void setInterval(int interval);
    int getInterval();

    /*
    SECTION 3: OTHER METHODS
    */
    bool increment();

    virtual void move() = 0;
    virtual void update() = 0;
};