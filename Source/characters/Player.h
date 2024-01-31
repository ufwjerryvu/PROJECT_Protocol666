#pragma once

#include <Systems.h>

#include <Character.h>
#include <Runnable.h>

class Gameplay;

class Player : public Character, public Rollable
{
private:
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Player(Gameplay *gameplay);
    ~Player();

    /*
    SECTION 2: OTHER METHODS
    */
    void run();
    void roll();
    void jump();
    void move();

    void update();
};