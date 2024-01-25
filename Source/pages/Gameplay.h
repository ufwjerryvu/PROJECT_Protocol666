#pragma once

#include <Systems.h>

class Master;

class Gameplay
{
private:
    Master *context;

    int lwidth = 1400;
    int lheight = 2800;
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Gameplay();
    Gameplay(Master *context);
    ~Gameplay();

    /*
    SECTION 2: GETTER AND SETTER METHODS
    */
    Master* getContext();
    int getLevelWidth();
    int getLevelHeight();

    /*
    SECTION 3: OTHER METHODS
    */
    void update();
    void render();
};