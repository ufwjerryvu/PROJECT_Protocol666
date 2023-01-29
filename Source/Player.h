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
	Player(int x, int y, Animation animation, UserEvent user_actions);
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

Player::Player(int x, int y, Animation animation, UserEvent user_actions)
	: Character(x, y, animation) {

	/*
	NOTE:
		- Calling Character's parameterized constructor.
	*/
	this->user_actions = user_actions;

	const int PIXELS_PER_FRAME = 4;
	this->setRunSpeed(PIXELS_PER_FRAME);
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
	if (*user_actions.key_down) {
		this->setRunningState(true);

		if (user_actions.current_key_states[SDL_SCANCODE_A]) {
			/*
			NOTE:
				- The player is running left.
			*/
			this->setX(this->getX() - this->getRunSpeed());
			this->setDirectionFacing(Direction::LEFT);
		}
		else if (user_actions.current_key_states[SDL_SCANCODE_D]) {
			/*
			NOTE:
				- The player is running right.
			*/
			this->setX(this->getX() + this->getRunSpeed());
			this->setDirectionFacing(Direction::RIGHT);
		}

		/*
		NOTE:
			- This might be deleted later because the character
			won't be moving diagonally across the screen.
		*/
		
		/*if (user_actions.current_key_states[SDL_SCANCODE_S]) {
			this->setY(this->getY() + this->getRunSpeed());
		}*/
	}
	else {
		this->setRunningState(false);
	}
}

void Player::jump() {
	if (*user_actions.key_down) {
		this->setJumpingState(true);
		int current_max_jump_height = 400 - this->getMaxJumpHeight();

		if (user_actions.current_key_states[SDL_SCANCODE_W] && this->getY() >= current_max_jump_height) {
				this->setY(this->getY() - this->getRunSpeed());
		}
	}
	else {
		this->setJumpingState(false);
	}
}

void Player::move() {
	/*
	NOTE:
		- The move() method will entail both the run() and
		jump() methods because they are both actions that
		displace the player.
	*/

	this->run();
	this->jump();
}

void Player::setNextFrame() {
	/*
	NOTE:
		- This is the default setNextFrame() method. Derived classes
		can override the method if there are other preferred animation
		sequences.

		- We want the animation sequence to be updated every 10 frames
		for the idle animation so we use a modulo operation.
	*/
	int frames_per_sequence = 10;

	if (!this->isRunning()) {
		/*
		NOTE:
			- If the user isn't moving then the current moving frame
			must be reset to 0.
		*/
		Animation temp = this->getAnimation();
		temp.current_frame_running = 0;
		this->setAnimation(temp);

		/*
		NOTE:
			- Setting the texture to be rendered to the current moving frame.
		*/
		if (!(temp.current_frame_idle % frames_per_sequence)) {
			this->setTexture(temp.frames_idle[temp.current_frame_idle / frames_per_sequence]);
		}

		/*
		NOTE:
			- Making sure the index doesn't access anything out of the
			vector's range.
		*/
		if (temp.current_frame_idle >= (temp.frames_idle.size() - 1) * frames_per_sequence) {
			temp.current_frame_idle = 0;
		}
		else {
			temp.current_frame_idle++;
		}

		this->setAnimation(temp);
	}
	else {
		/*
		NOTE:
			- On the contrary, if the player is moving then the current
			index for the idle frame gets reset to 0.

			- Everything here is pretty similar to the previous block, just
			that idle animation frames are accounted for instead.

			- In this case, we want the next animation sequence
			to be updated every 5 frames so a modulo operation is used to
			make sure the animation doesn't happen too quickly.
		*/

		frames_per_sequence = 5;
		Animation temp = this->getAnimation();
		temp.current_frame_idle = 0;

		this->setAnimation(temp);

		/*
		NOTE:
			- Here's the modulo operation metioned earlier.
		*/
		if (!(temp.current_frame_running % frames_per_sequence)) {
			this->setTexture(temp.frames_running[temp.current_frame_running / frames_per_sequence]);
		}

		if (temp.current_frame_running >= ((temp.frames_running.size() - 1) * frames_per_sequence)) {
			temp.current_frame_running = 0;
		}
		else {
			temp.current_frame_running++;
		}

		this->setAnimation(temp);
	}
}

void Player::update() {
	/*
	NOTE:
		- This is one of the most important methods in this
		class because it will be called to update the state
		of the player's character.

		- I will reimplement this later -- or make it abstract.
		No idea yet.
	*/

	/* 
	JUMP/FALL DEVELOPMENT NOTE:
		- Temporary code block for collision, assuming y = 400 is a platform.
		- Otherwise, reset fall_velocity to 0, for the next fall.
	*/

	if (this->getY() <= 400 && !this->isJumping()) {
		this->fall();
	}
	else {
		this->setFallVelocity(0);
	}

	this->move();

	this->setNextFrame();
}

void Player::render(SDL_Renderer* renderer) {
	/*
	NOTE:
		- This will be refactored later. 
		
		- A scrolling level (or a camera that follows 
		the player) has been implemented.
	*/

	SDL_Rect viewport = this->getViewport();

	viewport.x = this->getRenderX();
	viewport.y = this->getRenderY();

	if (this->getDirectionFacing() == Direction::LEFT) {
		/*
		NOTE:
			- By default, all character textures will
			be facing right. We flip it if the player
			is trying to go left. We use SDL_RenderCopyEx()
			instead of SDL_RenderCopy() for this purpose.
		*/
		const SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

		SDL_RenderCopyEx(renderer, this->getTexture(), NULL, &viewport, 0.00, NULL, flip);
	}
	else if (this->getDirectionFacing() == Direction::RIGHT 
		|| this->getDirectionFacing() == Direction::NONE) {
		SDL_RenderCopy(renderer, this->getTexture(), NULL, &viewport);
	}
}