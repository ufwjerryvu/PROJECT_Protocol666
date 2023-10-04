/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "Navigation.h"
#include "SettingsPage.h"
#include "InstructionsPage.h"
#include "AboutPage.h"

class MainMenu : public Navigation {
public:
	/*
	SECTION 0: BUTTONS
	*/
	Button button_play;
	Button button_settings;
	Button button_instructions;
	Button button_about;
	Button button_exit;

	SettingsPage page_settings;
	InstructionsPage page_instructions;
	AboutPage page_about;

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
	void updateButtons();
	void update();
	void renderButtons();
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

	this->page_instructions = InstructionsPage(this->user_actions, this->screen_width,
		this->screen_height, this->renderer);
	this->page_settings = SettingsPage(this->user_actions, this->screen_width,
		this->screen_height, this->renderer);
	this->page_about = AboutPage(this->user_actions, this->screen_width,
		this->screen_height, this->renderer);

	FileHandling file_io = FileHandling();

	/*
	NOTE:
		- Loading the buttons. This is done by creating an array of
		Button pointers and dereferencing the pointer members as we
		try to construct the buttons. I think this is genius.
	*/
	const int SPACING_Y = 5;
	const int START_X = 0;
	const int START_Y = 130;
	
	string prefixes[] = { "play", "instructions", "settings",
		"about", "exit" };

	Button* init[] = {&this->button_play, &this->button_instructions,
		&this->button_settings, &this->button_about, &this->button_exit};

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
int MainMenu::stateQuery() {
	/*
	NOTE:
		- Refer to the UML state diagram machine for more
		information regarding the return values for this function.
	*/
	const int NO_CHANGE = 0, GAMEPLAY = 1,
		SETTINGS = 2, INSTRUCTIONS = 3, ABOUT = 4, EXIT = 5, REVERT = 1;

	if (this->button_play.isPressed()) {
		return GAMEPLAY;
	}
	else if (this->button_settings.isPressed()) {
		/*
		NOTE:
			- Don't forget to call .update() on the page.
			If this is forgotten then the page's stateQuery()
			is always going to revert back to the main menu.
		*/
		this->page_settings.update();
		if (this->page_settings.stateQuery() == REVERT) {
			return NO_CHANGE;
		}
		return SETTINGS;
	}
	else if (this->button_instructions.isPressed()) {
		/*
		NOTE:
			- Same here. We've gotta call the update() method
			so the buttons can work on their own.
		*/
		this->page_instructions.update();
		if (this->page_instructions.stateQuery() == REVERT) {
			return NO_CHANGE;
		}
		return INSTRUCTIONS; 
	}
	else if (this->button_about.isPressed()) {
		/*
		NOTE:
			- Calling update() again. Spent probably an hour debugging
			this. This is simply bad design, not gonna lie.

		*/
		this->page_about.update();
		if (this->page_about.stateQuery() == REVERT) {
			return NO_CHANGE;
		}
		return ABOUT;
	}
	else if (this->button_exit.isPressed()) {
		return EXIT;
	}

	return NO_CHANGE;
}

void MainMenu::updateButtons() {
	/*
	NOTE:
		- Updating all the buttons at once. Since all the
		buttons have different functions, we simply just 
		can't use a loop to update all of them. This is the
		best I can do, for now.
	*/
	this->button_play.update();
	this->button_instructions.update();
	this->button_settings.update();
	this->button_about.update();
	this->button_exit.update();
}

void MainMenu::update() {
	/*
	NOTE:
		- We constantly run the state query function
		to make sure it's updated every frame and
		we update the buttons' status, too. 
	*/
	const int NO_CHANGE = 0, GAMEPLAY = 1,
		SETTINGS = 2, INSTRUCTIONS = 3, ABOUT = 4, EXIT = 5;
	
	int page = this->stateQuery();

	/*
	NOTE:
		- This is kind of shitty code but I'm writing this 
		while I'm on a train after a 17-hour day so we're
		gonna have to make do. 
	*/
	switch (page) {
		case NO_CHANGE:
			this->updateButtons();
			break;
		case GAMEPLAY:
			break;
		case SETTINGS:
			this->page_settings.update();
			break;
		case INSTRUCTIONS:
			this->page_instructions.update();
			break;
		case ABOUT:
			this->page_about.update();
			break;
	}

	/*
	NOTE:
		- We can always refactor the code later. Right now,
		I'm just trying to finish this part so we can finish
		the game as soon as possible.
	*/

	this->stateQuery();
}

void MainMenu::renderButtons() {
	this->button_play.render(this->renderer, false);
	this->button_instructions.render(this->renderer, false);
	this->button_settings.render(this->renderer, false);
	this->button_about.render(this->renderer, false);
	this->button_exit.render(this->renderer, false);
}

void MainMenu::render() {
	/*
	NOTE:
		- Clearing the renderer is important.
	*/
	SDL_RenderClear(this->renderer);

	const int NO_CHANGE = 0, GAMEPLAY = 1,
		SETTINGS = 2, INSTRUCTIONS = 3, ABOUT = 4, EXIT = 5;

	int page = this->stateQuery();

	switch(page){
		case NO_CHANGE:
			this->renderButtons();
			break;
		case GAMEPLAY:
			break;
		case SETTINGS:
			this->page_settings.render();
			break;
		case INSTRUCTIONS:
			this->page_instructions.render();
			break;
		case ABOUT:
			this->page_about.render();
			break;
	}

	/*
	NOTE:
		- Presenting to the renderer is also equally
		important.
	*/
	SDL_RenderPresent(this->renderer);
}