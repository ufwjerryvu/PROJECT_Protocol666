#pragma once

#include "Enemy.h"

class Goon : public Enemy {
	/*
	NOTE:
		- This class accounts for all humanoid enemies with 
		Player-chasing movement.
	*/

public:
	/*
	SECTION 1: CONSTRUCTOR AND DESTRUCTORS
	*/
	Goon();
	Goon(Gameplay *gameplay);
	~Goon();

	/*
	SECTION 2A: SETTERS
	*/

	/*
	SECTION 2B: GETTERS
	*/

	/*
	SECTION 3: OTHER METHODS
	*/

	void chasePlayer(Player& player, vector<Ground>& grounds, vector<Platform>& platforms);
	void attack();

	void update();
};