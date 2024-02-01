#include "Ground.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Ground::Ground(Gameplay *context) : Terrain(context)
{
    /*
    NOTE:
        - Probably empty, for good.
    */
}
Ground::~Ground()
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
void Ground::assemble()
{
    /*
    NOTE:
        - This function doesn't take in any parameters because it utilizes the
        base class's attributes instead.
    */
    vector<vector<Sprite>> assembled;

    /*
    NOTE:
        - These constants are assuming that the setup textures are configured as
        3x3. That is, `blocks` is a 3x3 two-dimensional vector or matrix, if you
        will. This will be enforced.
    */
    const int LEFT = 0, CENTER = 1, RIGHT = 2;
    const int TOP = 0, MIDDLE = 1, BOTTOM = 2;

    /*
    NOTE:
        - Checking if the texture blocks are empty.
    */
    if (!this->Matrix::getSetupBlocks().size())
    {
        cerr << "Error: the two-dimensional vector for setup textures is empty." << endl;
        assert(false);
    }

    /*
    NOTE:
        - This is the part where the matrix `assembled` gets initialized. The
        size of the matrix will depend on the number of blocks across and the
        number of blocks tall.
    */
    for (int i = 0; i < this->Matrix::getDiscreteHeight(); i++)
    {
        /*
        NOTE:
            - We declare the row first.
        */

        vector<Sprite> row;
        for (int j = 0; j < this->Matrix::getDiscreteWidth(); j++)
        {
            /*
            NOTE:
                - If `i` is `0` then all the Sprite objects in the first row would
                have the center top texture as specified by the setup blocks.
            */
            if (i == 0)
            {
                /*
                NOTE:
                    - If both indices `i` and `j` are `0` then the coordinates of
                    the very first element in the matrix are the coordinates of the
                    this instance itself.
                */
                if (j == 0)
                {
                    Coordinates position = this->getAbsolutePosition();
                    row.push_back(Sprite(Coordinates(position.getX(), position.getY()),
                                         this->getSetupBlocks()[TOP][CENTER]));
                }
                else
                {
                    /*
                    NOTE:
                        - However, if index `j` is not `0` then we need to find the
                        Sprite object to its left.
                    */
                    Sprite previous_horizontal = row[j - 1];

                    /*
                    NOTE:
                        - The starting position of the block that we're pushing into
                        the vector would be the right bound (i.e., x-coordinate + width)
                        of the block to its left. The y-coordinate stays the same.
                    */
                    row.push_back(Sprite(Coordinates(previous_horizontal.getRightBound(),
                                                     previous_horizontal.getAbsolutePosition().getY()),
                                         this->getSetupBlocks()[TOP][CENTER]));
                }
            }
            else if (i == this->Matrix::getDiscreteHeight() - 1)
            {
                /*
                NOTE:
                    - Similarly, if we're assigning the last row then we use the center
                    bottom texture as specified by the setup blocks.

                    - We also need to get the coordinates of the Sprite object that's
                    positioned on top of the Sprite that we're trying to instantiate.
                    This is to determine the next y-coordinates of the new instances.
                */
                Sprite previous_vertical = assembled[i - 1][j];
                if (j == 0)
                {
                    Coordinates position = this->getAbsolutePosition();
                    row.push_back(Sprite(Coordinates(position.getX(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[BOTTOM][CENTER]));
                }
                else
                {
                    Sprite previous_horizontal = row[j - 1];

                    row.push_back(Sprite(Coordinates(previous_horizontal.getRightBound(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[BOTTOM][CENTER]));
                }
            }
            else
            {
                Sprite previous_vertical = assembled[i - 1][j];
                if (j == 0)
                {
                    Coordinates position = this->getAbsolutePosition();
                    row.push_back(Sprite(Coordinates(position.getX(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[MIDDLE][CENTER]));
                }
                else
                {
                    Sprite previous_horizontal = row[j - 1];

                    /*
                    NOTE:
                        - Here, we need to know the position of both the Sprites on top
                        and to the left of the Sprite that we're trying to instantiate.
                    */
                    row.push_back(Sprite(Coordinates(previous_horizontal.getRightBound(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[MIDDLE][CENTER]));
                }
            }
        }

        /*
        NOTE:
            - Adding the row that we just initialized into the matrix `assembled`.
        */
        assembled.push_back(row);
    }

    /*
    NOTE:
        - Finally using the setter from the base class.
    */
    this->setAssembled(assembled);
}