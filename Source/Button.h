/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

struct ButtonAnimation {
	SDL_Texture* idle;
	SDL_Texture* hovering;
	SDL_Texture* pressed;
};

class Button : public Sprite {
private:
	bool appears;
	bool hovering;
	bool pressed;

	ButtonAnimation animation;
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS 
	*/
	Button();
	Button(int x, int y, ButtonAnimation animation);
	~Button();
	/*
	SECTION 2: OTHER METHODS
	*/
	bool hide();
	bool appear();
	bool hover(UserEvent user_actions);

	bool update(UserEvent user_actions);
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Button::Button() : Sprite() {
	this->appears = false;
	this->hovering = false;
	this->pressed = false;

	this->animation = {NULL, NULL, NULL};
}

Button::Button(int x, int y, ButtonAnimation animation) : Sprite(x, y, NULL) {
	this->appears = false;
	this->hovering = false;
	this->pressed = false;

	this->animation = animation;
}

Button::~Button() {
	/*
	NOTE:
		- Empty for now.
	*/
}

/*
SECTION 2: OTHER METHODS
*/

bool Button::hide() {
	bool success = true;

	this->appears = false;

	return success;
}

bool Button::appear() {
	bool success = true;

	this->appears = true;

	return success;
}

bool Button::hover(UserEvent user_actions) {
	bool success = true;

	/*
	NOTE:
		- If the mouse is hovering over the button then
		we set the `hovering` attribute to true and false 
		otherwise. If the user is pressing on the button
		then `pressing` gets set to true. False if otherwise.
	*/
	if (*user_actions.mouse_x >= this->getLeftBound() && *user_actions.mouse_x <= this->getRightBound()
		&& *user_actions.mouse_y >= this->getTopBound() && *user_actions.mouse_y <= this->getBottomBound()) {
		this->hovering = true;
		if (*user_actions.mouse_down) {
			this->pressed = true;
		}
	}
	else {
		this->hovering = false;
		this->pressed = false;
	}

	return success;
}

bool Button::update(UserEvent user_actions) {
	bool success = true;
	
	/*
	NOTE:
		- Calling `hover()` to set the relevant variables
		depending on the user.
	*/
	this->hover(user_actions);

	this->setTexture(this->animation.idle);

	/*
	NOTE:
		- Changing the displaying textures depending on 
		whichever action the user is taking.
	*/
	if (this->hovering) {
		this->setTexture(this->animation.hovering);
	}

	if (this->pressed) {
		this->setTexture(this->animation.pressed);
	}

	return success;
}