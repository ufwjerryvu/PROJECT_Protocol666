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