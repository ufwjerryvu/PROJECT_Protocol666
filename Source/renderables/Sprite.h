/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#pragma once

#include <Systems.h>

#include <Coordinates.h>

class Sprite
{
private:
	Coordinates absolute;
	Coordinates relative;

	SDL_Texture *texture;
	SDL_Rect viewport;

	int width;
	int height;

public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Sprite();
	Sprite(Coordinates absolute, SDL_Texture *texture);
	~Sprite();

	/*
	SECTION 2A: SETTERS
	*/
	void setAbsolutePosition(Coordinates absolute);
	void setRelativePosition(Coordinates camera);
	void setWidth(int width);
	void setHeight(int height);
	void setTexture(SDL_Texture *texture);

	/*
	SECTION 2B: GETTERS
	*/
	Coordinates &getAbsolutePosition();
	Coordinates &getRelativePosition();
	SDL_Texture *getTexture();
	SDL_Rect getViewport();
	int getWidth();
	int getHeight();
	int getTopBound();
	int getBottomBound();
	int getLeftBound();
	int getRightBound();

	/*
	SECTION 3: OTHER METHODS
	*/
	void render(SDL_Renderer *renderer, bool camera_follow);
};