#include "Button.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Button::Button(){
    /*
    NOTE:
        - Do not use.
    */
}

Button::Button(Coordinates position, SDL_Texture* texture)
    : Sprite(position, texture), Pressable(){
    /*
    NOTE:
        - Using the default constructors.
    */
}

Button::~Button(){
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

void Button::update(){
    /*
    TEMPORARY:
        - Empty, for now.
    */
}