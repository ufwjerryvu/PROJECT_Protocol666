#pragma once

#include <Systems.h>

#include <Platform.h>
#include <Matrix.h>

class Gameplay;

class MatrixPlatform : virtual public Platform, virtual public Matrix
{
private:
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    MatrixPlatform(Gameplay *context);
    ~MatrixPlatform();
    /*
    SECTION 2: SETTERS AND GETTERS
    */
    /*
    SECTION 3: OTHER METHODS
    */
    void assemble();
};