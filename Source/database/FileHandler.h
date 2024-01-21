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

/*
SECTION: UNIT LOADING
*/
SDL_Texture* FileHandler::loadTexture(SDL_Renderer *renderer, string path)
{
    /*
    NOTE:
        - Standard texture-loading method.
    */
    SDL_Texture *temp = IMG_LoadTexture(renderer, path.c_str());

    if (temp == NULL)
    {
        throwException("Error: cannot load texture from the specified path.");
    }

    return temp;
}