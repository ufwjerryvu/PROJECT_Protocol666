/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

enum class Direction {
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Collision {
	bool left = false;
	bool right = false;
	bool top = false;
	bool bottom = false;
};

struct Animation {
	vector<SDL_Texture*> frames_idle;
	vector<SDL_Texture*> frames_running;
	vector<SDL_Texture*> frames_jumping;
	vector<SDL_Texture*> frames_falling;

	int current_frame_idle = 0;
	int current_frame_running = 0;
	int current_frame_jumping = 0;
	int current_frame_falling = 0;
};

struct Damage {
	int collision;
	int attack;
	int self_destruct;
};

struct Movement {
	int spawn_x;
	int spawn_y;

	int x_max_displacement;
	int y_max_displacement;

	int x_direction_velocity;
	int y_direction_velocity;
};

class Sprite {
private:
	int x;
	int y;

	int render_x;
	int render_y;

	int width;
	int height;

	SDL_Texture* texture;
	SDL_Rect viewport;

	int level_width, level_height;
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Sprite();
	Sprite(int x, int y, SDL_Texture* texture);
	~Sprite();

	/*
	SECTION 2A: SETTERS
	*/
	bool setX(int x);
	bool setY(int y);
	bool setRenderX(int camera_x);
	bool setRenderY(int camera_y);
	bool setWidth(int width);
	bool setHeight(int height);
	bool setCoordinates(int x, int y);
	bool setRenderCoordinates(int camera_x, int camera_y);
	bool setTexture(SDL_Texture* texture);
	bool loadLevelWidth(int level_width);
	bool loadLevelHeight(int level_height);

	/*
	SECTION 2B: GETTERS
	*/
	int getX();
	int getY();
	int getRenderX();
	int getRenderY();
	int getWidth();
	int getHeight();
	int getTopBound();
	int getBottomBound();
	int getLeftBound();
	int getRightBound();
	SDL_Texture* getTexture();
	SDL_Rect getViewport();
	int getLevelWidth();
	int getLevelHeight();

	/*
	SECTION 3: OTHER METHODS
	*/
	bool render(SDL_Renderer* renderer, bool camera_follow);
};


/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Sprite::Sprite() {
	/*
	NOTE:
		- Initializing everything to default values.

		- Do not use default constructors if not needed.
	*/
	this->setX(0);
	this->setY(0);

	this->setRenderX(0);
	this->setRenderY(0);

	this->width = 0;
	this->height = 0;

	this->texture = NULL;
	this->viewport = SDL_Rect();
}

Sprite::Sprite(int x, int y, SDL_Texture* texture) {
	/*
	NOTE:
		- Setting attributes using the setter methods for
		extra security.
	*/
	this->setX(x);
	this->setY(y);

	this->setTexture(texture);

	if (this->getTexture() != NULL) {
		/*
		NOTE:
			- Using SDL_QueryTexture() to get the dimensions of
			the loaded texture.
		*/
		SDL_Point size;
		SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

		this->width = size.x;
		this->height = size.y;

		/*
		NOTE:
			- Setting the viewport using the texture information
			as well as the constructor's arguments.
		*/
		this->viewport = { x, y, this->width, this->height };
	}
	else {
		this->viewport = { x, y, 0, 0 };
	}
}

Sprite::~Sprite() {
	/*
	NOTE:
		- Empty for now.
	*/
}

/*
SECTION 2A: SETTERS
*/

bool Sprite::setX(int x) {
	bool success = true;
	
	/*
	NOTE:
		- Check x-coordinate's availability within the level
		before setting the Sprite's x-coordinates to a new location.
	*/

	if (!(x >= 0 && x <= this->getLevelWidth())) {
		cerr << "Warning from Sprite::setX(): x-coordinate is outside level bounds." << endl;
	}

	this->x = x;
	this->viewport.x = x;

	return success;
}
bool Sprite::setY(int y) {
	bool success = true;

	/*
	NOTE:
		- Check y-coordinate's availability in terms of height
		before changing the current Sprite's y-coordinate.
	*/

	if (!(y >= 0 && y <= this->getLevelHeight())) {
		cerr << "Warning from Sprite::setY(): y-coordinate is outside level bounds." << endl;
	}

	this->y = y;
	this->viewport.y = y;

	return success;
}

bool Sprite::setRenderX(int camera_x) {
	/*
	NOTE:
		- The x-coordinate to which the camera follows
		the character is different to that of the sprite's
		true x-coordinate in the level.
	*/

	bool success = true;
	const int SCREEN_WIDTH = 900;

	if (camera_x < 0) {
		cerr << "Error from Sprite::setRenderX(): camera x-coordinate is outside level bounds." << endl;
	}


	this->render_x = this->getX() - camera_x;

	return success;
}
bool Sprite::setRenderY(int camera_y) {
	/*
	NOTE:
		- Similarly, the y-coordinate to which the camera 
		follows the character is only relative to the level.
	*/

	bool success = true;
	const int SCREEN_HEIGHT = 500;

	if (camera_y < 0) {
		cerr << "Error from Sprite::setRenderY(): camera y-coordinate is outside level bounds." << endl;
	}

	this->render_y = this->getY() - camera_y;

	return success;
}

bool Sprite::setWidth(int width) {
	bool success = true;

	if (width == 0) {
		cerr << "Error from Sprite::setWidth(): width is 0 or null, and is not set." << endl;
		success = false;

		return success;
	}

	this->width = width;
	this->viewport.w = width;

	return success;
}

bool Sprite::setHeight(int height) {
	bool success = true;

	if (height == 0) {
		cerr << "Error from Sprite::setHeight(): height is 0 or null, and is not set." << endl;
		success = false;

		return success;
	}

	this->height = height;
	this->viewport.h = height;

	return success;
}

bool Sprite::setCoordinates(int x, int y) {
	/*
	NOTE:
		- Since both setX() and setY() return boolean
		values, we could use those values to set the
		coordinate.
	*/
	bool success = (this->setX(x) && this->setY(y));

	return success;
}

bool Sprite::setRenderCoordinates(int camera_x, int camera_y) {
	bool success = this->setRenderX(camera_x) && this->setRenderY(camera_y);

	return success;
}

bool Sprite::setTexture(SDL_Texture* texture) {
	/*
	NOTE:
		- This method determines the current texture of
		the sprite that is to be displayed.
	*/
	bool success = true;

	this->texture = texture;

	if (this->getTexture() != NULL) {
		/*
		NOTE:
			- We have to query for the size of the texture and 
			set the viewport again because the texture is now different
			or just in case it hasn't been initialized.
		*/
		SDL_Point size;
		SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);

		this->width = size.x;
		this->height = size.y;

		this->viewport = { this->x, this->y, this->width, this->height };
	}
	else {
		this->width = 0;
		this->height = 0;

		this->viewport = { 0, 0, this->width, this->height };
	}

	return success;
}

bool Sprite::loadLevelWidth(int level_width) {
	bool success = true;

	if (level_width == 0) {
		cerr << "Error from Sprite::loadLevelWidth() : level_width is 0 or null, and is not set." << endl;
		success = false;

		return success;
	}

	this->level_width = level_width;

	return success;
}

bool Sprite::loadLevelHeight(int level_height) {
	bool success = true;

	if (level_height == 0) {
		cerr << "Error from Sprite::loadLevelHeight() : level_height is 0 or null, and is not set." << endl;
		success = false;

		return success;
	}

	this->level_height = level_height;

	return success;
}

/*
SECTION 2B: GETTERS
*/
int Sprite::getX() { return this->x; }
int Sprite::getY() { return this->y; }
int Sprite::getRenderX() { return this->render_x; }
int Sprite::getRenderY() { return this->render_y; }
int Sprite::getWidth() { return this->width; }
int Sprite::getHeight() { return this->height; }
int Sprite::getTopBound() { return this->getY(); }
int Sprite::getBottomBound() { return this->getY() + this->getHeight(); }
int Sprite::getLeftBound() { return this->getX(); }
int Sprite::getRightBound() { return this->getX() + this->getWidth(); }
SDL_Texture* Sprite::getTexture() { return this->texture; }
SDL_Rect Sprite::getViewport() { return this->viewport; }
int Sprite::getLevelWidth() { return this->level_width; }
int Sprite::getLevelHeight() { return this->level_height; }

/*
SECTION 3: OTHER METHODS
*/
bool Sprite::render(SDL_Renderer* renderer, bool camera_follow = true) {
	bool success = true;

	/*
	NOTE:
		- According to the SDL documentation, SDL_RenderCopy()
		returns a negative number if it has failed to copy the
		texture to the renderer and a zero if it has successfully
		done so.
	*/
	if (!camera_follow) {
		if (SDL_RenderCopy(renderer, this->texture, NULL, &this->viewport) != 0) {
			cerr << "Error from Sprite::render(): unable to render the sprite's current texture."
				<< endl;
			success = false;
		}
	}
	else {
		SDL_Rect temp_viewport = this->viewport;
		temp_viewport.x = render_x;
		temp_viewport.y = render_y;

		if (SDL_RenderCopy(renderer, this->texture, NULL, &temp_viewport) != 0) {
			cerr << "Error from Sprite::render(): unable  to render the sprite's current texture."
				<< endl;
			success = false;
		}
	}

	return success;
}
