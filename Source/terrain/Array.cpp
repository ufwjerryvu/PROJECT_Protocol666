#include "Array.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Array::Array()
{
    /*
    NOTE:
        - Empty, probably for good.
    */
}
Array::~Array()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}
/*
SECTION 2: SETTERS AND GETTERS
*/
void Array::setSize(int size) { this->size = size; }
void Array::orientVertical() { this->horizontal = false; }
void Array::orientHorizontal() { this->horizontal = true; }
void Array::setSetupBlocks(vector<SDL_Texture *> blocks)
{
    /*
    NOTE:
        - Here's the thing. We need exactly three textures for this type of constr-
        uction. The first element will be at the left/top edge. The last element 
        will be at the right/bottom edge. The middle one will be filled in-between
        the first and last. 
    */   
    const int REQUIRED = 3;
    if(blocks.size() != REQUIRED){
        cerr << "Error: setup blocks must have exactly three textures." << endl;
        assert(false);
    }

    this->blocks = blocks;
}

int Array::getSize() { return this->size; }
bool Array::isHorizontal() { return this->horizontal; }
bool Array::isVertical() { return !this->horizontal; }
vector<SDL_Texture *> Array::getSetupBlocks() { return this->blocks; }