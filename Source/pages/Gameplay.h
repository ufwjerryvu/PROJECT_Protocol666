/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/
#pragma once

#include <Systems.h>

#include <Sprite.h>
#include <Coordinates.h>
#include <FileHandler.h>

class Master;

class Gameplay
{
private:
    Master *context;

    Sprite test;
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Gameplay();
    Gameplay(Master *context);
    ~Gameplay();

    /*
    SECTION 2: OTHER METHODS
    */
    void update();
    void render();
};