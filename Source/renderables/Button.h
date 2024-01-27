#pragma once

#include <Systems.h>

#include <Pressable.h>
#include <Sprite.h>

class Button : public Sprite, public Pressable{
private:
    map<string, SDL_Texture*> animation;
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Button();
    Button(Coordinates position, map<string, SDL_Texture*> animation);
    ~Button();

    /*
    SECTION 2: OTHER FUNCTIONS
    */
    void update();
};