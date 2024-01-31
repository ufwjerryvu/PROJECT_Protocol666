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
void Verticality::setCounter(int counter) { this->counter = counter; }
void Verticality::setInterval(int interval) { this->interval = interval; }

int Verticality::getVelocity() { return this->velocity; }
int Verticality::getCounter() { return this->counter; }
int Verticality::getInterval() { return this->interval; }

/*
SECTION 3: OTHER METHODS
*/
bool Verticality::increment()
{
    /*
    NOTE:
        - Function increments the counter and if the counter
        has reached the updating interval then we return `true`
        and `false` if otherwise. This signals whether we need
        to update a state.
    */
    this->counter++;

    return this->counter > this->interval;
}

void Verticality::reset()
{
    /*
    NOTE:
        - Resets the counter.
    */
    this->counter = 0;
}