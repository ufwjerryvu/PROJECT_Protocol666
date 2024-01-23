#include "Navigation.h"

/*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Navigation::Navigation()
{
    /*
    NOTE:
        - Do not use.
    */
}

Navigation::Navigation(Master *context)
{
    /*
    NOTE:
        - Sets the context to which the navigation will
        manipulate.
    */
    this->context = context;
}

Navigation::~Navigation()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: GETTERS (AND MAYBE, SETTERS)
*/
Master *Navigation::getContext() { return this->context; }
