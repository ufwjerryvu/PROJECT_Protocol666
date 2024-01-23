/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/
#pragma once

#include <Systems.h>

#include <Pressable.h>
#include <Sprite.h>

class Button : public Sprite, public Pressable{
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Button();
    Button(Coordinates position, SDL_Texture* texture);
    ~Button();

    /*
    SECTION 2: OTHER FUNCTIONS
    */
    void update();
};