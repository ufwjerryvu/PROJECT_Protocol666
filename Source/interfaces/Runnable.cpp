#include "Runnable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Runnable::Runnable()
{
    /*
    NOTE:
        - The running state is set to `false`. However, the speed
        must be specified by the builder or creator class.
    */
}

Runnable::~Runnable()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
void Runnable::setRunning(bool running) { this->running = running; }
bool Runnable::isRunning() { return this->running; }
void Runnable::setSpeed(int speed) { this->speed = speed; }
int Runnable::getSpeed() { return this->speed; }