/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

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
	bool setCoordinates(int x, int y);
	bool setRenderCoordinates(int camera_x, int camera_y);
	bool setTexture(SDL_Texture* texture);

	/*
	SECTION 2B: GETTERS
	*/
	int getX();
	int getY();
	int getRenderX();
	int getRenderY();
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();
	SDL_Rect getViewport();

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

	this->x = x;
	this->viewport.x = x;

	return success;
}
bool Sprite::setY(int y) {
	bool success = true;

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

	this->render_y = this->getY() - camera_y;

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

/*
SECTION 2B: GETTERS
*/
int Sprite::getX() { return this->x; }
int Sprite::getY() { return this->y; }
int Sprite::getRenderX() { return this->render_x; }
int Sprite::getRenderY() { return this->render_y; }
int Sprite::getWidth() { return this->width; }
int Sprite::getHeight() { return this->height; }
SDL_Texture* Sprite::getTexture() { return this->texture; }
SDL_Rect Sprite::getViewport() { return this->viewport; }

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