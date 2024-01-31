#include "Terrain.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Terrain::Terrain(){
    /*
    NOTE:
        - Empty, probably for good.
    */
}

Terrain::~Terrain(){
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
vector<vector<Sprite>> Terrain::getAssembled(){
    return this->assembled;
}

