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
    /*
    NOTE:
        - Request a specific frame in the sequence.
    */
    if (index < 0 || index >= this->frames.size())
    {
        return NULL;
    }

    return this->frames[index];
}

/*
SECTION 3: OTHER METHODS
*/
bool Animation::increment()
{
    /*
    NOTE:
        - This function returns `true` if the whole sequence has been completed
        and `false` if otherwise. Resets the counter, too.
    */
    this->counter++;

    if (this->counter >= this->interval)
    {
        this->index++;
        this->counter = 0;
    }
    /*
    NOTE:
        - Exceeds the the size of the list then we reset the index.
    */
    if (this->index >= this->frames.size())
    {
        this->reset();
        return true;
    }

    return false;
}

void Animation::reset()
{
    /*
    NOTE:
        - Resets all the counters to zero except the interval.
    */
    this->index = 0;
    this->counter = 0;
}