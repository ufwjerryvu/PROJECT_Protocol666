/*
@ COLLABORATORS: Jerry Vu, Kenny Nguyen
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

#include "Character.h"

#include "Terrain.h"
#include "Ground.h"
#include "Platform.h"
#include "SinglePlatform.h"

#include "Projectile.h"
#include "LaserBeam.h"
#include "FiftyCalibre.h"

class Player : public Character{
private:
	int current_horizontal_key;
	bool simultaneous_horizontal_keys_pressed;

	SDL_Texture* laser_beam_texture;
	vector<LaserBeam> laser_beams;
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
	bool loadLaserBeamTexture(SDL_Texture* laser_beam_texture);
	/*
	SECTION 2B: GETTERS
	*/
	vector<LaserBeam>& getLaserBeams();
	/*
	SECTION 3: OTHER FUNCTIONS
	*/
	void run();
	void jump();
	void move();

	void collide(vector<Ground>& args);
	void collide(vector<Platform>& args);

	void shoot();

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

		- Do not call this constructor if not needed.
	*/

	user_actions = { NULL, NULL, NULL, NULL, NULL, NULL };

	this->current_horizontal_key = 0;
	this->simultaneous_horizontal_keys_pressed = false;

	this->laser_beam_texture = NULL;
}

Player::Player(int x, int y, Animation animation, UserEvent user_actions)
	: Character(x, y, animation) {

	/*
	NOTE:
		- Calling Character's parameterized constructor.

		- This is the preferred constructor.
	*/
	this->user_actions = user_actions;

	this->current_horizontal_key = 0;
	this->simultaneous_horizontal_keys_pressed = false;

	const int PIXELS_PER_FRAME = 4;
	this->setRunSpeed(PIXELS_PER_FRAME);

	this->laser_beam_texture = NULL;
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
bool Player::loadLaserBeamTexture(SDL_Texture* laser_beam_texture) {
	bool success = true;

	this->laser_beam_texture = laser_beam_texture;

	return success;
}

/*
SECTION 2B: GETTERS
*/
vector<LaserBeam>& Player::getLaserBeams() {
	return this->laser_beams;
}

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
	if (!this->isJumping() && this->getY() <= this->getLevelHeight()) {
		this->fall();
	}
	
	if (!this->isFalling()) {
		/*
		NOTE:
			- This doesn't mean that we're going to make
			the player's character jump. The function still
			depends on the user's input via `user_actions`.
		*/
		this->jump();
	}

	this->run();
}

void Player::collide(vector<Ground>& args) {

	/*
	NOTE:
		- Code now made less redundant.

		- Storing the current collision status of 
		the player into a temporary structure.
	*/
	Collision temp = this->getCollisionDirections();

	/*
	NOTE:
		- Looping through the blocks of Ground and
		setting the collision flags to whichever direction
		that collision is detected in.
	*/
	for (int index = 0; index < args.size(); index++) {
		if (this->checkCollision(args[index])) {
			if (this->getLeftBound() <= args[index].getRightBound()
				&& this->getLeftBound() >= args[index].getLeftBound()) {
				temp.left = true;
			}

			if (this->getRightBound() >= args[index].getLeftBound()
				&& this->getRightBound() <= args[index].getRightBound()) {
				temp.right = true;
			}

			if (this->getBottomBound() >= args[index].getTopBound()
				&& this->getBottomBound() <= args[index].getBottomBound()) {
				temp.bottom = true;

				/*
				NOTE:
					- This is to make sure that the player
					stays on top of the Ground object(s).
				*/

				const int PIXEL_ERROR_MARGIN = 3;
				this->setY(args[index].getY() - this->getHeight() + PIXEL_ERROR_MARGIN);
			}
		}

		/*
		NOTE:
			- Finally setting the collision directions
			for the player.
		*/
		this->setCollision(temp);
	}
}

void Player::collide(vector<Platform>& args) {
	/*
	NOTE:
		- Having a temporary structure storing the current
		collision status of the player.
	*/
	Collision temp = this->getCollisionDirections();

	/*
	NOTE:
		- Looping through the blocks of Platform and setting only
		the collision flag for the bottom bound of the player 
		because the player can basically jump UP through a
		platform but once they jump over the platform they can
		rest on the platform after they fall down.
	*/
	for (int index = 0; index < args.size(); index++) {
		if (this->checkCollision(args[index])) {

			if (this->getBottomBound() >= args[index].getTopBound()
				&& this->getBottomBound() <= args[index].getBottomBound()) {

				/*
				NOTE:
					- Adding the extra collision detection margin is sort
					of a band-aid solution but this code is to prevent the
					player from catapulting upwards jumping halfway through
					the platform.
				*/
				const int PIXEL_ERROR_MARGIN = 3;
				const int EXTRA_DETECTION_MARGIN = 12;
				if (this->getBottomBound() <= args[index].getTopBound() 
					+ PIXEL_ERROR_MARGIN + EXTRA_DETECTION_MARGIN) {
					temp.bottom = true;
				}
				/*
				NOTE:
					- This is to make sure that the player
					stays on top of the platform.
				*/
				if (!this->isJumping() && temp.bottom) {
					this->setY(args[index].getY() - this->getHeight() + PIXEL_ERROR_MARGIN);
				}
			}
		}

		/*
		NOTE:
			- Finally setting the collision directions
			for the player.
		*/
		this->setCollision(temp);
	}
}

void Player::shoot() {
	/*
	NOTE:
		- The button that the player will be using to shoot, for now,
		is the space button.
	*/
	if (this->user_actions.current_key_states[SDL_SCANCODE_SPACE]) {
		this->setAttackingState(true);

		int shooting_bound = 0;
		if (this->getDirectionFacing() == Direction::LEFT) {
			shooting_bound = this->getLeftBound();
		}
		else if (this->getDirectionFacing() == Direction::RIGHT) {
			shooting_bound = this->getRightBound();
		}

		/*
		NOTE:
			- If the player is facing left then we want the projectile
			to come out from the left bound and if the player is facing
			right then we want the projectile to come out from the right
			bound.
		*/
		const int GUN_LEVEL_CORRECTION_FACTOR = 10;
		LaserBeam temp(shooting_bound, (this->getTopBound() + this->getBottomBound()) / 2 
			- GUN_LEVEL_CORRECTION_FACTOR, this->laser_beam_texture, this->getDirectionFacing());

		/*
		NOTE:
			- We also want to load the level width and height into the
			LaserBeam elements because we want to delete the instance
			that is colliding with the level bounds.
		*/
		temp.loadLevelWidth(this->getLevelWidth());
		temp.loadLevelHeight(this->getLevelWidth());

		this->laser_beams.push_back(temp);
	}
	else {
		this->setAttackingState(false);
	}
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
	this->shoot();

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