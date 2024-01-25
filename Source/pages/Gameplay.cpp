#include "Gameplay.h"

#include <Master.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Gameplay::Gameplay()
{
    /*
    NOTE:
        - Do not use. Ever.
    */
}

Gameplay::Gameplay(Master *context)
{
    /*
    NOTE:
        - Context is set to the master as part of the navigation
        scheme.
    */
    this->context = context;
}
Gameplay::~Gameplay()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
Master *Gameplay::getContext() { return this->context; }
int Gameplay::getLevelWidth() { return this->lwidth; }
int Gameplay::getLevelHeight() { return this->lheight; }

/*
SECTION 3: OTHER METHODS
*/
void Gameplay::update()
{
}
void Gameplay::render()
{
}