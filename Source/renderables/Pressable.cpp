#include "Pressable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Pressable::Pressable()
{
    /*
    NOTE:
        - Initially set to `false` for both.
    */
    this->setPressed(false);
    this->setHovering(false);
}

Pressable::~Pressable()
{
    /*
    NOTE:
        - Empty, for now.
    */
}

/*
SECTION 2A: SETTERS
*/
void Pressable::setPressed(bool pressed)
{
    this->pressed = pressed;
    if (pressed)
    {
        this->hovering = false;
    }
}
void Pressable::setHovering(bool hovering)
{
    this->hovering = hovering;
    if(hovering){
        this->pressed = false;
    }
}
/*
SECTION 2B: GETTERS
*/
bool Pressable::isPressed() { return pressed; }
bool Pressable::isHovering() { return hovering; }