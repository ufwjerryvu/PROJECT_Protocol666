/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu, Khanh Nguyen
*/

#pragma once

#include "Sprite.h"

struct DiscreteDimensions {
	int width_by_units;
	int height_by_units;
};

class Terrain : public Sprite {
private:
	DiscreteDimensions discrete_dimensions;
	vector<vector<SDL_Texture*>> texture_setup_blocks;
	vector<vector<Sprite>> assembled_texture;
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Terrain();
	Terrain(int x, int y, vector<vector<SDL_Texture*>> texture_setup_blocks);
	Terrain(int x, int y, vector<vector<SDL_Texture*>> texture_setup_blocks, DiscreteDimensions discrete_dimensions);
	~Terrain();

	/*
	SECTION 2A: SETTERS
	*/
	bool setTextureBlocks(vector<vector<SDL_Texture*>> texture_setup_blocks);
	bool setDiscreteDimensions(DiscreteDimensions discrete_dimensions);
	bool setAssembledTexture(vector<vector<Sprite>> assembled_texture);
	bool setWidth();
	bool setHeight();
	bool setRenderCoordinates(int camera_x, int camera_y);
	/*
	SECTION 2B: GETTERS
	*/
	vector<vector<SDL_Texture*>> getTextureBlocks();
	DiscreteDimensions getDiscreteDimensions();
	vector<vector<Sprite>> getAssembledTexture();

	/*
	SECTION 3: OTHER METHODS
	*/
	bool render(SDL_Renderer* renderer, bool camera_follow);
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Terrain::Terrain() : Sprite() {
	/*
	NOTE:
		- Do not call the default constructor if not needed.
	*/
	this->setDiscreteDimensions(DiscreteDimensions{ 0, 0 });
}

Terrain::Terrain(int x, int y, vector<vector<SDL_Texture*>> texture_setup_blocks) : Sprite(x, y, NULL) {
	/*
	NOTE:
		- Setup blocks are just textures that are needed
		to assemble a terrain object.
	*/
	this->setTextureBlocks(texture_setup_blocks);
	this->setDiscreteDimensions(DiscreteDimensions{ 0, 0 });
}

Terrain::Terrain(int x, int y, vector<vector<SDL_Texture*>> texture_setup_blocks,
	DiscreteDimensions discrete_dimensions) : Sprite(x, y, NULL) {
	/*
	NOTE:
		- This is the preferred constructor. 
	*/
	this->setTextureBlocks(texture_setup_blocks);
	this->setDiscreteDimensions(discrete_dimensions);
}

Terrain::~Terrain() {
	/*
	NOTE:
		- Empty for now.
	*/
}

/*
SECTION 2A: SETTERS
*/
bool Terrain::setTextureBlocks(vector<vector<SDL_Texture*>> texture_blocks) {
	bool success = true;

	this->texture_setup_blocks = texture_blocks;

	return success;
}

bool Terrain::setDiscreteDimensions(DiscreteDimensions discrete_dimensions) {
	bool success = true;

	this->discrete_dimensions = discrete_dimensions;

	return success;
}

bool Terrain::setAssembledTexture(vector<vector<Sprite>> assembled_texture) {
	bool success = true;

	this->assembled_texture = assembled_texture;

	return success;
}

bool Terrain::setWidth() {
	bool success = true;

	/*
	NOTE:
		- Since the Terrain instance is not represented by a single
		texture but rather a collection of Sprites in a 2D vector,
		we can't use SDL_QueryTexture to find its width and so we have
		to determine the aggregate width by adding the widths of all
		the textures in a row together.
	*/
	vector<vector<Sprite>> assembled_texture = this->getAssembledTexture();
	int width_in_pixels = 0;

	if (assembled_texture.size()) {
		for (int index = 0; index < assembled_texture[0].size(); index++) {
			width_in_pixels += assembled_texture[0][index].getWidth();
		}
	}

	/*
	NOTE:
		- In the end, we still need to use the setter
		function from the base class because an instance of
		Terrain is still one individual object and not a
		collection of Sprites.
	*/
	Sprite::setWidth(width_in_pixels);

	return success;
}

bool Terrain::setHeight() {
	bool success = true;

	/*
	NOTE:
		- Similar to Terrain::setWidth(), we can find the
		aggregate height by adding all the heights of the
		textures in a column.
	*/
	vector<vector<Sprite>> assembled_texture = this->getAssembledTexture();
	int height_in_pixels = 0;

	for (int index = 0; index < assembled_texture.size(); index++) {
		if (assembled_texture[index].size()) {
			height_in_pixels += assembled_texture[index][0].getHeight();
		}
	}

	/*
	NOTE:
		- And again, we set the height of the Terrain object
		via the setter function in its base class.
	*/
	Sprite::setHeight(height_in_pixels);

	return success;
}

bool Terrain::setRenderCoordinates(int camera_x, int camera_y) {
	vector<vector<Sprite>> assembled_texture = this->getAssembledTexture();

	/*
	NOTE:
		- The attribute `assembled_texture` is a 2D vector that 
		contains Sprite objects. Therefore, in order to set the new
		render coordinates of all the objects we need to run 
		a nested loop.
	*/
	for (int i = 0; i < assembled_texture.size(); i++) {
		for (int j = 0; j < assembled_texture[i].size(); j++) {
			assembled_texture[i][j].setRenderCoordinates(camera_x, camera_y);
		}
	}

	/*
	NOTE:
		- At the end we need to set the new 2D vector to
		replace the old attributes.
	*/
	this->setAssembledTexture(assembled_texture);

	return true;
}

/*
SECTION 2B: GETTERS
*/
vector<vector<SDL_Texture*>> Terrain::getTextureBlocks() { return this->texture_setup_blocks; }
DiscreteDimensions Terrain::getDiscreteDimensions() { return this->discrete_dimensions; }
vector<vector<Sprite>> Terrain::getAssembledTexture() { return this->assembled_texture; }

/*
SECTION 3: OTHER METHODS
*/
bool Terrain::render(SDL_Renderer* renderer, bool camera_follow = true) {

	vector<vector<Sprite>> assembled_texture = this->getAssembledTexture();

	/*
	NOTE:
		- Similarly, to render all the objects in the 2D
		vector we need to use a nested loop.
	*/
	for (int i = 0; i < assembled_texture.size(); i++) {
		for (int j = 0; j < assembled_texture[i].size(); j++) {
			assembled_texture[i][j].render(renderer, camera_follow);
		}
	}

	return true;
}