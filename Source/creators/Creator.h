/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#include <Systems.h>

#include <FileHandler.h>

#include <Button.h>

class Creator
{
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Creator();
    ~Creator();

    /*
    SECTION 2: CREATOR FUNCTIONS
    */
    Button createButton(SDL_Renderer* renderer, string name, Coordinates position);
};