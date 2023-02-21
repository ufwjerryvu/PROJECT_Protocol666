/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

class Projectile : public Sprite {
private:
	int damage;
	int velocity;
	Direction travel_direction;
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Projectile();
	Projectile(int x, int y, SDL_Texture* texture);
	Projectile(int x, int y, SDL_Texture* texture, Direction travel_direction);
	~Projectile();

	/*
	SECTION 2A: SETTERS
	*/
	bool setCollisionDamage(int damage);
	bool setProjectileVelocity(int velocity);
	bool setTravelDirection(Direction travel_direction);

	/*
	SECTION 2B: GETTERS
	*/
	int getCollisionDamage();
	int getProjectileVelocity();
	Direction getTravelDirection();

	/*
	SECTION 3: OTHER METHODS
	*/
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Projectile::Projectile() : Sprite() {
	/*
	NOTE:
		- Do not use the default constructor if 
		not needed.
	*/
	this->setCollisionDamage(0);
	this->setProjectileVelocity(0);
	this->setTravelDirection(Direction::NONE);
}

Projectile::Projectile(int x, int y, SDL_Texture* texture) : Sprite(x, y, texture) {
	/*
	NOTE:
		- Do not use this constructor as well. Use
		the constructor with the most number of
		parameters.
	*/
	this->setCollisionDamage(0);
	this->setProjectileVelocity(0);
	this->setTravelDirection(Direction::NONE);
}

Projectile::Projectile(int x, int y, SDL_Texture* texture, Direction travel_direction)
	: Sprite(x, y, texture) {
	/*
	NOTE:
		- This is the preferred constructor. But don't use
		the base class to initialize or instantiate objects.
	*/

	/*
	NOTE:
		- The setCollisionDamage() and setProjectileVelocity()
		functions should take in different values in the 
		parameterized constructors of Projectile's derived classes.
		In other words, the values being set for collision damage
		and projectile velocity are overridable and should be 
		anything other than 0 when constructing derived classes.
	*/
	this->setCollisionDamage(0);
	this->setProjectileVelocity(0);
	this->setTravelDirection(travel_direction);
}

Projectile::~Projectile() {
	/*
	NOTE:
		- Empty for now.
	*/
}
/*
SECTION 2A: SETTERS
*/
bool Projectile::setCollisionDamage(int damage) {
	bool success = true;

	this->damage = damage;

	return success;
}

bool Projectile::setProjectileVelocity(int velocity) {
	bool success = true;

	this->velocity = velocity;

	return success;
}

bool Projectile::setTravelDirection(Direction travel_direction) {
	bool success = true;

	this->travel_direction = travel_direction;

	return success;
}

/*
SECTION 2B: GETTERS
*/
int Projectile::getCollisionDamage() { return this->damage; }
int Projectile::getProjectileVelocity() { return this->velocity; }
Direction Projectile::getTravelDirection() { return this->travel_direction; }

/*
SECTION 3: OTHER METHODS
*/