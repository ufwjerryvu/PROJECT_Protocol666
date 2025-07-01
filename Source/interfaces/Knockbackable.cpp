#include "Knockbackable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Knockbackable::Knockbackable()
{
    /*
    NOTE:
        - Empty, probably for good.
    */
}
Knockbackable::~Knockbackable()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
void Knockbackable::setKnockback(bool knockbacked) { this->knockbacked = knockbacked; }
bool Knockbackable::isKnockbacked() { return this->knockbacked; }
void Knockbackable::setSpeed(int speed) { this->speed = speed; }
int Knockbackable::getSpeed() { return this->speed; }