#pragma once

#include <Systems.h>

class Animation
{
private:
    int index;
    vector<SDL_Texture *> frames;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Animation(vector<SDL_Texture *> frames);
    ~Animation();
    /*
    SECTION 2: SETTERS AND GETTERS
    */
    int getSize();
    SDL_Texture *getCurrentFrame();
    SDL_Texture *requestFrame(int index);

    /*
    SECTION 3: OTHER METHODS
    */
    void increment();
    void reset();
};