#include "Sprite.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Sprite::Sprite()
{
	/*
	NOTE:
		- Do not use.
	*/
}
Sprite::Sprite(Coordinates absolute, SDL_Texture *texture)
{
	/*
	NOTE:
		- Setting attributes using the setter methods for
		extra security.
	*/
	this->absolute = absolute;

	this->setTexture(texture);

	if (this->getTexture() != NULL)
	{
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
		this->viewport = {this->absolute.getX(), this->absolute.getY(),
						  this->width, this->height};
	}
	else
	{
		this->viewport = {this->absolute.getX(), this->absolute.getY(),
						  0, 0};
	}
}

Sprite::~Sprite()
{
	/*
	NOTE:
		- Empty for now.
	*/
}

/*
SECTION 2A: SETTERS
*/

void Sprite::setAbsolutePosition(Coordinates absolute)
{
	/*
	NOTE:
		- Aligning the viewport's position to match up with
		the position of the sprite object.
	*/
	this->absolute = absolute;
}

void Sprite::setRelativePosition(Coordinates camera)
{
	/*
	NOTE:
		- The coordinates to which the camera follows the
		character is different to that of the sprite's true
		coordinates in the level.
	*/
	int x = this->absolute.getX() - camera.getX();
	int y = this->absolute.getY() - camera.getY();

	this->relative = Coordinates(x, y);
}

void Sprite::setWidth(int width)
{
	if (width <= 0)
	{
		cerr << "Error: width is invalid." << endl;
		assert(false);
	}

	/*
	NOTE:
		- This function is when we want to manually set the width and
		not have the width depend on the texture. Some Sprite objects
		are made up of multiple Sprite objects and not just one texture.
	*/
	this->width = width;
	this->viewport.w = width;
}

void Sprite::setHeight(int height)
{
	if (height == 0)
	{
		cerr << "Error: height is invalid." << endl;
		assert(false);
	}

	/*
	NOTE:
		- Similarly, this function is when we want to manually set the height and
		not have the height depend on the texture.
	*/
	this->height = height;
	this->viewport.h = height;
}

void Sprite::setTexture(SDL_Texture *texture)
{
	/*
	NOTE:
		- This method determines the current texture of
		the sprite that is to be displayed.
	*/
	this->texture = texture;

	if (this->getTexture() != NULL)
	{
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

		this->viewport = {this->absolute.getX(), this->absolute.getY(),
						  this->width, this->height};
	}
	else
	{
		/*
		NOTE:
			- Directly setting the sizes to `0` because this is one
			of the rare cases where it could be `0`. The enforcement
			policy in the setters are not suitable to be used here.
		*/
		this->width = 0;
		this->height = 0;

		this->viewport = {0, 0, this->width, this->height};
	}
}

/*
SECTION 2B: GETTERS
*/
Coordinates &Sprite::getAbsolutePosition() { return this->absolute; }
Coordinates &Sprite::getRelativePosition() { return this->relative; }
SDL_Texture *Sprite::getTexture() { return this->texture; }
SDL_Rect &Sprite::getViewport() { return this->viewport; }
int Sprite::getWidth() { return this->width; }
int Sprite::getHeight() { return this->height; }
int Sprite::getTopBound() { return this->absolute.getY(); }
int Sprite::getBottomBound() { return this->absolute.getY() + this->getHeight(); }
int Sprite::getLeftBound() { return this->absolute.getX(); }
int Sprite::getRightBound() { return this->absolute.getX() + this->getWidth(); }

/*
SECTION 3: OTHER METHODS
*/
void Sprite::render(SDL_Renderer *renderer, bool camera_follow = true)
{
	/*
	NOTE:
		- According to the SDL documentation, SDL_RenderCopy()
		returns a negative number if it has failed to copy the
		texture to the renderer and a zero if it has successfully
		done so.
	*/
	if (!camera_follow)
	{
		/*
		NOTE:
			- Setting the viewport's absolute position everytime we
			render without the camera.
		*/
		this->viewport.x = this->absolute.getX();
		this->viewport.y = this->absolute.getY();
	}
	else
	{
		this->viewport.x = this->relative.getX();
		this->viewport.y = this->relative.getY();
	}

	if (SDL_RenderCopy(renderer, this->texture, NULL, &this->viewport))
	{
		cerr << "Error: unable to render the current texture." << endl;
		assert(false);
	}
}
