#include "ArrayPlatform.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
ArrayPlatform::ArrayPlatform(Gameplay *context) : Platform(context), Terrain(context)
{
    /*
    NOTE:
        - Empty, probably for good.
    */
}

ArrayPlatform::~ArrayPlatform()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/

/*
SECTION 3: OTHER METHODS
*/
void ArrayPlatform::assemble()
{
    /*
    TEMPORARY:
        - We've only accounted for horizontal array platforms but not vertical array
        platforms. We might need to fix this later on.
    */
    vector<vector<Sprite>> assembled;

    const int LEFT = 0, CENTER = 1, RIGHT = 2;

    /*
    NOTE:
        - The platform is one block tall so we only need to think one-dimensionally.
    */
    vector<Sprite> row;
    for (int index = 0; index < this->getSize(); index++)
    {
        /*
        NOTE:
            - This whole thing is similar to how we instantiate `Ground` objects.
        */
        Coordinates position = this->getAbsolutePosition();
        if (index == 0)
        {
            /*
            NOTE:
                - This is to get the leftmost texture.
            */
            row.push_back(Sprite(Coordinates(position.getX(), position.getY()),
                                 this->getSetupBlocks()[LEFT]));
        }
        else if (index == this->getSize() - 1)
        {
            /*
            NOTE:
                - This is to get the rightmost texture.
            */
            row.push_back(Sprite(Coordinates(row[index - 1].getRightBound(),
                                             position.getY()),
                                 this->getSetupBlocks()[RIGHT]));
        }
        else
        {
            /*
            NOTE:
                - This is to get all the textures in between.
            */
            row.push_back(Sprite(Coordinates(row[index - 1].getRightBound(),
                                             position.getY()),
                                 this->getSetupBlocks()[CENTER]));
        }
    }

    assembled.push_back(row);

    /*
    NOTE:
        - The Terrain namespace has to be invoked because the class somehow 
        doesn't recognize that the function was being overridden.
    */
    Terrain::setAssembled(assembled);
}