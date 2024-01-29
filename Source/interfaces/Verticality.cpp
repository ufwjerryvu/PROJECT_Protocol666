#include "Verticality.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Verticality::Verticality()
{
    /*
    NOTE:
        - Empty, probably for good.
    */
}

Verticality::~Verticality()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}
/*
SECTION 2: SETTERS AND GETTERS
*/
void Verticality::setVelocity(int velocity) { this->velocity = velocity; }
int Verticality::getVelocity() { return this->velocity; }

void Verticality::setInterval(int interval) { this->interval = interval; }
int Verticality::getInterval() { return this->interval; }

/*
SECTION 3: OTHER METHODS
*/
bool Verticality::increment(){
    /*
    NOTE:
        - Function increments the counter and if the counter
        has reached the updating interval then we return `true`
        and `false` if otherwise. This signals whether we need
        to update a state.
    */
    this->counter++;

    if(this->counter >= this->interval){
        this->counter = 0;
        return true;
    }
    return false;
}