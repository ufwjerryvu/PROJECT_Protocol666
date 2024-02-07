#include "MatrixPlatform.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
MatrixPlatform::MatrixPlatform(Gameplay *context) : Platform(context), Terrain(context)
{
    /*
    NOTE:
        - Empty, probably for good.
    */
}
MatrixPlatform::~MatrixPlatform()
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
void MatrixPlatform::assemble()
{
    /*
    NOTE:
        - This function is nearly the same as that of `Ground::assemble()` but
        has many modifications. This is not a code repeat.
    */

    vector<vector<Sprite>> assembled;

    /*
    NOTE:
        - These constants are assuming that the setup textures are configured as 3x3.
        That is, `blocks` is a 3x3 two-dimensional vector.
    */
    const int LEFT = 0, CENTER = 1, RIGHT = 2;
    const int TOP = 0, MIDDLE = 1, BOTTOM = 2;

    /*
    NOTE:
        - Making sure the setup blocks vector isn't empty.
    */
    if (!this->Matrix::getSetupBlocks().size())
    {
        cerr << "Error: the two-dimensional vector for setup textures is empty." << endl;
        assert(false);
    }

    /*
    NOTE:
        - This is the part where the matrix `assembled` gets initialized. The size
        of the vector will depend on the number of blocks across `getDiscreteWidth()`
        and the number of blocks tall `getDiscreteHeight()`.
    */
    for (int i = 0; i < this->getDiscreteHeight(); i++)
    {
        /*
        NOTE:
            - We declare the row first.
        */
        vector<Sprite> row;
        for (int j = 0; j < this->getDiscreteWidth(); j++)
        {
            /*
            NOTE:
                - If `i` is 0 then all the Sprite objects in the first row would
                have the texture on the top row as specified by the setup blocks.
            */
            if (i == 0)
            {
                /*
                NOTE:
                    - If both indices `i` and `j` are `0` then the coordinates of
                    the very first element in the matrix is the coordinates of the
                    instance itself.
                */
                if (j == 0)
                {
                    Coordinates position = this->getAbsolutePosition();
                    row.push_back(Sprite(Coordinates(position.getX(), position.getY()),
                                         this->Matrix::getSetupBlocks()[TOP][LEFT]));
                }
                else if (j == this->getDiscreteWidth() - 1)
                {
                    /*
                    NOTE:
                        - However, if index `j` is not `0` then we need to find the
                        Sprite object to its left.
                    */
                    Sprite previous_horizontal = row[j - 1];
                    row.push_back(Sprite(Coordinates(previous_horizontal.getRightBound(),
                                                     previous_horizontal.getAbsolutePosition().getY()),
                                         this->getSetupBlocks()[TOP][RIGHT]));
                }
                else
                {
                    Sprite previous_horizontal = row[j - 1];

                    /*
                    NOTE:
                        - The starting position of the block that we're pushing into the vector
                        would be the right bound (i.e., x-coordinate + width) of the block to
                        its left. The y-coordinate stays the same.
                    */
                    row.push_back(Sprite(Coordinates(previous_horizontal.getRightBound(),
                                                     previous_horizontal.getAbsolutePosition().getY()),
                                         this->getSetupBlocks()[TOP][CENTER]));
                }
            }
            else if (i == this->getDiscreteHeight() - 1)
            {
                /*
                NOTE:
                    - Similarly, if we're assigning the last row then we use the
                    bottom row textures as specified by the setup blocks.

                    - We also need to get the coordinates of the Sprite object that's
                    positioned on top of the Sprite that we're trying to instantiate.
                    This is so that we could determine the next y-coordinates of the
                    new instances and this is done via the line below.
                */
                Sprite previous_vertical = assembled[i - 1][j];
                if (j == 0)
                {
                    row.push_back(Sprite(Coordinates(this->getAbsolutePosition().getX(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[BOTTOM][LEFT]));
                }
                else if (j == this->getDiscreteWidth() - 1)
                {
                    Sprite previous_horizontal = row[j - 1];

                    row.push_back(Sprite(Coordinates(previous_horizontal.getRightBound(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[BOTTOM][RIGHT]));
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
                    row.push_back(Sprite(Coordinates(this->getAbsolutePosition().getX(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[MIDDLE][LEFT]));
                }
                else if (j == this->getDiscreteWidth() - 1)
                {
                    Sprite previous_horizontal = row[j - 1];
                    /*
                    NOTE:
                        - Here, we need to know the position of both the Sprites
                        on top and to the left of the Sprite that we're trying to
                        instantiate.
                    */
                    row.push_back(Sprite(Coordinates(previous_horizontal.getRightBound(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[MIDDLE][RIGHT]));
                }
                else
                {
                    Sprite previous_horizontal = row[j - 1];
                    row.push_back(Sprite(Coordinates(previous_horizontal.getRightBound(),
                                                     previous_vertical.getBottomBound()),
                                         this->getSetupBlocks()[MIDDLE][CENTER]));
                }
            }
        }

        /*
        NOTE:
            - Adding the row that we just initialized into the final matrix 
            `assembled`.
        */
        assembled.push_back(row);
    }

    /*
    NOTE:
        - Finally using the setter from the base class.
    */
    this->Terrain::setAssembled(assembled);

    /*
        NOTE:
        - Based on the initialization information, we are parsing the width
        and the height and storing it in the base class.
    */
    int width = 0;
    for (int i = 0; i < assembled[0].size(); i++)
    {
        width += assembled[0][i].getWidth();
    }

    int height = 0;
    for (int i = 0; i < assembled.size(); i++)
    {
        height += assembled[i][0].getHeight();
    }

    this->setWidth(width);
    this->setHeight(height);
}