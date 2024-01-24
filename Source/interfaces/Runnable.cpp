#include "Moveable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Moveable::Moveable(){
    /*
    NOTE:
        - Empty, for good.
    */
}
Moveable::~Moveable(){
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
void Moveable::setDirectionFacing(Direction direction)
{
    this->facing = direction;
}

Direction Moveable::getDirectionFacing()
{
    return this->facing;
}