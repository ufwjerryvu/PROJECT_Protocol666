#pragma once

#include <Systems.h>

#include <Moveable.h>

class Runnable : virtual public Moveable
{
private:
    bool running = false;
    int speed;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Runnable();
    ~Runnable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setRunning(bool running);
    bool isRunning();

    void setSpeed(int speed);
    int getSpeed();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void run() = 0;

    virtual void move() = 0;
    virtual void update() = 0;
};