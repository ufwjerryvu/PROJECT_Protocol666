#pragma once

#include <Systems.h>

class Master;

class Gameplay
{
private:
    Master *context;
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