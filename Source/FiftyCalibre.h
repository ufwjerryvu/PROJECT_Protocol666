/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

#include "Projectile.h"

class FiftyCalibre : public Projectile {
private:
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	FiftyCalibre();
	FiftyCalibre(int x, int y, SDL_Texture* texture);
	FiftyCalibre(int x, int y, SDL_Texture* texture, Direction travel_direction);
	~FiftyCalibre();
	/*
	SECTION 2A: SETTERS
	*/
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
FiftyCalibre::FiftyCalibre() : Projectile() {
	/*
	NOTE:
		- Do not use this constructor if not needed.
	*/
}
FiftyCalibre::FiftyCalibre(int x, int y, SDL_Texture* texture) : Projectile(x, y, texture) {
	/*
	NOTE:
		- Do not use this constructor if not needed.
	*/
}

FiftyCalibre::FiftyCalibre(int x, int y, SDL_Texture* texture, Direction travel_direction)
	: Projectile(x, y, texture, travel_direction) {
	/*
	NOTE:
		- This is the preferred constructor.
	*/

	this->setCollisionDamage(35);
	/*
	NOTE:
		- Projectile velocity is in pixels per frame.
	*/
	this->setProjectileVelocity(12);
}

FiftyCalibre::~FiftyCalibre() {
	/*
	NOTE:
		- Empty for now.
	*/
}
/*
SECTION 2A: SETTERS
*/
/*
SECTION 2B: GETTERS
*/

/*
SECTION 3: OTHER METHODS
*/
