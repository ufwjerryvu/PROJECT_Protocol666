#pragma once

#include <Systems.h>

#include <Coordinates.h>
#include <Sprite.h>
#include <Runnable.h>

class Gameplay;

class Character : public Sprite, public Runnable
{
private:
    Gameplay *context;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Character(Gameplay *context);
    ~Character();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    Gameplay *getContext();
    
    /*
    SECTION 3: OTHER METHODS
    */
    virtual void run() = 0;
    virtual void move() = 0;

    virtual void update() = 0;
    void render();
};