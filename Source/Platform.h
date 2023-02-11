/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu, Khanh Nguyen
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"
#include "Terrain.h"

class Platform : public Terrain {
private:
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Platform();
	Platform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks);
	Platform(int x, int y, vector<vector<SDL_Texture*>> textures_blocks, DiscreteDimensions discrete_dimensions);
	~Platform();

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
Platform::Platform() : Terrain() {
	/*
	NOTE:
		- Do not call the default constructor if not needed.
	*/
}

Platform::Platform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks)
	: Terrain(x, y, texture_blocks) {
	/*
	NOTE:
		- Do not call this constructor if you don't know what
		you're doing.
	*/
}

Platform::Platform(int x, int y, vector<vector<SDL_Texture*>> texture_blocks,
	DiscreteDimensions discrete_dimensions) :Terrain(x, y, texture_blocks, discrete_dimensions) {
	/*
	NOTE:
		- This is the preferred constructor.
	*/
	this->setAssembledTexture();
	this->setWidth();
	this->setHeight();
}

Platform::~Platform() {
	/*
	NOTE:
		- Empty for now.
	*/
}
/*
SECTION 2A: SETTERS
*/
bool Platform::setAssembledTexture() {
	return true;
}
/*
SECTION 2B: GETTERS
*/
/*
SECTION 3: OTHER FUNCTIONS
*/