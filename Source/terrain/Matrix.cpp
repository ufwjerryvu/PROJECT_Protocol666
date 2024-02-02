#include "Matrix.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Matrix::Matrix()
{
    /*
    NOTE:
        - Empty, probably for good.
    */
}

Matrix::~Matrix(){
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
void Matrix::setDiscreteWidth(int width) { this->width = width; }
void Matrix::setDiscreteHeight(int height) { this->height = height; }
void Matrix::setSetupBlocks(vector<vector<SDL_Texture *>> blocks)
{
    /*
    NOTE:
        - All setup matrices must be a three by three. The middle ones get
        extended as always.
    */
    const int REQUIRED_M = 3;
    const int REQUIRED_N = 3;

    if (blocks.size() != REQUIRED_M)
    {
        cerr << "Error: the setup for the matrix assembly must be a 3x3." << endl;
        assert(false);
    }

    /*
    NOTE:
        - Now we're looping through each row to see if each row contains 
        exactly three. If not, we throw an assertion error and let the half
        witted user know.
    */
    for (int i = 0; i < blocks.size(); i++)
    {
        if (blocks[i].size() != REQUIRED_N)
        {
            cerr << "Error: the setup for the matrix assembly must be a 3x3." << endl;
            assert(false);
        }
    }

    /*
    NOTE:
        - Finally, we assign the blocks if all is well.
    */
    this->blocks = blocks;
}

int Matrix::getDiscreteWidth() { return this->width; }
int Matrix::getDiscreteHeight() { return this->height; }
vector<vector<SDL_Texture *>> Matrix::getSetupBlocks() { return this->blocks; }