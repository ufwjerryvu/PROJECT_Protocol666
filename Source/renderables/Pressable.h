/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#pragma once

#include <Systems.h>

class Pressable
{
private:
    bool hovering;
    bool pressed;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Pressable();
    ~Pressable();

    /*
    SECTION 2A: SETTERS
    */
    void setPressed(bool pressed);
    void setHovering(bool hovering);
    /*
    SECTION 2B: GETTERS
    */
    bool isPressed();
    bool isHovering();
};