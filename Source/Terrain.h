/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

class Terrain : public Sprite {
private:
	
public:
	Terrain();
	Terrain(int x, int y, SDL_Texture* texture);
	~Terrain();
};

Terrain::Terrain() : Sprite() {
	/*
	NOTE:
		- Empty for now.
	*/
}

Terrain::Terrain(int x, int y, SDL_Texture* texture) : Sprite(x, y, texture) {
	/*
	NOTE:
		- The arguments given to the base class constructor
		here is different to that of Character's because for
		Character we have animation frames so we need to 
		initialize the texture to NULL first.
	*/
}

Terrain::~Terrain() {
	/*
	NOTE:
		- Empty for now.
	*/
}