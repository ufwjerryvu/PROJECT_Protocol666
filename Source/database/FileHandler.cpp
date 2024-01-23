#include "FileHandler.h"

/*
SECTION: UNIT LOADING
*/
SDL_Texture *FileHandler::loadTexture(SDL_Renderer *renderer, string path)
{
    /*
    NOTE:
        - Standard texture-loading method.
    */
    SDL_Texture *temp = IMG_LoadTexture(renderer, path.c_str());

    if (temp == NULL)
    {
        cerr << "Error: cannot load texture from the specified path." << endl;
        assert(false);
    }

    return temp;
}