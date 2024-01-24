#pragma once

#include <Systems.h>

class FileHandler
{
public:
    /*
    SECTION: UNIT LOADING
    */
    SDL_Texture *loadTexture(SDL_Renderer *renderer, string path);
};
