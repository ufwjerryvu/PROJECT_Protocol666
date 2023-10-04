/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

class Gameplay {
public:
	/*
	SECTION 0A: SYSTEM VARIABLES, CONSTANTS, AND THE EVENT HANDLER
	*/
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int screen_width;
	int screen_height;

	UserEvent user_actions;

	/*
	SECTION 0B: GAME BACKGROUND VARIABLES
	*/
	int current_level;

	int level_width;
	int level_height;

	SDL_Rect camera;

	vector<string> level_config_paths;

	/*
	SECTION 0C: GAME ASSET VARIABLES
	*/
	Player player;
	vector<Ground> grounds;
	vector<Platform> platforms;

	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Gameplay();
	Gameplay(UserEvent user_actions, int screen_width, int screen_height,
		SDL_Renderer* renderer);
	/*
	SECTION 2: GAME LOADING
	*/
	bool loadAllGameplayAssets();
	bool loadCurrentLevel();

	/*
	SECTION 3: GAME LOGIC
	*/
	int stateQuery();

	void updateCamera();
	void updateRenderCoordinates();
	void updateCollisions();

	void update();
	void render();
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Gameplay::Gameplay() {
	/*
	NOTE:
		- Setting uninitialized fields to their default states.
	*/

	this->screen_width = 0;
	this->screen_height = 0;

	this->level_width = 0;
	this->level_height = 0;

	this->camera = SDL_Rect();

	this->user_actions = UserEvent();
	this->current_level = 0;
}

Gameplay::Gameplay(UserEvent user_actions, int screen_width, int screen_height,
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

	/*
	NOTE:
		- Same deal.
	*/
	this->current_level = 0;


	/*
	NOTE:
		- The gameplay variables are set using the loading member
		methods.

		- The function `loadCurrentLevel()` must come before
		`loadAllGameplayAssets()` or there will be a runtime error.
	*/
	this->loadCurrentLevel();
	this->loadAllGameplayAssets();
}

/*
SECTION 2: LOADING
*/
bool Gameplay::loadCurrentLevel() {
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

bool Gameplay::loadAllGameplayAssets() {
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

/*
SECTION 3: GAME LOGIC
*/
int Gameplay::stateQuery() {
	/*
	NOTE:
		- Empty for now.
	*/
	return 0;
}

void Gameplay::updateCamera() {
	/*
	NOTE:
		- The code below centers the player.
		- Code modified from lazyfoo.net.
	*/
	camera.x = (this->player.getX() + this->player.getWidth() / 2) - this->screen_width / 2;
	camera.y = (this->player.getY() + this->player.getHeight() / 2) - this->screen_height / 2;

	/*
	NOTE:
		- Making sure the camera doesn't go out of the discrete_dimensions of
		the level. Again, the code was modified from lazyfoo.net.
	*/
	if (this->camera.x < 0) { this->camera.x = 0; }
	if (this->camera.y < 0) { this->camera.y = 0; }

	if (this->camera.x > this->level_width - this->screen_width) {
		this->camera.x = this->level_width - this->screen_width;
	}
	if (this->camera.y > this->level_height - this->screen_height) {
		this->camera.y = this->level_height - this->screen_height;
	}
}

void Gameplay::updateRenderCoordinates() {
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

	for (int index = 0; index < this->player.getLaserBeams().size(); index++) {
		this->player.getLaserBeams()[index].setRenderCoordinates(this->camera.x, this->camera.y);
	}

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

void Gameplay::updateCollisions() {
	/*
	NOTE:
		- We must clear all collision directions
		for all objects that detect collision
		directions first.
	*/
	this->player.setCollision(Collision());

	/*
	NOTE:
		- Then we call all the objects that have a collide()
		function.
	*/
	this->player.collide(this->platforms);
	this->player.collide(this->grounds);

	/*
	NOTE:
		- Deleting laser beams from the vector if any laser beam
		is found to be violating the level bounds.
	*/
	for (int index = 0; index < this->player.getLaserBeams().size(); index++) {
		if (this->player.getLaserBeams()[index].getRightBound() >= this->level_width
			|| this->player.getLaserBeams()[index].getLeftBound() <= 0) {
			this->player.getLaserBeams().erase(this->player.getLaserBeams().begin() + index);
		}
	}
}

void Gameplay::update() {
	/*
	NOTE:
		- Updating the render coordinates to make sure
		the objects are properly in the camera.
	*/
	this->updateRenderCoordinates();
	this->updateCollisions();

	/*
	NOTE:
		- Updating the status of all the objects.
	*/
	this->player.update();
	for (int index = 0; index < this->player.getLaserBeams().size(); index++) {
		this->player.getLaserBeams()[index].update();
	}
}

void Gameplay::render() {
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
	for (int index = 0; index < this->player.getLaserBeams().size(); index++) {
		this->player.getLaserBeams()[index].render(this->renderer);
	}

	this->player.render(this->renderer);

	/*
	NOTE:
		- Finally rendering everything.
	*/
	SDL_RenderPresent(this->renderer);
}
