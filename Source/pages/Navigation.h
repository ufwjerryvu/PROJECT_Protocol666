/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#pragma once

#include <Systems.h>

class Master;

class Navigation
{
private:
    Master *context;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Navigation();
    Navigation(Master *context);
    ~Navigation();

    /*
    SECTION 2: GETTERS (AND MAYBE, SETTERS)
    */
    Master *getContext();
    
    /*
    SECTION 3: OTHER METHODS
    */
    virtual void update() = 0;
    virtual void render() = 0;
};