/*
@ COLLABORATORS: Khanh Nguyen
@ CLASS DESIGNERS: Khanh Nguyen
*/

#pragma once

#include "Enemy.h"

class Goon : public Enemy {
	/*
	NOTE:
		- This class accounts for all humanoid enemies with 
		Player-chasing movement.
	*/

public:
	/*
	SECTION 1: CONSTRUCTOR AND DESTRUCTORS
	*/
	Goon();
	Goon(int x, int y, Animation animation, Damage damage_dealt, Knockback knockback);
	~Goon();

	/*
	SECTION 2A: SETTERS
	*/

	/*
	SECTION 2B: GETTERS
	*/

	/*
	SECTION 3: OTHER METHODS
	*/

	void chasePlayer(Player& player, vector<Ground>& grounds, vector<Platform>& platforms);
	void attack();

	void setNextFrame();
	void update();
	void render(SDL_Renderer* renderer);
};

/*
SECTION 1: CONSTRUCTOR AND DESTRUCTORS
*/

Goon::Goon() : Enemy() {
	/*
	NOTE:
		- Enemy called by default has the -Default- name, and all
		attribute values are set to 0.

		- Also calls Character's default constructor to initialize
		default Enemy coordinates.
	*/

	Movement default_logic = { 0, 0, 0, 0, 0, 0 };

	Damage default_damage = { 0, 0 };

	this->setDamageDealt(default_damage);

	this->setUpdateInterval(0);
};

Goon::Goon(int x, int y, Animation animation, Damage damage_dealt, Knockback knockback)
	: Enemy(x, y, animation, damage_dealt, knockback) {
	this->setDamageDealt(damage_dealt);
	this->setUpdateInterval(0);

	/*
	NOTE:
		- By default, Enemy needs to be facing the right as
		they spawn, to ensure the consistency of their movement.
	*/

	this->setDirectionFacing(Direction::RIGHT);
};

Goon::~Goon() {
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

void Goon::chasePlayer(Player& player, vector<Ground>& grounds, vector<Platform>& platforms) {
	/*
	NOTE:
		- Below are the logic used for MeleeGoon to detect the Player.

		- MeleeGoon will always chase the Player in the X-direction.

		- If Player is on another platform, MeleeGoon will stop to jump when it is in range of the platform.
			+ The Goon will continue to chase once it lands on the platform.
			+ The same will happen if the Player is on a platform under the MeleeGoon.

		- Once in attack range, the MeleeGoon will stop for the entire attack animation and attack
		the player, then continues the chase.
	*/
	const int PIXEL_ERROR = 5;
	const int UPDATE_INTERVAL = 3;
	const int JUMP_X_RANGE = ((this->getInitialJumpVelocity() / 2) * UPDATE_INTERVAL) * this->getRunSpeed();
	const int DROP_HEIGHT = 20;

	/*
	NOTE:
		- While the Enemy is not within attack range, it will chase the Player.
	*/
	if (!this->isAttacking()) {
		/*
		NOTE:
			- MeleeGoon faces the Player at all times.

			- If MeleeGoon is within attack range, it will stop and attack.
		*/

		if (player.getX() + player.getWidth() <= this->getX() + this->getWidth()) {
			this->setDirectionFacing(Direction::LEFT);

			if (this->getLeftBound() > player.getLeftBound() && this->getLeftBound() < player.getRightBound() && this->getBottomBound() == player.getBottomBound()) {
				this->attack();
				player.setX(this->getLeftBound() - player.getWidth() - player.getRunSpeed());
			}
		}
		else if (player.getX() >= this->getX()) {
			this->setDirectionFacing(Direction::RIGHT);

			if (this->getRightBound() < player.getRightBound() && this->getRightBound() > player.getLeftBound() && this->getBottomBound() == player.getBottomBound()) {
				this->attack();
				player.setX(this->getRightBound() + player.getRunSpeed());
			}
		}

		/*
		NOTE:
			- Check if MeleeGoon is on the same platform as the Player.

			- MeleeGoon will jump onto same platform as the Player, to ensure
			that the MeleeGoon jumps onto the platform, it must meet the Player's
			current platform's boundary to jump on.

			- MeleeGoon will drop if it is above the Player y-level.
		*/
		if (player.getBottomBound() < this->getBottomBound() && player.getCollisionDirections().bottom && this->getCollisionDirections().bottom) {
			Platform current_platform_ptr;

			for (Platform current_platform : platforms) {
				if (player.getBottomBound() >= current_platform.getTopBound() - PIXEL_ERROR && player.getBottomBound() <= current_platform.getTopBound() + PIXEL_ERROR) {
					current_platform_ptr = current_platform;
					break;
				}
			}

			if (this->getLeftBound() > current_platform_ptr.getLeftBound() - JUMP_X_RANGE && this->getRightBound() < current_platform_ptr.getRightBound() + JUMP_X_RANGE) {
				this->jump();
				return;
			}
		}

		else if (player.getTopBound() > this->getBottomBound() && player.getCollisionDirections().bottom && this->getCollisionDirections().bottom && !this->isJumping()) {
			this->setY(this->getY() + DROP_HEIGHT);
			this->fall();
			return;
		}
	}
	else {
		this->attack();
	}
}

void Goon::attack() {
	/*
	NOTE:
		- Temporarily triggers idle animation, since
		Enemy stops moving during attack.
	*/

	const int ANIMATION_FRAMES = 20;
	this->setRunningState(false);

	if (!this->isAttacking()) {
		this->setAttackingState(true);
		this->setUpdateInterval(0);
	}
	else {
		if (this->getUpdateInterval() == ANIMATION_FRAMES) {
			this->setAttackingState(false);
			this->setUpdateInterval(0);
		}
		else {
			this->setUpdateInterval(this->getUpdateInterval() + 1);
		}
	}
}

void Goon::setNextFrame() {
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

void Goon::update() {
	this->move();
	this->setNextFrame();
}

void Goon::render(SDL_Renderer* renderer) {
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