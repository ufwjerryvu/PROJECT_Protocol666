#include "Rollable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Rollable::Rollable()
{
    /*
    NOTE:
        - The rolling state is set to `false`. However, the speed
        must be specified by the builder or creator class.
    */
}

Rollable::~Rollable()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
void Rollable::setRolling(bool rolling) { this->rolling = rolling; }
bool Rollable::isRolling() { return this->rolling; }
void Rollable::setSpeed(int speed) { this->speed = speed; }
int Rollable::getSpeed() { return this->speed; }