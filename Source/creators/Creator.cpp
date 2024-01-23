#include "Creator.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Creator::Creator(){
    /*
    NOTE:
        - Empty, permanently.
    */
}

Creator::~Creator(){
    /*
    NOTE:
        - Empty, permanently.
    */
}

/*
SECTION 2: CREATOR FUNCTIONS
*/
Button Creator::createButton(SDL_Renderer *renderer, string name, Coordinates position)
{
    FileHandler file = FileHandler();
    string types[] = {"idle", "hover", "pressed"};
    map<string, SDL_Texture *> animation;

    for (string type : types)
    {
        string path = "Assets/Sprite/Button/" + name + "_" + type + ".png";
        animation[type] = file.loadTexture(renderer, path);
    }

    return Button(position, animation);
}