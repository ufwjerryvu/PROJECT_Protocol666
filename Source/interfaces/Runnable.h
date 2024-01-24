#pragma once

#include <Systems.h>

#include <Direction.h>

class Runnable
{
private:
    bool running;
    int speed;
    
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Runnable(int speed);
    ~Runnable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setRunning(bool running);
    bool isRunning();
    

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void 

    virtual void move() = 0;
    virtual void update() = 0;
};