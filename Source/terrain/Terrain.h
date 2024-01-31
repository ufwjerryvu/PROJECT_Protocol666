#pragma once 

#include <Systems.h>

#include <Sprite.h>

class Terrain{
private:
    vector<vector<Sprite>> assembled;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Terrain();
    ~Terrain();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    vector<vector<Sprite>> getAssembled();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void assemble() = 0;
};