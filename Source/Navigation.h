/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Utilities.h"
#include "FileHandler.h"

#include "Sprite.h"

#include "Projectile.h"
#include "LaserBeam.h"
#include "FiftyCalibre.h"

#include "Character.h"
#include "Enemy.h"
#include "MeleeGoon.h"
#include "RangeGoon.h"
#include "Player.h"

#include "Terrain.h"
#include "Ground.h"
#include "Platform.h"
#include "SinglePlatform.h"
#include "MultiplePlatform.h"

class Navigation {
public:
	/*
	SECTION 0: SYSTEM VARIABLES, CONSTANTS, AND THE EVENT HANDLER
	*/
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int screen_width;
	int screen_height;

	UserEvent user_actions;

	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Navigation();
	Navigation(UserEvent user_actions, int screen_width, int screen_height,
		SDL_Renderer* renderer);

	/*
	SECTION 2: NAVIGATION LOGIC
	*/
	virtual void update() = 0;
	virtual void render() = 0;
};

/*
SECTION 1: CONSTRUCTOR AND DESTRUCTORS
*/
Navigation::Navigation() {
	/*
	NOTE:
		- Setting uninitialized variables to their supposed
		default states.
	*/
	this->screen_width = 0;
	this->screen_height = 0;
	this->user_actions = UserEvent();
}

Navigation::Navigation(UserEvent user_actions, int screen_width, int screen_height,
	SDL_Renderer* renderer) {
	/*
	NOTE:
		- Just simply assigning the arguments to their respective
		member fields.
	*/
	this->renderer = renderer;
	this->user_actions = user_actions;

	this->screen_width = screen_width;
	this->screen_height = screen_height;
}

/*
SECTION 2: NAVIGATION LOGIC (no implementation)
*/