/*
@ COLLABORATORS: Jerry Vu, Kenny Nguyen
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"
#include "Character.h"

class Player : public Character{
private:
	int current_horizontal_key;
	bool simultaneous_horizontal_keys_pressed;
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

	this->current_horizontal_key = 0;
	this->simultaneous_horizontal_keys_pressed = false;
}

Player::Player(int x, int y, Animation animation, UserEvent user_actions)
	: Character(x, y, animation) {

	/*
	NOTE:
		- Calling Character's parameterized constructor.
	*/
	this->user_actions = user_actions;

	this->current_horizontal_key = 0;
	this->simultaneous_horizontal_keys_pressed = false;

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
	/*
	NOTE:
		- Checking if either of the horizontal running keys has been pressed 
		(i.e., 'A' and/or 'D') to set the running state of the player to true 
		for animation purposes.
	*/
	if (this->user_actions.current_key_states[SDL_SCANCODE_A] || this->user_actions.current_key_states[SDL_SCANCODE_D]) {
		this->setRunningState(true);

		if (this->user_actions.current_key_states[SDL_SCANCODE_A] && !this->user_actions.current_key_states[SDL_SCANCODE_D]) {
			/*
			NOTE:
				- This is what happens when only one key ('A') is pressed.
			*/
			this->simultaneous_horizontal_keys_pressed = false;
			this->current_horizontal_key = SDL_SCANCODE_A;
		}
		else if (!this->user_actions.current_key_states[SDL_SCANCODE_A] && this->user_actions.current_key_states[SDL_SCANCODE_D]) {
			/*
			NOTE:
				- This is what happens when only one key ('D') is pressed.
			*/
			this->simultaneous_horizontal_keys_pressed = false;
			this->current_horizontal_key = SDL_SCANCODE_D;
		}

		if (this->user_actions.current_key_states[SDL_SCANCODE_A] && this->user_actions.current_key_states[SDL_SCANCODE_D]) {
			/*
			NOTE:
				- If two keys are being pressed down then the subsequent key 
				is the final input.

				- For example, if 'D' was pressed first and 'A' is pressed
				after then 'A' becomes the final processed input and the
				player's character runs left.

				- We only change the value of `current_horizontal_key` if the 
				flag that notes the concurrence of the two horizontal keys 
				is not set.
			*/

			if (this->current_horizontal_key == SDL_SCANCODE_D && !this->simultaneous_horizontal_keys_pressed) {
				this->current_horizontal_key = SDL_SCANCODE_A;
			}
			else if (this->current_horizontal_key == SDL_SCANCODE_A && !this->simultaneous_horizontal_keys_pressed) {
				this->current_horizontal_key = SDL_SCANCODE_D;
			}

			this->simultaneous_horizontal_keys_pressed = true;
		}

		/*
		NOTE:
			- The variable `current_horizontal_key` ultimately decides
			the direction of the player's running motion and not 
			`current_key_states`.
		*/
		if (this->current_horizontal_key == SDL_SCANCODE_A) {
			this->setDirectionFacing(Direction::LEFT);
			/*
			NOTE:
				- Checking if the player is going out of the left bound. If they
				are then stop them.
			*/
			if (this->getX() - this->getRunSpeed() <= 0) {
				this->setRunningState(false);
				/*
				NOTE:
					- The following code that sets the x-coordinate is basically saying
					that we don't want to leave a gap between the player and the edge
					of the screen.
				*/
				this->setX(0);
				return;
			}
			/*
			NOTE:
				- The player is running left.
			*/
			this->setX(this->getX() - this->getRunSpeed());
		} else if (this->current_horizontal_key == SDL_SCANCODE_D) {
			this->setDirectionFacing(Direction::RIGHT);
			/*
			NOTE:
				- Checking if the player is going out of the right bound. If they
				are then stop them. 
			*/
			if (this->getX() + this->getRunSpeed() + this->getWidth() >= this->getLevelWidth()) {
				this->setRunningState(false);
				return;
			}
			/*
			NOTE:
				- The player is running right.
			*/
			this->setX(this->getX() + this->getRunSpeed());
		}
	}
	else {
		this->setRunningState(false);
	}
}

void Player::jump() {
	const int FRAME_UPDATE_INTERVAL = 3;

	if (this->isJumping()) {
		/*
		NOTE:
			- If the character is jumping mid air, jump() continues to increase the y
			coordinate of this player.
		*/

		if (this->getVerticalVelocity() == 0) {
			/*
			NOTE:
				- Jump is at its highest point, calls off the jump() function
			*/
			this->setJumpingState(false);
			this->setFallingState(true);
			this->setVerticalUpdateInterval(0);
			this->setVerticalVelocity(0);
			;
		}

		else if (this->getVerticalVelocity() > 0) {
			/*
			NOTE:
				- In a static jump, if 'W' key is pressed, the jump continues until
				max jump height is reached

				- During this jump, gravitational acceleration is in effect, slowing
				the player's jump/vertical velocity nearing the max jump height.

				- A frame update interval is added to demonstrate the deceleration of
				the vertical velocity as vertical velocity can only be change once
				a frame update interval is met, in this case '2'.

			*/

			if (this->getVerticalUpdateInterval() == FRAME_UPDATE_INTERVAL) {
				this->setVerticalVelocity(this->getVerticalVelocity() - this->getGravitationalAcceleration());
				this->setVerticalUpdateInterval(0);
			}

			else {
				this->setVerticalUpdateInterval(this->getVerticalUpdateInterval() + 1);
				this->setY(this->getY() - this->getVerticalVelocity());
			}
		}
	}

	/*
	NOTE:
		- Condition checks for 'W' key being pressed to trigger jump()

	*/

	else if (!this->isJumping() && this->user_actions.current_key_states[SDL_SCANCODE_W]) {
		this->setJumpingState(true);
		this->setVerticalVelocity(this->getInitialJumpVelocity());
		this->setVerticalUpdateInterval(0);
	}
}

void Player::move() {
	/*
	NOTE:
		- The move() method will entail both the run() and
		jump() methods because they are both actions that
		displace the player.
		
		- Fall() can only be called if the character is mid air,  
		while not in jumping motion

		- Jump() can only be called if the character is currently on
		a platform, and is not falling mid air.
		
	*/

	const int PIXEL_ERROR_MARGIN = 3;

	if (!this->isJumping() && this->getY() <= this->getLevelHeight()) {
		this->fall();
	}
	
	if (!this->isFalling()) {
		this->jump();
	}

	this->run();
	
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

	if (this->isFalling()) {
		Animation temp = this->getAnimation();

		temp.current_frame_idle = 0;
		temp.current_frame_running = 0;
		temp.current_frame_jumping = 0;

		this->setAnimation(temp);

		/*
		NOTE:
			- Setting the texture to be rendered to the current falling frame.
		*/
		if (!(temp.current_frame_falling % frames_per_sequence)) {
			this->setTexture(temp.frames_falling[temp.current_frame_falling / frames_per_sequence]);
		}

		/*
		NOTE:
			- Making sure the index doesn't access anything out of the
			vector's range.
		*/
		if (temp.current_frame_falling >= (temp.frames_falling.size() - 1) * frames_per_sequence) {
			temp.current_frame_falling = 0;
		}
		else {
			temp.current_frame_falling++;
		}

		this->setAnimation(temp);

		return;
	}

	if (this->isJumping()) {
		Animation temp = this->getAnimation();

		temp.current_frame_idle = 0;
		temp.current_frame_running = 0;
		temp.current_frame_falling = 0;

		this->setAnimation(temp);

		/*
		NOTE:
			- Setting the texture to be rendered to the current falling frame.
		*/
		if (!(temp.current_frame_jumping % frames_per_sequence)) {
			this->setTexture(temp.frames_jumping[temp.current_frame_jumping / frames_per_sequence]);
		}

		/*
		NOTE:
			- Making sure the index doesn't access anything out of the
			vector's range.
		*/
		if (temp.current_frame_jumping >= (temp.frames_jumping.size() - 1) * frames_per_sequence) {
			temp.current_frame_jumping = 0;
		}
		else {
			temp.current_frame_jumping++;
		}

		this->setAnimation(temp);

		return;
	}

	if (!this->isRunning()) {
		/*
		NOTE:
			- If the user isn't moving then the current moving frame
			must be reset to 0.
		*/
		Animation temp = this->getAnimation();

		temp.current_frame_running = 0;
		temp.current_frame_falling = 0;
		temp.current_frame_jumping = 0;

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
		temp.current_frame_falling = 0;
		temp.current_frame_jumping = 0;

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