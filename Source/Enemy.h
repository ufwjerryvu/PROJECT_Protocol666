/*
@ COLLABORATORS: Khanh Nguyen
@ CLASS DESIGNERS: Khanh Nguyen
*/

#pragma once

#include "Sprite.h"

#include "Character.h"
#include "Player.h"

class Enemy : public Character {
private:
	string name;
	Movement movement_logic;
	Damage damage_dealt;

	/*
	NOTE:
		- Name is the Enemy's categorized names (Zombie, Raider, etc...)

		- Movement_logic is defined in Movement struct which its unit is in pixels.

		- Damage_dealt is defined in Damage which is in Health Points 
		(presumed Player has 100 max HP)
	*/

public:
	/*
	SECTION 1: CONSTRUCTOR AND DESTRUCTORS
	*/
	Enemy();
	Enemy(string name, Movement movement_logic, Damage damage_dealt, int x, int y, Animation animation);
	~Enemy();

	/*
	SECTION 2A: SETTERS
	*/
	bool setName(string name);
	bool setMovementLogic(Movement movement_logic);
	bool setDamageDealt(Damage damage_dealt);

	/*
	SECTION 2B: GETTERS
	*/
	string getName();
	Movement getMovementLogic();
	Damage getDamageDealt();

	/*
	SECTION 3: OTHER FUNCTIONS
	*/
	void run();
	void jump();
	void move();

	/*
	NOTE:
		- DetectPlayer() is virtual, potentially, as different Enemy
		has different field of vision.

		- Attack() is virtual, potentially, since different Enemy has 
		different attacks (Range, Melee, Lunge Melee, etc...).
	*/

	virtual void detectPlayer(Player& arg) = 0;
	virtual void attack() = 0;
};

/*
SECTION 1: CONSTRUCTOR AND DESTRUCTORS
*/

Enemy::Enemy() : Character() {
	/*
	NOTE:
		- Enemy called by default has the -Default- name, and all
		attribute values are set to 0.

		- Also calls Character's default constructor to initialize
		default Enemy coordinates.
	*/
	
	this->setName("-Default-");
	
	Movement default_logic = {0, 0, 0, 0, 0, 0};

	this->setMovementLogic(default_logic);

	Damage default_damage = {0, 0, 0};

	this->setDamageDealt(default_damage);
};

Enemy::Enemy(string name, Movement movement_logic, Damage damage_dealt, int x, int y, Animation animation) : Character(x, y, animation) {
	this->setName(name);
	this->setMovementLogic(movement_logic);
	this->setDamageDealt(damage_dealt);
};

Enemy::~Enemy() {
	/*
	NOTE:
		- Empty for now
	*/
}

/*
SECTION 2A: SETTERS
*/

bool Enemy::setName(string name) {
	bool success = true;

	this->name = name;

	return success;
}

bool Enemy::setMovementLogic(Movement movement_logic) {
	bool success = true;

	this->movement_logic = { movement_logic.spawn_x, movement_logic.y_direction_velocity, movement_logic.x_max_displacement, movement_logic.y_max_displacement };

	return success;
}

bool Enemy::setDamageDealt(Damage damage_dealt) {
	bool success = true;

	this->damage_dealt = {damage_dealt.attack, damage_dealt.collision, damage_dealt.self_destruct};

	return success;
}

/*
SECTION 2B: GETTERS
*/

string Enemy::getName() { return this->name; };
Movement Enemy::getMovementLogic() { return this->movement_logic; };
Damage Enemy::getDamageDealt() { return this->damage_dealt; };

/*
SECTION 3: OTHER FUNCTIONS
*/

void Enemy::run() {
	const int PIXEL_ERROR = 4;

	/* 
	NOTE:
		- As Enemy spawns, it has the max x-displacement to the right,
		and by default it will be facing towards the Right.
		
		- Enemy keeps running within their boundary if Enemy is 
		within their movement boundary
		
		- Else setX() back into boundary if Player knock Enemy out of 
		movement zone.

		- The first if-statement checks whether the Enemy is within
		their default spawn_x coordinate and x_max_displacement boundary
	*/

	if (this->getX() > this->getMovementLogic().spawn_x && this->getX() < this->getMovementLogic().spawn_x + this->getMovementLogic().x_max_displacement) {
		/*
			NOTE:
				- Check for Direction facing to continue its movement in that direction.

				- While in that running in that direction, if there is an obstacle, stops running and returns.

				- NEEDS TO IMPLEMENT: Prevention of Enemy falling into a hole/gap
		*/
		
		if (this->getDirectionFacing() == Direction::RIGHT && this->getX() + this->getRunSpeed() < this->getMovementLogic().spawn_x + this->getMovementLogic().x_max_displacement) {
			

			if (!this->checkCollision(*this)) {
				this->setX(this->getX() + this->getMovementLogic().x_direction_velocity);
				return;
			}
			else {
				return;
			}
		}

		else if (this->getDirectionFacing() == Direction::LEFT && this->getX() - this->getRunSpeed() > this->getMovementLogic().spawn_x) {
			if (!this->checkCollision(*this)) {
				this->setX(this->getX() - this->getMovementLogic().x_direction_velocity);
				return;
			}
			else {
				return;
			}
		}
		
		else if ((this->getDirectionFacing() == Direction::RIGHT && this->getX() + this->getRunSpeed() <= this->getMovementLogic().spawn_x + this->getMovementLogic().x_max_displacement + 4 && this->getX() + this->getRunSpeed() >= this->getMovementLogic().spawn_x - this->getMovementLogic().x_max_displacement - 4)) {

			this->setRunningState(false);
			/*
			NOTE:
				- The following code that sets the x-coordinate to ensure 
				if the Enemy crosses or comes close to its boundary, it is 
				set exactly upon the boundary, facing inwards of the boundary
				towards the other end.
			*/

			this->setX(this->getMovementLogic().spawn_x + this->getMovementLogic().x_max_displacement);
			this->setDirectionFacing(Direction::LEFT);
			return;
		}

		else if ((this->getDirectionFacing() == Direction::LEFT && this->getX() - this->getRunSpeed() >= this->getMovementLogic().spawn_x - PIXEL_ERROR && this->getX() - this->getRunSpeed() <= this->getMovementLogic().spawn_x + PIXEL_ERROR)) {
			this->setRunningState(false);
			/*
			NOTE:
				- The following code that sets the x-coordinate is basically saying
				that we don't want the Enemy leaving its spawn_x boundary.
			*/
			this->setX(this->getMovementLogic().spawn_x);
			this->setDirectionFacing(Direction::RIGHT);
			return;
		}
	}
	else {
		/*
		NOTE:
			- This else-condition sees whether the Enemy has been knocked 
			back by the Player or Obstacle, hence it sets the current position
			of the Enemy as its new spawn_x.
		*/
		
		Movement new_logic;
		new_logic.spawn_x = this->getX();
		new_logic.spawn_y = this->getY();
		new_logic.x_direction_velocity = this->getMovementLogic().x_direction_velocity;
		new_logic.x_max_displacement = this->getMovementLogic().x_max_displacement;
		new_logic.y_direction_velocity = this->getMovementLogic().y_direction_velocity;
		new_logic.y_max_displacement = this->getMovementLogic().y_max_displacement;


		this->setMovementLogic(new_logic);
	}
}

void Enemy::jump() {
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
				- In a static jump, the jump continues until max jump height is reached

				- During this jump, gravitational acceleration is in effect, slowing
				the Enemy's jump/vertical velocity nearing the max jump height.

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
		- Condition checks collision of a vertical wall that 
		requires Enemy to Jump.

	*/
	else if (!this->isJumping() && this->checkCollision(*this) && this->isRunning()) {
		this->setJumpingState(true);
		this->setRunningState(false);
		this->setVerticalVelocity(this->getInitialJumpVelocity());
		this->setVerticalUpdateInterval(0);
	}
}

void Enemy::move() {
	this->run();
	this->jump();
}
