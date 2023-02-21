/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

#include "Terrain.h"
#include "Platform.h"

class SinglePlatform : public Platform {
private:
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	SinglePlatform();
	SinglePlatform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks);
	SinglePlatform(int x, int y, vector<vector<SDL_Texture*>> textures_blocks, DiscreteDimensions discrete_dimensions);
	~SinglePlatform();

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
SinglePlatform::SinglePlatform() : Platform() {
	/*
	NOTE:
		- Do not call the default constructor if not needed.
	*/
}

SinglePlatform::SinglePlatform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks)
	: Platform(x, y, texture_blocks) {
	/*
	NOTE:
		- Do not call this constructor if you don't know what
		you're doing.
	*/
}

SinglePlatform::SinglePlatform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks,
	DiscreteDimensions discrete_dimensions) : Platform(x, y, texture_blocks, discrete_dimensions) {
	/*
	NOTE:
		- This is the preferred constructor.
	*/

	/*
	NOTE:
		- Since this is a single platform, if the height
		is greater than one then we output a warning message.
		The block of code also automatically sets the height
		to one after the warning message.
	*/
	if (discrete_dimensions.height_by_units != 1) {
		cerr << "Warning from SinglePlatform::SinglePlatform(): height can only be 1 block tall. Height is reset to 1." << endl;
		discrete_dimensions.height_by_units = 1;
		this->setDiscreteDimensions(discrete_dimensions);
	}

	/*
	NOTE:
		- Similarly, if the width is less than two then
		we need to output a warning message and correct
		the dimensions.
	*/
	if (discrete_dimensions.width_by_units <= 1) {
		cerr << "Warning from SinglePlatform::SinglePlatform(): "
			<< "width can only be larger than or equal to 2 blocks wide. Width is set to the minimum of 2." << endl;
		discrete_dimensions.width_by_units = 2;
		this->setDiscreteDimensions(discrete_dimensions);
	}

	this->setAssembledTexture();
	Terrain::setWidth();
	Terrain::setHeight();
}

SinglePlatform::~SinglePlatform() {
	/*
	NOTE:
		- Empty for now.
	*/
}

/*
SECTION 2A: SETTERS
*/
bool SinglePlatform::setAssembledTexture() {
	bool success = true;

	vector<vector<SDL_Texture*>> texture_setup_blocks = this->getTextureBlocks();
	vector<vector<Sprite>> st_vec;

	/*
	NOTE:
		- Checking whether or not the vector is empty.
	*/
	if (!texture_setup_blocks.size()) {
		cerr << "Error from SinglePlatform::setAssembledTexture(): no elements are found in the setup texture vector." << endl;
		return success = false;
	}
	else {
		/*
		NOTE:
			- Checking if the row in the setup vector actually
			exists.
		*/
		const int PLATFORM_SETUP_SIZE = 3;
		if (texture_setup_blocks[0].size() != PLATFORM_SETUP_SIZE) {
			cerr << "Error from SinglePlatform::setAsssembledTexture(): invalid number of elements in the vector." << endl;
			return success = false;
		}
	}

	const int LEFT = 0, CENTER = 1, RIGHT = 2;

	/*
	NOTE:
		- The platform is one block tall so we only need
		to think one-dimensionally.
	*/
	vector<Sprite> row;
	for (int index = 0; index < this->getDiscreteDimensions().width_by_units; index++) {
		/*
		NOTE:
			- This whole thing is similar to how we instantiate
			Ground objects.
		*/
		if (index == 0) {
			Sprite temp(this->getX(), this->getY(), texture_setup_blocks[0][LEFT]);
			row.push_back(temp);
		}
		else if (index == this->getDiscreteDimensions().width_by_units - 1) {
			Sprite temp(row[index - 1].getRightBound(), this->getY(), texture_setup_blocks[0][RIGHT]);
			row.push_back(temp);
		}
		else {
			Sprite temp(row[index - 1].getRightBound(), this->getY(), texture_setup_blocks[0][CENTER]);
			row.push_back(temp);
		}
	}

	st_vec.push_back(row);

	/*
	NOTE:
		- The Terrain namespace has to be invoked because
		the class somehow doesn't recognize that the function
		was being overridden.
	*/
	Terrain::setAssembledTexture(st_vec);

	return success;
}

/*
SECTION 2B: GETTERS
*/
/*
SECTION 3: OTHER METHODS
*/