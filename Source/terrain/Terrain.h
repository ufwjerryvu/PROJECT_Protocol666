#pragma once

#include <Systems.h>

#include <Master.h>
#include <Sprite.h>

class Gameplay;

class Terrain : virtual public Sprite
{
private:
    Gameplay *context;
    vector<vector<Sprite>> assembled;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Terrain(Gameplay *context);
    ~Terrain();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setAssembled(vector<vector<Sprite>> assembled);
    void setRelativePosition(Coordinates camera);
    Gameplay *getContext();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void assemble() = 0;
    void render();
};