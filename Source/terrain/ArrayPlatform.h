#pragma once

#include <Systems.h>

#include <Platform.h>
#include <Array.h>

class Gameplay;

class ArrayPlatform : virtual public Platform, virtual public Array{
private:
public: 
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    ArrayPlatform(Gameplay *context);
    ~ArrayPlatform();
    /*
    SECTION 2: SETTERS AND GETTERS
    */
    /*
    SECTION 3: OTHER METHODS
    */
    void assemble();
};