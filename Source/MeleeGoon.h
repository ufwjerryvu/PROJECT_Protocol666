/*
@ COLLABORATORS: Khanh Nguyen
@ CLASS DESIGNERS: Khanh Nguyen
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

#include "Character.h"
#include "Player.h"
#include "Enemy.h"

class MeleeGoon : public Enemy {
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	MeleeGoon();
	MeleeGoon(int x, int y, Animation animation, string name, Movement movement_logic, Damage damage_dealt);
	~MeleeGoon();

	/*
	SECTION 2A: SETTERS
	*/
	/*
	SECTION 2B: GETTERS	
	*/
	/*
	SECTION 3: OTHER METHODS
	*/
	void detectPlayer(Player& arg);
	void attack();

	void setNextFrame();
	void update();
	void render(SDL_Renderer* renderer);
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
MeleeGoon::MeleeGoon() : Enemy(){
	/*
	NOTE:
		- Do not use this constructor if not needed.
	*/
}

MeleeGoon::MeleeGoon(int x, int y, Animation animation, string name, Movement movement_logic, Damage damage_dealt) 
	: Enemy(x, y, animation, name, movement_logic, damage_dealt) {
	/*
	NOTE:
		- This is the preferred constructor.
	*/
	this->setRunSpeed(2);

};

MeleeGoon::~MeleeGoon() {
	/*
	NOTE:
		- Empty for now
	*/
}

/*
SECTION 2A: SETTERS
*/
/*
SECTION 2B: GETTERS	
*/
/*
SECTION 3: OTHER METHODS
*/

void MeleeGoon::detectPlayer(Player& arg) {
	const int DETECTION_RANGE = 300;
	const int CLOSE_RANGE_DECTECTION = 5;
	const int ANIMATION_RANGE = 8;
	const int CHASING_SPEED = 4;
	const int PIXEL_ERROR = 5;

	if (arg.getY() <= this->getY() + PIXEL_ERROR && arg.getY() >= this->getY() - this->getHeight() - PIXEL_ERROR) {
		/*
		NOTE:
			- The MeleeGoons detect Player in a rectangular box in the direction
			the MeleeGoon is facing.

			- This rectangular detection zone is defined by the height of the
			EnemyGoon x 300 pixels (half and a little less than the width of the
			game window).

			- Once the player is detected, the Enemy has to run toward the Player
			and will then attack.

			- DEVELOPMENT: The animation range will be defined by the pixel art's
			animation, to be develop after Enemy is designed and animated.
		*/

		if (arg.getX() >= this->getX() - CLOSE_RANGE_DECTECTION && arg.getX() <= this->getX() + CLOSE_RANGE_DECTECTION) {
			/*
			NOTE:
				- This is close range detection range conditional check.
			*/
			
			if (arg.getX() < this->getX()) {
				this->setRunningState(true);
				this->setAttackingState(true);

				if (this->getDirectionFacing() == Direction::RIGHT) {
					this->setDirectionFacing(Direction::LEFT);
				}


				this->setX(this->getX() - CHASING_SPEED);
				this->setUpdateInterval(0);
			}
			else if (arg.getX() > this->getX()) {
				this->setRunningState(true);
				this->setAttackingState(true);

				if (this->getDirectionFacing() == Direction::LEFT) {
					this->setDirectionFacing(Direction::RIGHT);
				}

				this->setX(this->getX() + CHASING_SPEED);
				this->setUpdateInterval(0);
			}
		}

		else if (this->getDirectionFacing() == Direction::RIGHT) {
			/*
			NOTE:
				- This is the Enemy's detection range when facing
				the right.
			*/

			if (arg.getX() >= this->getX() && arg.getX() <= this->getX() + DETECTION_RANGE) {
				this->setRunningState(true);
				this->setAttackingState(true);

				this->setX(this->getX() + CHASING_SPEED);
				this->setUpdateInterval(0);

				if (this->getX() + ANIMATION_RANGE >= arg.getX() && this->getX() + ANIMATION_RANGE <= arg.getX() + arg.getWidth()) {
					this->attack();
					this->setUpdateInterval(0);
				}
			}
		}

		else if (this->getDirectionFacing() == Direction::LEFT) {
			/*
			NOTE:
				- This is the Enemy's detection range when facing
				the left.
			*/
			
			if (arg.getX() <= this->getX() && arg.getX() >= this->getX() - DETECTION_RANGE) {
				this->setRunningState(true);
				this->setAttackingState(true);

				this->setX(this->getX() - CHASING_SPEED);
				this->setUpdateInterval(0);

				if (this->getX() - ANIMATION_RANGE >= arg.getX() && this->getX() - ANIMATION_RANGE <= arg.getX() + arg.getWidth()) {
					this->attack();
					this->setUpdateInterval(0);
				}
			}
		}
	}

	else {
		this->setAttackingState(false);
	}
}

void MeleeGoon::attack() {
	/*
	NOTE:
		- Empty for now.
	*/
}

void MeleeGoon::setNextFrame() {
	/*
	NOTE:
		- This is the default setNextFrame() method from Player.h
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

void MeleeGoon::update() {
	this->move();
	this->setNextFrame();
}

void MeleeGoon::render(SDL_Renderer* renderer) {
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