#pragma once

#include <Systems.h>

#include <Coordinates.h>
#include <Sprite.h>
#include <Runnable.h>
#include <Rollable.h>
#include <Jumpable.h>
#include <Fallable.h>
#include <Animation.h>
#include <Animator.h>

class Gameplay;

class Character : public Sprite, public Runnable, 
        public Jumpable, public Fallable
{
private:
    Gameplay *context;
    Animator<string> animator;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Character(Gameplay *context);
    ~Character();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setAnimator(Animator<string> animator);
    Gameplay *getContext();
    Animator<string> &getAnimator();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void run() = 0;
    virtual void jump() = 0;
    void fall();
    virtual void move() = 0;

    virtual void update() = 0;
    void render();
};