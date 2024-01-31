#pragma once

#include <Systems.h>

class Matrix
{
private:
    int width;
    int height;
    vector<vector<SDL_Texture *>> blocks;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Matrix();
    virtual ~Matrix() = 0;

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setDiscreteWidth(int width);
    void setDiscreteHeight(int height);
    void setSetupBlocks(vector<vector<SDL_Texture *>> blocks);

    int getDiscreteWidth();
    int getDiscreteHeight();
    vector<vector<SDL_Texture *>> getSetupBlocks();
};