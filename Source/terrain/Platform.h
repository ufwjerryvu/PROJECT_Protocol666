#pragma once

#include <Systems.h>

#include <Terrain.h>

class Platform : virtual public Terrain
{
private:
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Platform(Gameplay *context);
    ~Platform();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    /*
    NOTE:
        - Empty.
    */

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void assemble() = 0;
};