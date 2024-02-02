#pragma once

#include <Systems.h>

#include <Character.h>
#include <Runnable.h>
#include <Ground.h>
#include <Platform.h>

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
    bool collide(vector<Ground *> &args);
    bool collide(vector<Platform *> &args);

    void run();
    void roll();
    void jump();
    void move();

    void update();
};