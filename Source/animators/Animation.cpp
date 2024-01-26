#include "Animation.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Animation::Animation(vector<SDL_Texture *> frames)
{
    /*
    NOTE:
        - Set the frames carefully because we have to initialize
        a new animation object if we get the frames wrong.
    */
    this->frames = frames;
}

Animation::~Animation()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}
/*
SECTION 2: SETTERS AND GETTERS
*/
int Animation::getSize() { return this->frames.size(); }
SDL_Texture *Animation::getCurrentFrame() { return this->frames[this->index]; }
SDL_Texture *Animation::requestFrame(int index) { return this->frames[index]; }

/*
SECTION 3: OTHER METHODS
*/
void Animation::increment(){
    this->index++;

    /*
    NOTE:
        - Exceeds the the size of the list then
        we reset the index.
    */
    if(this->index >= this->frames.size()){
        this->reset();
    }
}

void Animation::reset() { this->index = 0; }