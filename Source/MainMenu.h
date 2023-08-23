#pragma once

#include "LIBDECLARATIONS.h"

#include "Utilities.h"
#include "FileHandling.h"

#include "Navigation.h"

#include "Sprite.h"

#include "Button.h"

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

class MainMenu : public Navigation {
public:
	/*
	SECTION 0: BUTTONS
	*/
	Button play;
	Button settings;
	Button instructions;
	Button about;
	Button exit;

	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	MainMenu();
	MainMenu(UserEvent user_actions, int screen_width, int screen_height,
		SDL_Renderer* renderer);

	/*
	SECTION 2: NAVIGATION LOGIC
	*/
	int stateQuery();
	void update();
	void render();
};

/*
SECTION 1: CONSTRUCTOR AND DESTRUCTORS
*/
MainMenu::MainMenu() : Navigation() {
	/*
	NOTE:
		- Using the base class's constructor.
	*/
}

MainMenu::MainMenu(UserEvent user_actions, int screen_width, int screen_height,
	SDL_Renderer* renderer) : Navigation(user_actions, screen_width, screen_height, renderer) {
	/*
	NOTE:
		- Using the base class's parameterized constructor.

		- All buttons are loaded using the `FileHandling` class,
		similar to the one in `Gameplay.h`. 
	*/
	
	/*
	NOTE:
		- Button and background loading to be added later. 
	*/
}

/*
SECTION 2: NAVIGATION LOGIC
*/
int MainMenu::stateQuery() {
	/*
	NOTE:
		- Empty for now.
	*/
}

void MainMenu::update() {
	/*
	NOTE:
		- Empty for now.
	*/
}

void MainMenu::render() {
	/*
	NOTE:
		- Empty for now.
	*/
}