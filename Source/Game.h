/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Utilities.h"
#include "FileHandling.h"

#include "Sprite.h"

#include "Character.h"
#include "Player.h"

#include "Terrain.h"
#include "Ground.h"
#include "Platform.h"
#include "SinglePlatform.h"

class Game {
public:
	/*
	SECTION 0A: SYSTEM VARIABLES, CONSTANTS, AND THE EVENT HANDLER
	*/
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	static const int SCREEN_WIDTH = 900;
	static const int SCREEN_HEIGHT = 500;

	UserEvent user_actions;

	/*
	SECTION 0B: GAME BACKGROUND VARIABLES
	*/
	const int FRAME_RATE = 60;

	int current_level;

	int level_width;
	int level_height;

	SDL_Rect camera;

	vector<string> level_config_paths;

	/*
	SECTION 0C: GAME ASSETS VARIABLES
	*/
	Player player;
	vector<Ground> grounds;
	vector<Platform> platforms;

	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Game(UserEvent user_actions);

	/*
	SECTION 2: SYSTEM INITIALIZATIONS AND DESTRUCTIONS
	*/
	bool initialize();
	bool loadAllAssets();
	bool loadCurrentLevel();
	void close();

	/*
	SECTION 3: GAME LOGIC
	*/
	void updateCamera();
	void updateRenderCoordinates();
	void update();
	void render();
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Game::Game(UserEvent user_actions) {
	/*
	NOTE:
		- Initializing all SDL subsystems.
	*/

	if (!this->initialize()) {
		cerr << "Error from Game(): cannot initialize SDL subsystems." << endl;
	}

	/*
	NOTE:
		- Initializing the camera.
	*/
	SDL_Rect camera = { 0, 0, this->SCREEN_WIDTH, this->SCREEN_HEIGHT };
	this->user_actions = user_actions;

	/*
	NOTE:
		- Loading the first level of the game
		as we are initializing the game.
	*/
	this->current_level = 0;

	if (!this->loadCurrentLevel()) {
		cerr << "Error from Game(): cannot load the current level configurations." << endl;
	}

	/*
	NOTE:
		- Loading all assets.
	*/
	if (!this->loadAllAssets()) {
		cerr << "Error from Game(): cannot load some or all assets properly." << endl;
	}
}

/*
SECTION 2: SYSTEM INITIALIZATIONS AND DESTRUCTIONS
*/
bool Game::initialize() {
	bool success = true;

	/*
	NOTE:
		- Initializing the SDL video subsystems. This step is modified
		from lazyfoo.net.
	*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Error from Game.initialize(): cannot initialize the SDL video subsystems." << endl;
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
		cerr << "Error from Game.initialize(): cannot create window." << endl;
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
		cerr << "Error from Game.initialize(): cannot create renderer." << endl;
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
		cerr << "Error from Game.initialize(): cannot initialize IMG subsystems." << endl;
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
		cerr << "Error from Game.initialize(): could not initialize TTF subsystems." << endl;
		success = false;
		return success;
	}

	return success;
}

bool Game::loadAllAssets() {
	bool success = true;

	FileHandling file_io;

	this->player = file_io.loadPlayer(this->renderer, this->level_config_paths[this->current_level],
		this->user_actions);
	
	this->grounds = file_io.loadGrounds(this->renderer, this->level_config_paths[this->current_level]);
	this->platforms = file_io.loadPlatforms(this->renderer, this->level_config_paths[this->current_level]);

	/*
	NOTE:
		- We kind of have to update the player regarding how big
		the level is everytime the level changes. This is purely
		because of bad design.
	*/
	this->player.loadLevelWidth(this->level_width);
	this->player.loadLevelHeight(this->level_height);

	return success;
}

bool Game::loadCurrentLevel() {
	bool success = true;
	/*
	NOTE:
		- Initializing current level configs.
	*/

	FileHandling file_io;
	this->level_config_paths = file_io.parseLevelConfigPaths();

	this->level_width = file_io.parseLevelWidth(level_config_paths[this->current_level]);
	this->level_height = file_io.parseLevelHeight(level_config_paths[this->current_level]);

	return success;
}

void Game::close() {
	/*
	NOTE:
		- To be added later.
	*/
}

/*
SECTION 3: GAME LOGIC
*/

void Game::updateCamera() {
	/*
	NOTE:
		- The code below centers the player.
		- Code modified from lazyfoo.net.
	*/
	camera.x = (this->player.getX() + this->player.getWidth() / 2) - this->SCREEN_WIDTH / 2;
	camera.y = (this->player.getY() + this->player.getHeight() / 2) - this->SCREEN_HEIGHT / 2;

	/*
	NOTE:
		- Making sure the camera doesn't go out of the discrete_dimensions of
		the level. Again, the code was modified from lazyfoo.net.
	*/
	if (this->camera.x < 0) { this->camera.x = 0; }
	if (this->camera.y < 0) { this->camera.y = 0; }

	if (this->camera.x > this->level_width - this->SCREEN_WIDTH) {
		this->camera.x = this->level_width - this->SCREEN_WIDTH;
	}
	if (this->camera.y > this->level_height - this->SCREEN_HEIGHT) {
		this->camera.y = this->level_height - this->SCREEN_HEIGHT;
	}
}

void Game::updateRenderCoordinates() {
	/*
	NOTE:
		- We update the camera first.
	*/
	this->updateCamera();

	/*
	NOTE:
		- We must update the render coordinates of the player
		before we set the render coordinates of the other objects
		because the camera will be following the player.
	*/
	this->player.setRenderCoordinates(this->camera.x, this->camera.y);

	for (int index = 0; index < this->grounds.size(); index++) {
		this->grounds[index].setRenderCoordinates(this->camera.x, this->camera.y);
	}

	for (int index = 0; index < this->platforms.size(); index++) {
		this->platforms[index].setRenderCoordinates(this->camera.x, this->camera.y);
	}

	/*
	NOTE:
		- Then we update the render coordinates for the other objects
		in the game.
	*/
}

void Game::update() {
	/*
	NOTE:
		- All object updates must go first (including the player's).
		But the player's update must be placed last in the sequence
		of updates. I don't know why yet but this just feels right.
	*/
	this->updateRenderCoordinates();

	/*
	NOTE:
		- We must reset all collision directions for the player first.
	*/
	this->player.setCollision(Collision());
	this->player.collide(this->platforms);
	this->player.collide(this->grounds);

	this->player.update();
}

void Game::render() {
	/*
	NOTE:
		- Clearing everything in the renderer.
	*/
	SDL_RenderClear(this->renderer);

	/*
	NOTE:
		- Copying all the non-playable objects to the renderer.
	*/

	/*
	NOTE:
		- The player's texture is being copied last because
		the player's character will be on top of all the
		other textures.
	*/
	for (int index = 0; index < this->grounds.size(); index++) {
		this->grounds[index].render(this->renderer);
	}
	for (int index = 0; index < this->platforms.size(); index++) {
		this->platforms[index].render(this->renderer);
	}

	this->player.render(this->renderer);

	/*
	NOTE:
		- Finally rendering everything.
	*/
	SDL_RenderPresent(this->renderer);
}
