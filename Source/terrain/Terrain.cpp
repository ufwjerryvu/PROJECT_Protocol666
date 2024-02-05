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
void Terrain::setAssembled(vector<vector<Sprite>> assembled)
{
    this->assembled = assembled;
}

void Terrain::setRelativePosition(Coordinates camera)
{
    /*
    NOTE:
        - The attribute `assembled` is a matrix that  contains Sprite objects.
        Therefore, in order to set the new ender coordinates of all the objects
        we need to run a nested loop.
    */
    for (int i = 0; i < this->assembled.size(); i++)
    {
        for (int j = 0; j < this->assembled[i].size(); j++)
        {
            this->assembled[i][j].setRelativePosition(camera);
        }
    }
}

Gameplay *Terrain::getContext() { return this->context; }

int Terrain::getTopBound()
{
    /*
    NOTE:
        - Since terrain types inherit from `Sprite` but gives no singular texture,
        it needs to give it's own implementation of these methods. Here, we're us-
        ing the top left block.
    */
    if (this->assembled.size())
    {
        return this->assembled[0][0].getTopBound();
    }
    return 0;
}

int Terrain::getBottomBound()
{
    /*
    NOTE:
        - Gets the bottom right block and gets the bottom bound from there.
    */
    if (this->assembled.size())
    {
        return this->assembled[this->assembled.size() - 1]
                              [this->assembled.size() - 1]
                                  .getBottomBound();
    }
    return 0;
}

int Terrain::getLeftBound(){
    /*
    NOTE:
        - Gets the left bound using the top left block.
    */
    if (this->assembled.size())
    {
        return this->assembled[0][0].getTopBound();
    }
    return 0;    
}

int Terrain::getRightBound(){
    /*
    NOTE:
        - Gets the right bound using the bottom right block.
    */
    if (this->assembled.size())
    {
        return this->assembled[this->assembled.size() - 1]
                              [this->assembled.size() - 1]
                                  .getBottomBound();
    }
    return 0;  
}


/*
SECTION 3: OTHER METHODS
*/
void Terrain::render()
{
    /*
    NOTE:
        - We are just printing the matrix by row and column. Thus, using a nest-
        ed loop.
    */
    SDL_Renderer *renderer = this->getContext()->getContext()->getRenderer();

    for (vector<Sprite> row : assembled)
    {
        for (Sprite block : row)
        {
            block.render(renderer, true);
        }
    }
}
