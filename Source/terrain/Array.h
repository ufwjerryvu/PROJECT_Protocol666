#pragma once

#include <Systems.h>

class Array{
private:
    int size;
    bool horizontal;
    vector<SDL_Texture*> blocks;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Array();
    ~Array();
    
    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setSize(int size);
    void orientVertical();
    void orientHorizontal();
    void setSetupBlocks(vector<SDL_Texture*> blocks);

    int getSize();
    bool isHorizontal();
    bool isVertical();
    vector<SDL_Texture*> getSetupBlocks();
};