/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

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

	UserEvent user_actions;

public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS 
	*/
	Button();
	Button(int x, int y, ButtonAnimation animation,
		UserEvent user_actions);
	~Button();

	/*
	SECTION 2: OTHER METHODS
	*/
	bool unpress();
	bool isPressed();
	bool hide();
	bool appear();
	bool hover();

	bool update();
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Button::Button() : Sprite() {
	this->appears = false;
	this->hovering = false;
	this->pressed = false;

	this->animation = {NULL, NULL, NULL};

	user_actions = UserEvent{};
}

Button::Button(int x, int y, ButtonAnimation animation,
	UserEvent user_actions): Sprite(x, y, NULL) {
	this->appears = false;
	this->hovering = false;
	this->pressed = false;

	this->animation = animation;

	/*
	NOTE:
		- Setting the default texture to the idling
		image.
	*/
	this->setTexture(animation.idle);

	this->user_actions = user_actions;
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
bool Button::unpress() {
	bool success = true;

	this->pressed = false;

	return success;
}

bool Button::isPressed() {
	return this->pressed;
}

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

bool Button::hover() {
	bool success = true;

	/*
	NOTE:
		- If the mouse is hovering over the button then
		we set the `hovering` attribute to true and false 
		otherwise. If the user is pressing on the button
		then `pressing` gets set to true. False if otherwise.
	*/
	if (*this->user_actions.mouse_x >= this->getLeftBound() 
		&& *this->user_actions.mouse_x <= this->getRightBound()
		&& *this->user_actions.mouse_y >= this->getTopBound() 
		&& *this->user_actions.mouse_y <= this->getBottomBound()) {

		this->hovering = true;
		if (*this->user_actions.mouse_down) {
			this->pressed = true;
		}
	}
	else {
		this->hovering = false;
		this->pressed = false;
	}

	return success;
}

bool Button::update() {
	bool success = true;

	/*
	NOTE:
		- Calling `hover()` to set the relevant variables
		depending on the user.
	*/
	this->hover();

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