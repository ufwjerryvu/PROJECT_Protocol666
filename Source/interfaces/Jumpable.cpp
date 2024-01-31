#include "Jumpable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Jumpable::Jumpable()
{
    /*
    NOTE:
        - Empty, probably for good.
    */
}
Jumpable::~Jumpable()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
void Jumpable::setJumping(bool jumping) { this->jumping = jumping; }
bool Jumpable::isJumping() { return this->jumping; }
void Jumpable::setInitialVelocity(int velocity) { this->velocity = velocity; }
int Jumpable::getInitialVelocity() { return this->velocity; }