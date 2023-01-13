/*
@ COLLABORATORS: Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"
#include "Character.h"

class Player : public Character{
protected:
	UserEvent user_actions;
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Player();
	Player(int x, int y, vector<SDL_Texture*> anm_frames_moving, 
		vector<SDL_Texture*> anm_frames_idle, UserEvent user_actions);
	~Player();

	/*
	SECTION 2A: SETTERS
	*/
	/*
	SECTION 2B: GETTERS
	*/

	/*
	SECTION 3: OTHER FUNCTIONS
	*/
	void run();
	void jump();
	void move();

	/*
	NOTE:
		- The render method here will override that of
		the base class Sprite. We will need to use
		SDL_RenderCopyEx() instead because the player's
		character needs to be flipped based on the 
		direction of travel.
	*/
	void setNextFrame();
	void update();
	void render(SDL_Renderer* renderer);
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Player::Player() : Character() {
	/*
	NOTE:
		- Calling the base classs's constructor. I don't know what
		to initialize user_actions with. Probably just setting 
		everything to NULL should do.
	*/

	user_actions = { NULL, NULL, NULL, NULL, NULL, NULL };
}

Player::Player(int x, int y, vector<SDL_Texture*> anm_frames_moving,
	vector<SDL_Texture*> anm_frames_idle, UserEvent user_actions)
	: Character(x, y, anm_frames_moving, anm_frames_idle) {

	/*
	NOTE:
		- Calling Character's parameterized constructor.
	*/
	this->user_actions = user_actions;
}

Player::~Player() {
	/*
	NOTE:
		- Empty for now.
	*/
}

/*
SECTION 2A: SETTERS
*/
/*
SECTION 2B: GETTERS
*/

/*
SECTION 3: OTHER FUNCTIONS
*/
void Player::run() {
	/*
	NOTE:
		- Empty for now. Might change to an 
		abstract method later on.
	*/
}

void Player::jump() {
	/*
	NOTE:
		- Empty for now. This, too.
	*/
}

void Player::move() {
	/*
	NOTE:
		- Empty for now. And this.
	*/
}

void Player::setNextFrame() {
	/*
	NOTE:
		- This is the default setNextFrame() method. Derived classes
		can override the method if there are other preferred animation
		sequences.
	*/
	if (!this->isMoving()) {
		/*
		NOTE:
			- If the user isn't moving then the current moving frame
			must be reset to 0.
		*/
		this->current_frame_moving = 0;

		/*
		NOTE:
			- Setting the texture to be rendered to the current moving frame.
		*/
		this->setTexture(this->getAnimationFramesIdle()[this->current_frame_idle]);

		/*
		NOTE:
			- Making sure the index doesn't access anything out of the
			vector's range.
		*/
		if (this->current_frame_idle >= this->getAnimationFramesIdle().size() - 1) {
			this->current_frame_idle = 0;
		}
		else {
			this->current_frame_idle++;
		}
	}
	else {
		/*
		NOTE:
			- On the contrary, if the player is moving then the current
			index for the idle frame gets reset to 0.

			- Everything here is pretty similar to the previous block, just
			that idle animation frames are accounted for instead.
		*/

		this->current_frame_idle = 0;

		this->setTexture(this->getAnimationFramesMoving()[current_frame_moving]);

		if (this->current_frame_moving >= this->getAnimationFramesMoving().size() - 1) {
			this->current_frame_moving = 0;
		}
		else {
			this->current_frame_moving++;
		}
	}
}

void Player::update() {
	/*
	NOTE:
		- This is one of the most important methods in this
		class because it will be called to update the state
		of the player's character.

		- I will implement this later -- or make it abstract.
		No idea yet.
	*/
}

void Player::render(SDL_Renderer* renderer) {
	/*
	NOTE:
		- This will be implemented later. Technicalities 
		for a scrolling level must be figured out before this
		can be worked on. 
	*/
}