/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

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
	SECTION 2: ASSET LOADING
	*/
	bool loadAllMainMenuAssets();

	/*
	SECTION 3: NAVIGATION LOGIC
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
	
	this->loadAllMainMenuAssets();
}

/*
SECTION 2: ASSET LOADING
*/
bool MainMenu::loadAllMainMenuAssets() {
	bool success = true;

	FileHandling file_io = FileHandling();

	/*
	NOTE:
		- Loading the buttons.
	*/
	int play_button_x = 0, play_button_y = 220;
	this->play = file_io.loadButton(this->renderer, play_button_x, play_button_y, 
		"play", this->user_actions);

	/*
	NOTE:
		- All the other buttons will be loaded later.
	*/
	this->about = Button();
	this->instructions = Button();
	this->settings = Button();
	this->exit = Button();

	return success;
}

/*
SECTION 3: NAVIGATION LOGIC
*/
int MainMenu::stateQuery() {
	/*
	NOTE:
		- Refer to the UML state diagram machine for more
		information regarding the return values for this function.
	*/
	const int NO_CHANGE = 0, GAMEPLAY = 1,
		SETTINGS = 2, INSTRUCTIONS = 3, ABOUT = 4, EXIT = 5;
	if (this->play.isPressed()) {
		return GAMEPLAY;
	}
	else if (this->settings.isPressed()) {
		return SETTINGS;
	}
	else if (this->instructions.isPressed()) {
		return INSTRUCTIONS;
	}
	else if (this->about.isPressed()) {
		return ABOUT;
	}
	else if (this->exit.isPressed()) {
		return EXIT;
	}

	return NO_CHANGE;
}

void MainMenu::update() {
	/*
	NOTE:
		- Centering/aligning the buttons.
	*/
	this->play.setX(this->screen_width / 2 - this->play.getWidth() / 2);

	/*
	NOTE:
		- We constantly run the state query function
		to make sure it's updated every frame and
		we update the buttons' status, too.
	*/
	this->play.update();

	this->stateQuery();
}

void MainMenu::render() {
	/*
	NOTE:
		- Clearing the renderer is important.
	*/
	SDL_RenderClear(this->renderer);

	this->play.render(this->renderer, false);

	/*
	NOTE:
		- Presenting to the renderer is also equally
		important.
	*/
	SDL_RenderPresent(this->renderer);
}