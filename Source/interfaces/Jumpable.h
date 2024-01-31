#pragma once

#include <Systems.h>

#include <Moveable.h>
#include <Verticality.h>

class Jumpable : virtual public Moveable, virtual public Verticality
{
private:
    bool jumping = false;
    int velocity;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Jumpable();
    ~Jumpable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setJumping(bool jumping);
    bool isJumping();
    void setInitialVelocity(int velocity);
    int getInitialVelocity();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void jump() = 0;
    
    virtual void move() = 0;
    virtual void update() = 0;
};