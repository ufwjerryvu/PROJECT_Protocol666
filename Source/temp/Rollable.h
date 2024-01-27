#pragma once

#include <Systems.h>

#include <Direction.h>

class Rollable
{
private:
    bool rolling;
    int speed;
    
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Rollable(int speed);
    ~Rollable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setRunning(bool running);
    bool isRunning();
    

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void left();
    virtual void right();

    virtual void move() = 0;
    virtual void update() = 0;
};