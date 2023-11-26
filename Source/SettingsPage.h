/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Utilities.h"
#include "FileHandler.h"

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

class SettingsPage : public Navigation {
public:
	/*
	SECTION 0: BUTTONS
	*/
	Button button_back;

	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	SettingsPage();
	SettingsPage(UserEvent user_actions, int screen_width, int screen_height,
		SDL_Renderer* renderer);

	/*
	SECTION 2: ASSET LOADING
	*/
	bool loadAllSettingsPageAssets();

	/*
	SECTION 3: NAVIGATION LOGIC
	*/
	int stateQuery();
	void updateButtons();
	void update();
	void renderButtons();
	void render();
};

/*
SECTION 1: CONSTRUCTOR AND DESTRUCTORS
*/
SettingsPage::SettingsPage() : Navigation() {
	/*
	NOTE:
		- Using the base class's constructor.
	*/
}

SettingsPage::SettingsPage(UserEvent user_actions, int screen_width, int screen_height,
	SDL_Renderer* renderer) : Navigation(user_actions, screen_width, screen_height, renderer) {
	/*
	NOTE:
		- Using the base class's parameterized constructor.

		- All buttons are loaded using the `FileHandler` class,
		similar to the one in `Gameplay.h`.
	*/

	this->loadAllSettingsPageAssets();
}

/*
SECTION 2: ASSET LOADING
*/
bool SettingsPage::loadAllSettingsPageAssets() {
	bool success = true;

	FileHandler file_io = FileHandler();

	/*
	NOTE:
		- Loading the buttons. This is done by creating an array of
		Button pointers and dereferencing the pointer members as we
		try to construct the buttons. I think this is genius.
	*/
	const int SPACING_Y = 5;
	const int START_X = 0;
	const int START_Y = 380;

	string prefixes[] = { "back"};

	Button* init[] = { &this->button_back };

	/*
	NOTE:
		- Looping through the array of pointers and constructing
		buttons based on the array of prefixes. We dereference the
		pointers.
	*/
	int size_of_init = sizeof(init) / sizeof(Button*);

	int greatest_y = START_Y;

	for (int index = 0; index < size_of_init; index++) {
		*init[index] = file_io.loadButton(this->renderer, START_X,
			greatest_y + SPACING_Y, prefixes[index], this->user_actions);

		greatest_y = init[index]->getBottomBound() + SPACING_Y;

		/*
		NOTE:
			- Centering/aligning the buttons.
		*/
		init[index]->setX(this->screen_width / 2 - init[index]->getWidth() / 2);
	}

	return success;
}

/*
SECTION 3: NAVIGATION LOGIC
*/
int SettingsPage::stateQuery() {
	/*
	NOTE:
		- Refer to the UML state diagram machine for more
		information regarding the return values for this function.
	*/
	const int NO_CHANGE = 0, MAIN_MENU = 1;

	if (this->button_back.isPressed()) {
		return MAIN_MENU;
	}

	return NO_CHANGE;
}

void SettingsPage::updateButtons() {
	this->button_back.update();
}

void SettingsPage::update() {
	/*
	NOTE:
		- We constantly run the state query function
		to make sure it's updated every frame and
		we update the buttons' status, too.
	*/
	this->updateButtons();
	this->stateQuery();
	/*
	NOTE:
		- We can always refactor the code later. Right now,
		I'm just trying to finish this part so we can finish
		the game as soon as possible.
	*/
}

void SettingsPage::renderButtons() {
	this->button_back.render(this->renderer, false);
}

void SettingsPage::render() {
	/*
	NOTE:
		- Clearing the renderer is important.
	*/
	SDL_RenderClear(this->renderer);

	this->renderButtons();

	/*
	NOTE:
		- Presenting to the renderer is also equally
		important.
	*/
	SDL_RenderPresent(this->renderer);
}