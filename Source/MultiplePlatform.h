/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "Platform.h"

class MultiplePlatform : public Platform {
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	MultiplePlatform();
	MultiplePlatform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks);
	MultiplePlatform(int x, int y, vector<vector<SDL_Texture*>> textures_blocks, DiscreteDimensions discrete_dimensions);
	~MultiplePlatform();

	/*
	SECTION 2A: SETTERS
	*/
	bool setAssembledTexture();

	/*
	SECTION 2B: GETTERS
	*/
	/*
	SECTION 3: OTHER METHODS
	*/
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
MultiplePlatform::MultiplePlatform() : Platform() {
	/*
	NOTE:
		- Do not call the default constructor if not needed.
	*/
}

MultiplePlatform::MultiplePlatform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks)
	: Platform(x, y, texture_blocks) {
	/*
	NOTE:
		- Do not call this constructor if you don't know what
		you're doing.
	*/
}

MultiplePlatform::MultiplePlatform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks,
	DiscreteDimensions discrete_dimensions) : Platform(x, y, texture_blocks, discrete_dimensions) {
	/*
	NOTE:
		- This is the preferred constructor.
	*/

	/*
	NOTE:
		- Since this is a MultiplePlatform, if the height
		is less than or equal to one then we output a warning
		message. The block of code also automatically sets 
		the height to the minimum after the warning message.
	*/
	if (discrete_dimensions.height_by_units <= 1) {
		cerr << "Warning from MultiplePlatform::MultiplePlatform(): invalid height. Height is set to the minimum of 2." << endl;
		discrete_dimensions.height_by_units = 2;
		this->setDiscreteDimensions(discrete_dimensions);
	}

	/*
	NOTE:
		- Similarly, if the width is less than two then
		we need to output a warning message and correct
		the dimensions.
	*/
	if (discrete_dimensions.width_by_units <= 1) {
		cerr << "Warning from MultiplePlatform::MultiplePlatform(): "
			<< "width can only be larger than or equal to 2 blocks wide. Width is set to the minimum of 2." << endl;
		discrete_dimensions.width_by_units = 2;
		this->setDiscreteDimensions(discrete_dimensions);
	}

	this->setAssembledTexture();
	Terrain::setWidth();
	Terrain::setHeight();
}

MultiplePlatform::~MultiplePlatform() {
	/*
	NOTE:
		- Empty for now.
	*/
}

/*
SECTION 2A: SETTERS
*/
bool MultiplePlatform::setAssembledTexture() {
	bool success = true;
	/*
	NOTE:
		- This function is nearly the same as that of 
		Ground::setAssembledTexture() but has many modifications. 
		This is not a code repeat.
	*/

	/*
	NOTE:
		- This function doesn't take in any parameters because it's
		the initializer for the second parameterized constructor.
		It utilizes the base class's attributes instead.
	*/
	vector<vector<Sprite>> assembled_texture;

	/*
	NOTE:
		- These constants are assuming that the setup textures
		are configured as 3x3. That is, `texture_setup_blocks`
		is a 3x3 two-dimensional vector.
	*/
	const int LEFT = 0, CENTER = 1, RIGHT = 2;
	const int TOP = 0, MIDDLE = 1, BOTTOM = 2;

	/*
	NOTE:
		- Checking if the texture blocks are empty.
	*/
	if (!this->getTextureBlocks().size()) {
		cerr << "Error from MultiplePlatform::setAssembledTexture(): the two-dimensional vector for setup "
			<< "textures is empty." << endl;
		return success = false;
	}

	/*
	NOTE:
		- This is the part where the 2D vector `assembled_texture`
		gets initialized. The size of the vector will depend on
		the number of blocks across `width_by_units` and the number
		of blocks tall `height_by_units`.
	*/
	for (int i = 0; i < this->getDiscreteDimensions().height_by_units; i++) {
		/*
		NOTE:
			- We declare the row first.
		*/
		vector<Sprite> row;
		for (int j = 0; j < this->getDiscreteDimensions().width_by_units; j++) {
			/*
			NOTE:
				- If `i` is 0 then all the Sprite objects in the
				first row would have the texture on the top row as
				specified by `Terrain::texture_setup_blocks`.
			*/
			if (i == 0) {
				/*
				NOTE:
					- If both indices `i` and `j` are 0 then the
					coordinates of the very first element in the
					2D vector are the coordinates of the MultiplePlatform
					instance itself.
				*/
				if (j == 0) {
					row.push_back(Sprite(this->getX(), this->getY(), this->getTextureBlocks()[TOP][LEFT]));
				}
				else if(j == this->getDiscreteDimensions().width_by_units - 1) {
					/*
					NOTE:
						- However, if index `j` is not 0 then we
						need to find the Sprite object to its left.
					*/
					Sprite previous_horizontal = row[j - 1];
					row.push_back(Sprite(previous_horizontal.getRightBound(), previous_horizontal.getY(),
						this->getTextureBlocks()[TOP][RIGHT]));
				}else{
					Sprite previous_horizontal = row[j - 1];

					/*
					NOTE:
						- The starting position of the block that we're
						pushing into the vector would be the right bound
						(i.e., x-coordinate + width) of the block to its
						left. The y-coordinate stays the same.
					*/
					row.push_back(Sprite(previous_horizontal.getRightBound(), previous_horizontal.getY(),
						this->getTextureBlocks()[TOP][CENTER]));
				}
			}
			else if (i == this->getDiscreteDimensions().height_by_units - 1) {
				/*
				NOTE:
					- Similarly, if we're assigning the last row then
					we use the bottom row textures as specified by `Terrain::
					texture_setup_blocks`.

					- We also need to get the coordinates of the Sprite object
					that's positioned on top of the Sprite that we're trying to
					instantiate. This is so that we could determine the next
					y-coordinates of the new instances and this is done via the line
					below.
				*/
				Sprite previous_vertical = assembled_texture[i - 1][j];
				if (j == 0) {
					row.push_back(Sprite(this->getX(), previous_vertical.getBottomBound(), this->getTextureBlocks()[BOTTOM][LEFT]));
				}
				else if(j == this->getDiscreteDimensions().width_by_units - 1) {
					Sprite previous_horizontal = row[j - 1];

					row.push_back(Sprite(previous_horizontal.getRightBound(),
						previous_vertical.getBottomBound(), this->getTextureBlocks()[BOTTOM][RIGHT]));
				}
				else {
					Sprite previous_horizontal = row[j - 1];

					row.push_back(Sprite(previous_horizontal.getRightBound(),
						previous_vertical.getBottomBound(), this->getTextureBlocks()[BOTTOM][CENTER]));
				}
			}
			else {
				Sprite previous_vertical = assembled_texture[i - 1][j];
				if (j == 0) {
					row.push_back(Sprite(this->getX(), previous_vertical.getBottomBound(), this->getTextureBlocks()[MIDDLE][LEFT]));
				}
				else if (j == this->getDiscreteDimensions().width_by_units - 1) {
					Sprite previous_horizontal = row[j - 1];
					/*
					NOTE:
						- Here, we need to know the position of both
						the Sprites on top and to the left of the Sprite
						that we're trying to instantiate.
					*/
					row.push_back(Sprite(previous_horizontal.getRightBound(),
						previous_vertical.getBottomBound(), this->getTextureBlocks()[MIDDLE][RIGHT]));
				}
				else {
					Sprite previous_horizontal = row[j - 1];
					row.push_back(Sprite(previous_horizontal.getRightBound(),
						previous_vertical.getBottomBound(), this->getTextureBlocks()[MIDDLE][CENTER]));
				}
			}
		}

		/*
		NOTE:
			- Adding the row that we just initialized into the 2D
			vector `assembled_texture`. We then clear the vector `row`
			to initialize the succeeding rows.
		*/
		assembled_texture.push_back(row);
		row.clear();
	}

	/*
	NOTE:
		- Finally using the setter from the base class.
	*/
	Terrain::setAssembledTexture(assembled_texture);

	return success;
}

/*
SECTION 2B: GETTERS
*/
/*
SECTION 3: OTHER METHODS
*/