/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Utilities.h"
#include "FileHandling.h"
#include "Gameplay.h"
#include "Navigation.h"
#include "MainMenu.h"

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

enum State {
	MAIN_MENU,
	GAMEPLAY,
	PAUSE
};

class Master {
public:
	/*
	SECTION 0A: SYSTEM VARIABLES, CONSTANTS, AND THE EVENT HANDLER
	*/
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	static const int SCREEN_WIDTH = 900;
	static const int SCREEN_HEIGHT = 500;

	UserEvent user_actions;

	const int FRAME_RATE = 60;

	/*
	SECTION 0B: STATE CONTROL AND BRANCHES
	*/
	State state;

	MainMenu main_menu;
	Gameplay gameplay;

	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Master(UserEvent user_actions);

	/*
	SECTION 2: SYSTEM INITIALIZATIONS AND DESTRUCTIONS
	*/
	bool initialize();
	void close();

	/*
	SECTION 3: UPDATE AND DISPLAY
	*/
	void update();
	void render();
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Master::Master(UserEvent user_actions) {
	/*
	NOTE:
		- Initializing all SDL subsystems.
	*/

	if (!this->initialize()) {
		cerr << "Error from Master(): cannot initialize SDL subsystems." << endl;
	}

	/*
	NOTE:
		- Initializing the camera.
	*/
	SDL_Rect camera = { 0, 0, this->SCREEN_WIDTH, this->SCREEN_HEIGHT };
	this->user_actions = user_actions;

	/*
	NOTE:
		- Making sure the first thing that pops up is the main menu when 
		the user starts the game.
	*/
	this->state = MAIN_MENU;

	/*
	NOTE:
		 - Passing the system variables and the event handler into the 
		 main menu and gameplay objects.
	*/
	this->main_menu = MainMenu(this->user_actions, this->SCREEN_WIDTH, this->SCREEN_HEIGHT,
		this->renderer);

	this->gameplay = Gameplay(this->user_actions, this->SCREEN_WIDTH, this->SCREEN_HEIGHT,
		this->renderer);
}

/*
SECTION 2: SYSTEM INITIALIZATIONS AND DESTRUCTIONS
*/
bool Master::initialize() {
	bool success = true;

	/*
	NOTE:
		- Initializing the SDL video subsystems. This step is modified
		from lazyfoo.net.
	*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Error from Master.initialize(): cannot initialize the SDL video subsystems." << endl;
		success = false;
		return success;
	}

	/*
	NOTE:
		- Attempting to create a window. This step is also modified
		from lazyfoo.net.
	*/
	this->window = SDL_CreateWindow("Protocol 666", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (this->window == NULL) {
		cerr << "Error from Master.initialize(): cannot create window." << endl;
		success = false;
		return success;
	}

	/*
	NOTE:
		- Also modified from lazyfoo.net. All textures of the game
		objects will be rendered via this renderer. If it fails then
		nothing gets displayed.
	*/
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == NULL) {
		cerr << "Error from Master.initialize(): cannot create renderer." << endl;
		success = false;
		return success;
	}

	/*
	NOTE:
		- Initializing the SDL IMG library, specifically to load
		in and display PNG images. Modified from lazyfoo.net.

		- The bitwise AND operation below is used to make sure
		the IMG_Init() function returns its argument. If the function
		doesn't return the value of its argument then the whole
		expression evaluates to 1, and 0 if vice versa.

		- In the document, IMG_INIT_PNG = 2. If IMG_Init(IMG_INIT_PNG)
		returns 2, then IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG is 2 & 2
		which would be evaluated to 1. At this point, we've successfully
		initiated the IMG subsystem for PNG images.

		- However, if IMG_Init(IMG_INIT_PNG) would return something else
		like 4, which presumably is the value for IMG_INIT_JPEG then
		the expression IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG is 4 & 2,
		which would then be evaluated to 0. A zero means we've failed
		to initialize the PNG subsystems.

		- This was just my rationale --- Jerry.
	*/
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		cerr << "Error from Master.initialize(): cannot initialize IMG subsystems." << endl;
		success = false;
		return success;
	}
	else {
		SDL_SetRenderDrawColor(renderer, 90, 90, 90, 90);
	}

	/*
	NOTE:
		- Modified from lazyfoo.net. A negative one means the
		TTF subsystem has failed to initialize.
	*/
	if (TTF_Init() == -1) {
		cerr << "Error from Master.initialize(): could not initialize TTF subsystems." << endl;
		success = false;
		return success;
	}

	return success;
}

void Master::close() {
	/*
	NOTE:
		- To be added later.
	*/
}

/*
SECTION 3: UPDATE AND DISPLAY
*/
void Master::update() {
	/*
	NOTE:
		- Check the UML state diagram for more information regarding
		the stateQuery() methods and their return values.
	*/
	if (this->state == MAIN_MENU) {
		this->main_menu.update();

		if (this->main_menu.stateQuery() == 1) {
			this->state = GAMEPLAY;
		}

	}
	if (this->state == GAMEPLAY) {
		this->gameplay.update();
	}
}

void Master::render() {
	if (this->state == MAIN_MENU) {
		this->main_menu.render();
	}

	if (this->state == GAMEPLAY) {
		this->gameplay.render();
	}
}
