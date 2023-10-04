/*
@ COLLABORATORS: Khanh Nguyen
@ CLASS DESIGNERS: Khanh Nguyen
*/

#pragma once

class RangeGoon : public Enemy {
public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	RangeGoon();
	RangeGoon(int x, int y, Animation animation, string name, Movement movement_logic, Damage damage_dealt);
	~RangeGoon();
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
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
RangeGoon::RangeGoon() : Enemy() {
	/*
	NOTE:
		- Do not use this constructor if not needed.
	*/
}

RangeGoon::RangeGoon(int x, int y, Animation animation, string name, Movement movement_logic, Damage damage_dealt) 
	: Enemy(x, y, animation, name, movement_logic, damage_dealt) {
	/*
	NOTE:
		- This is the preferred constructor.
	*/
};

RangeGoon::~RangeGoon() {
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

void RangeGoon::detectPlayer(Player& arg) {
	const int DETECTION_RANGE = 300;
	const int ATTACK_RANGE = 200;

	/*
	NOTE:
		- Similar to MeleeGoons, RangeGoons detect Player in a rectangular box 
		in the direction the MeleeGoon is facing.

		- RangeGoons also share the rectangular detection zone with MeleeGoon, 
		which is defined by the height of the EnemyGoon x 300 pixels in length
		(half and a little less than the width of the game window).

		- Once the player is detected, the RangeGoon will not shoot immediately
		as a shooting range of 300 pixels might seem unfair. Hence, it will have
		to run towards the Player, until it is in range to attack.

		- DEVELOPMENT: ATTACK_RANGE needs to be properly develop once 
		projectiles are done.
	*/

	if (arg.getY() > this->getY() && arg.getY() < this->getY() - this->getHeight()) {
		if (this->getDirectionFacing() == Direction::RIGHT) {
			if (arg.getX() > this->getX() && arg.getX() && arg.getX() < this->getX() + DETECTION_RANGE) {
				this->setX(this->getX() + 6);

				if (this->getX() + ATTACK_RANGE == arg.getX()) {
					this->attack();
				}
			}
		}
		else if (this->getDirectionFacing() == Direction::LEFT) {
			if (arg.getX() < this->getX() && arg.getX() > this->getX() - DETECTION_RANGE) {
				this->setX(this->getX() - 6);

				if (this->getX() + ATTACK_RANGE == arg.getX()) {
					this->attack();
				}
			}
		}
	}
}

void RangeGoon::attack() {
	/*
	NOTE:
		- Empty for now.
	*/
}