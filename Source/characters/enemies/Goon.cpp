#include "Goon.h"

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

	Damage default_damage = { 0, 0 };

	this->setDamageDealt(default_damage);

	this->setUpdateInterval(0);
};

Goon::Goon(Gameplay *gameplay) : Enemy(gameplay) 
{
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
	const int JUMP_X_RANGE = ((this->Jumpable::getInitialVelocity() / 2) * UPDATE_INTERVAL) * this->Runnable::getSpeed();
	const int DROP_HEIGHT = 20;

	/*
	NOTE:
		- While the Enemy is not within attack range, it will chase the Player.
        - To be re-implemented after Attackable is implemented.
	*/

	// if (!this->Attackable::isAttacking()) {
	// 	/*
	// 	NOTE:
	// 		- MeleeGoon faces the Player at all times.

	// 		- If MeleeGoon is within attack range, it will stop and attack.
	// 	*/

	// 	if (player.getX() + player.getWidth() <= this->getX() + this->getWidth()) {
	// 		this->setDirectionFacing(Direction::LEFT);
	// 	}
	// 	else if (player.getX() >= this->getX()) {
	// 		this->setDirectionFacing(Direction::RIGHT);
	// 	}

	// 	/*
	// 	NOTE:
	// 		- Check if MeleeGoon is on the same platform as the Player.

	// 		- MeleeGoon will jump onto same platform as the Player, to ensure
	// 		that the MeleeGoon jumps onto the platform, it must meet the Player's
	// 		current platform's boundary to jump on.

	// 		- MeleeGoon will drop if it is above the Player y-level.
	// 	*/
	// 	if (player.getBottomBound() < this->getBottomBound() && player.getCollisionDirections().bottom && this->getCollisionDirections().bottom) {
	// 		Platform current_platform_ptr;

	// 		for (Platform current_platform : platforms) {
	// 			if (player.getBottomBound() >= current_platform.getTopBound() - PIXEL_ERROR && player.getBottomBound() <= current_platform.getTopBound() + PIXEL_ERROR) {
	// 				current_platform_ptr = current_platform;
	// 				break;
	// 			}
	// 		}

	// 		if (this->getLeftBound() > current_platform_ptr.getLeftBound() - JUMP_X_RANGE && this->getRightBound() < current_platform_ptr.getRightBound() + JUMP_X_RANGE) {
	// 			this->jump();
	// 			return;
	// 		}
	// 	}
	// 	else if (player.getTopBound() > this->getBottomBound() && player.getCollisionDirections().bottom && this->getCollisionDirections().bottom && !this->isJumping()) {
	// 		this->setY(this->getY() + DROP_HEIGHT);
	// 		this->fall();
	// 		return;
	// 	}
	// }
}

void Goon::attack() {
	/*
	NOTE:
		- Temporarily triggers idle animation, since
		Enemy stops moving during attack.
	*/

	const int ANIMATION_FRAMES = 20;
	this->Runnable::setRunning(false);

    /*
	NOTE:
		- To be re-implemented after Attackable is implemented.
	*/

	// if (!this->isAttacking()) {
	// 	this->setAttackingState(true);
	// 	this->setUpdateInterval(0);
	// }
	// else {
	// 	if (this->getUpdateInterval() == ANIMATION_FRAMES) {
	// 		this->setAttackingState(false);
	// 		this->setUpdateInterval(0);
	// 	}
	// 	else {
	// 		this->setUpdateInterval(this->getUpdateInterval() + 1);
	// 	}
	// }
}

void Goon::update() {
	/*
    NOTE:
        - This method is used to update the Goon's position and state.
        - Currently, this method is taken from Player's update method
        with a few modifications.
		- We need to call the `move()` method before we query what the player
		is doing.
	*/
	this->move();

	/*
	TEMPORARY:
		- This is slightly more complicated and has more actions.
	*/

	if (this->isRunning())
		this->getAnimator().setKey("run");

	if (this->isFalling())
		this->getAnimator().setKey("fall");

	if (this->isJumping())
		this->getAnimator().setKey("jump");

}