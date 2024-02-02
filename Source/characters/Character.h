#pragma once

#include <Systems.h>

#include <Coordinates.h>
#include <Sprite.h>
#include <Runnable.h>
#include <Rollable.h>
#include <Jumpable.h>
#include <Fallable.h>
#include <Collidable.h>
#include <Animation.h>
#include <Animator.h>
#include <Ground.h>

class Gameplay;

class Character : virtual public Sprite, virtual public Runnable,
        virtual public Jumpable, virtual public Fallable, 
        virtual public Collidable
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
    virtual bool collide(vector<Ground *> &args) = 0;
    // virtual bool collide(vector<Platform>& args) = 0;

    virtual void run() = 0;
    virtual void jump() = 0;
    void fall();
    virtual void move() = 0;

    virtual void update() = 0;
    void render();
};