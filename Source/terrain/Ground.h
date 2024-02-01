#pragma once

#include <Systems.h>

#include <Matrix.h>
#include <Terrain.h>

class Gameplay;

class Ground : virtual public Matrix, virtual public Terrain
{
private:
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Ground(Gameplay *context);
    ~Ground();
    /*
    SECTION 2: SETTERS AND GETTERS
    */

    /*
    SECTION 3: OTHER METHODS
    */
    void assemble();
};