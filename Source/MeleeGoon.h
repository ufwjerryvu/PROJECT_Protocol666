/*
@ COLLABORATORS: Khanh Nguyen
@ CLASS DESIGNERS: Khanh Nguyen
*/

#pragma once

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
	MeleeGoon(string name, Movement movement_logic, Damage damage_dealt, int x, int y, Animation animation);
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
	void attack();
	void detectPlayer(Player& arg);
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
MeleeGoon::MeleeGoon() : Enemy(){}

MeleeGoon::MeleeGoon(string name, Movement movement_logic, Damage damage_dealt, int x, int y, Animation animation) : Enemy(name, movement_logic, damage_dealt, x, y, animation) {};

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
void MeleeGoon::attack(){
	
}

void MeleeGoon::detectPlayer(Player& arg) {
	const int DETECTION_RANGE = 300;
	const int ANIMATION_RANGE = 8;

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

	if (arg.getY() > this->getY() && arg.getY() < this->getY() - this->getHeight()) {
		if (this->getDirectionFacing() == Direction::RIGHT) {
			if (arg.getX() > this->getX() && arg.getX() && arg.getX() < this->getX() + DETECTION_RANGE) {				
				this->setX(this->getX() + 6);
				
				if (this->getX() + ANIMATION_RANGE == arg.getX()) {
					this->attack();
				}
			}
		}
		else if (this->getDirectionFacing() == Direction::LEFT) {
			if (arg.getX() < this->getX() && arg.getX() > this->getX() - DETECTION_RANGE) {
				this->setX(this->getX() - 6);

				if (this->getX() + ANIMATION_RANGE == arg.getX()) {
					this->attack();
				}
			}
		}
	}
}
