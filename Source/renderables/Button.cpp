#include "Button.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Button::Button()
{
    /*
    NOTE:
        - Do not use.
    */
}

Button::Button(Coordinates position, map<string, SDL_Texture *> animation)
    : Sprite(position, NULL), Pressable()
{
    /*
    NOTE:
        - Using the default constructors. However, we
        set it to `NULL` initially and then reset it
        to the idle frame.
    */
    this->setTexture(animation["idle"]);

    this->animation = animation;
}

Button::~Button()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

void Button::update()
{
    /*
    NOTE:
        - Targeted animation. We store this simply in a
        map.
    */
    if (this->isPressed())
    {
        this->setTexture(animation["pressed"]);
    }
    else if (this->isHovering())
    {
        this->setTexture(animation["hover"]);
    }
    else
    {
        this->setTexture(animation["idle"]);
    }
}