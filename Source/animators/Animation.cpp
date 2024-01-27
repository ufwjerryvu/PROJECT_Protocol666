#include "Animation.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Animation::Animation()
{
    /*
    NOTE:
        - What do I put here?
    */
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
void Animation::setFrames(vector<SDL_Texture *> frames) { this->frames = frames; }
void Animation::setInterval(int interval) { this->interval = interval; }
int Animation::getSize() { return this->frames.size(); }
SDL_Texture *Animation::getCurrentFrame() { return this->frames[this->index]; }
SDL_Texture *Animation::requestFrame(int index)
{
    if (index < 0 || index >= this->frames.size())
    {
        return NULL;
    }

    return this->frames[index];
}

/*
SECTION 3: OTHER METHODS
*/
void Animation::increment()
{
    this->count++;

    if(this->count >= this->interval){
        this->index++;
        this->count = 0;
    }
    /*
    NOTE:
        - Exceeds the the size of the list then
        we reset the index.
    */
    if (this->index >= this->frames.size())
    {
        this->reset();
    }
}

void Animation::reset() { this->index = 0; }