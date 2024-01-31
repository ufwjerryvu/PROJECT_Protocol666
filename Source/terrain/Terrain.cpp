#include "Terrain.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Terrain::Terrain(Gameplay *context)
{
    /*
    NOTE:
        - Just stores the context to know about other things.
    */
    this->context = context;
}

Terrain::~Terrain()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
Gameplay *Terrain::getContext() { return this->context; }

vector<vector<Sprite>> Terrain::getAssembled()
{
    return this->assembled;
}
