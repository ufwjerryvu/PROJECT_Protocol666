#pragma once

#include <Systems.h>

class Verticality
{
private:
    int velocity = 0;
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
    void setCounter(int counter);
    void setInterval(int interval);
    
    int getVelocity();
    int getCounter();
    int getInterval();

    /*
    SECTION 3: OTHER METHODS
    */
    bool increment();
    void reset();

    virtual void move() = 0;
    virtual void update() = 0;
};