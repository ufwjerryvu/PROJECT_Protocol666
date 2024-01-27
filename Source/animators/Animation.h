#pragma once

#include <Systems.h>

class Animation
{
private:
    int index = 0;
    int count = 0;
    int interval;

    vector<SDL_Texture *> frames;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Animation();
    ~Animation();
    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setFrames(vector<SDL_Texture*> frames);
    void setInterval(int interval);
    int getSize();
    SDL_Texture *getCurrentFrame();
    SDL_Texture *requestFrame(int index);

    /*
    SECTION 3: OTHER METHODS
    */
    void increment();
    void reset();
};