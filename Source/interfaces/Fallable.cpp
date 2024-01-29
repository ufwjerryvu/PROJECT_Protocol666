#include "Fallable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Fallable::Fallable(){
    /*
    NOTE:
        - Empty, probably for good.
    */
}
Fallable::~Fallable(){
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
void Fallable::setFalling(bool falling){this->falling = falling;}
void Fallable::setGravitationalAcceleration(int accel){this->acceleration = accel;}
void Fallable::setTerminalVelocity(int terminal){this->terminal = terminal;}

bool Fallable::isFalling(){return this->falling;}
int Fallable::getGravitationalAcceleration(){return this->acceleration;}
int Fallable::getTerminalVelocity(){return this->terminal;}
