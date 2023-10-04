/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

class LaserBeam : public Projectile {
private:
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	LaserBeam();
	LaserBeam(int x, int y, SDL_Texture* texture);
	LaserBeam(int x, int y, SDL_Texture* texture, Direction travel_direction);
	~LaserBeam();
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
LaserBeam::LaserBeam() : Projectile() {
	/*
	NOTE:
		- Do not use this constructor if not needed.
	*/
}
LaserBeam::LaserBeam(int x, int y, SDL_Texture* texture) : Projectile(x, y, texture) {
	/*
	NOTE:
		- Do not use this constructor if not needed.
	*/
}

LaserBeam::LaserBeam(int x, int y, SDL_Texture* texture, Direction travel_direction)
	: Projectile(x, y, texture, travel_direction) {
	/*
	NOTE:
		- This is the preferred constructor.
	*/

	this->setCollisionDamage(20);
	/*
	NOTE:
		- Projectile velocity is in pixels per frame.
	*/
	this->setProjectileVelocity(16);
}

LaserBeam::~LaserBeam() {
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
