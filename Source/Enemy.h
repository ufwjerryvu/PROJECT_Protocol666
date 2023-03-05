/*
@ COLLABORATORS: Khanh Nguyen
@ CLASS DESIGNERS: Khanh Nguyen
*/

#pragma once

#include "LIBDECLARATIONS.h"

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
	Enemy(int x, int y, Animation animation, string name, Movement movement_logic, Damage damage_dealt);
	~Enemy();

	/*
	SECTION 2A: SETTERS
	*/
	bool setName(string name);
	bool setMovementLogic(Movement movement_logic);
	bool setDamageDealt(Damage damage_dealt);
	bool setAttackDamage(int attack_damage);

	/*
	SECTION 2B: GETTERS
	*/
	string getName();
	Movement getMovementLogic();
	Damage getDamageDealt();
	int getAttackDamage();

	/*
	SECTION 3: OTHER METHODS
	*/
	void collide(vector<Ground>& args);
	void collide(vector<Platform>& args);

	bool atPlatformBoundary(vector<Platform>& platforms);
	bool atGroundBoundary(vector<Ground>& grounds);

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
	
	this->setName("Default");
	
	Movement default_logic = {0, 0, 0, 0, 0, 0};

	this->setMovementLogic(default_logic);

	Damage default_damage = {0, 0, 0};

	this->setDamageDealt(default_damage);
};

Enemy::Enemy(int x, int y, Animation animation, string name, Movement movement_logic, Damage damage_dealt)
	: Character(x, y, animation) {
	this->setName(name);
	this->setMovementLogic(movement_logic);
	this->setDamageDealt(damage_dealt);

	/* 
	NOTE: 
		- By default, Enemy needs to be facing the right as 
		they spawn, to ensure the consistency of their movement.
	*/

	this->setDirectionFacing(Direction::RIGHT);
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

	this->movement_logic = { movement_logic.spawn_x, movement_logic.spawn_y, movement_logic.x_max_displacement, movement_logic.y_max_displacement, movement_logic.x_direction_velocity, movement_logic.y_direction_velocity };

	return success;
}

bool Enemy::setDamageDealt(Damage damage_dealt) {
	bool success = true;

	this->damage_dealt = {damage_dealt.attack, damage_dealt.collision, damage_dealt.self_destruct};

	return success;
}

bool Enemy::setAttackDamage(int attack_damage) {
	bool success = true;

	Damage temp = this->getDamageDealt();
	temp.attack = attack_damage;

	this->setDamageDealt(temp);

	return success;
}

/*
SECTION 2B: GETTERS
*/

string Enemy::getName() { return this->name; };
Movement Enemy::getMovementLogic() { return this->movement_logic; };
Damage Enemy::getDamageDealt() { return this->damage_dealt; };
int Enemy::getAttackDamage() { return this->getDamageDealt().attack; }

/*
SECTION 3: OTHER METHODS
*/

void Enemy::collide(vector<Ground>& args) {
	/*
	NOTE:
		- Code is adjusted to suit Enemy from Player.h, 
		developed by Jerry Vu.

		- Storing the current collision status of
		the Enemy into a temporary structure.
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
			if (this->getBottomBound() >= args[index].getTopBound()
				&& this->getBottomBound() <= args[index].getBottomBound()) {

				const int PIXEL_ERROR_MARGIN = 3;
				const int EXTRA_DETECTION_MARGIN = 12;

				if (this->getBottomBound() <= args[index].getTopBound()
					+ PIXEL_ERROR_MARGIN + EXTRA_DETECTION_MARGIN) {
					temp.bottom = true;
					/*
					NOTE:
						- This is to make sure that the player
						stays on top of the Ground object(s).
					*/

					this->setY(args[index].getY() - this->getHeight() + PIXEL_ERROR_MARGIN);
				}
			}
		}
		/*
		NOTE:
			- Finally setting the collision directions
			for the Enemy.
		*/

		this->setCollision(temp);
	}
}

void Enemy::collide(vector<Platform>& args) {
	/*
	NOTE:
		- Having a temporary structure storing the current
		collision status of the Enemy.
	*/

	Collision temp = this->getCollisionDirections();

	/*
	NOTE:
		- Looping through the blocks of Platform and setting only
		the collision flag for the bottom bound of the Enemy
		since general enemies, such as Goons, will not be jumping
		to detect collision in any other direction.
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
			for the Enemy.
		*/
		this->setCollision(temp);
	}
}

bool Enemy::atPlatformBoundary(vector<Platform>& platforms) {
	/*
	NOTE:
		- at_platform_edge is a boolean indicating whether 
		the Enemy is near the edge of the Platform, where it 
		would fall if it continues walking in its current direction.

		- potential_platform checks for all platforms that has
		the current y-level as the Enemy.

		- current_platform_found and index_of_current_platform is 
		used to traverse through the platforms vector and identify 
		which specific platform is the Enemy currently on to 
		detect its boundary (left and right bound).
	*/
	
	bool at_platform_edge = false;

	vector<int> potential_platforms;
	bool current_platform_found = false;
	int index_of_current_platform;

	for (int i = 0; i < platforms.size(); i++) {
		if (platforms[i].getTopBound() <= this->getBottomBound()) {
			/*
			NOTE:
				- This loop is inefficient as it detects any platform
				that is under the y-level of the current Enemy, however
				this is to prevent the Enemy to continuously walk in one
				direction mid-air, passing another platform.
			*/

			potential_platforms.push_back(i);
		}
	}
	
	for (int j = 0; j < potential_platforms.size(); j++) {
		if (this->getX() > platforms[potential_platforms[j]].getLeftBound() - this->getRunSpeed() && this->getX() < platforms[potential_platforms[j]].getRightBound() + this->getRunSpeed()) {
			/*
			NOTE:
				- Checks for the left and right boundary to identify
				which platform is the current platform that the Enemy 
				is standing on or floating above.
			*/
			
			index_of_current_platform = j;
			current_platform_found = true;
			break;
		}
	}
	
	/*
	NOTE:
		- If no platforms are identified for the Enemy, by default
		the Enemy is not at the edge of any platform.
	*/

	if (!current_platform_found) {
		return at_platform_edge;
	}

	/*
	NOTE:
		- Platforms are detected, Enemy must now check if its bounds 
		to return whether the Enemy is at the platform's boundary.
	*/

	if (this->getRightBound() >= platforms.at(index_of_current_platform).getRightBound() || this->getLeftBound() <= platforms.at(index_of_current_platform).getLeftBound()) {
		at_platform_edge = true;
	}

	return at_platform_edge;
}

bool Enemy::atGroundBoundary(vector<Ground>& grounds) {
	/* 
	NOTE:
		- In cases of having multiple Ground in the vector,
		this function detects its boundary and prevent the
		Character from falling at its boundaries.
	*/

	bool at_ground_edge = false;

	vector<int> potential_grounds;
	int index_of_current_ground = 0;
	bool current_ground_found = false;

	if (this->getX() <= 0 || this->getX() >= this->getLevelWidth()) {
		/* 
		NOTE:
			- First check to see if the Enemy is going out of the screen.
		*/

		at_ground_edge = true;
		return at_ground_edge;
	}

	for (int i = 0; i < grounds.size(); i++) {
		if (grounds[i].getTopBound() <= this->getBottomBound()) {
			/*
			NOTE: 
				- Find Ground instances that are under the Enemy y-level.
			*/

			potential_grounds.push_back(i);
		}
	}

	for (int j = 0; j < potential_grounds.size(); j++) {
		if (this->getX() > grounds[potential_grounds[j]].getLeftBound() - this->getRunSpeed() && this->getX() < grounds[potential_grounds[j]].getRightBound() + this->getRunSpeed()) {
			/*
			NOTE:
				- Find the Ground instance that has the Enemy
				within boundary
			*/

			index_of_current_ground = j;
			current_ground_found = true;
			break;
		}
	}

	if (!current_ground_found) {
		return at_ground_edge;
	}

	if (this->getX() >= grounds.at(index_of_current_ground).getRightBound() || this->getX() <= grounds.at(index_of_current_ground).getLeftBound()) {
		/*
		NOTE:
			- Check if the Enemy is at the Ground instance's boundary
		*/
		at_ground_edge = true;
	}

	return at_ground_edge;
}

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

	if (this->getX() < this->getMovementLogic().spawn_x - PIXEL_ERROR || this->getX() > this->getMovementLogic().spawn_x + this->getMovementLogic().x_max_displacement + PIXEL_ERROR) {
		/*
			NOTE:
				- Check for Direction facing to continue its movement in that direction.

				- While in that running in that direction, if there is an obstacle, stops running and returns.
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
	
	else if (this->getDirectionFacing() == Direction::RIGHT && this->getX() + this->getRunSpeed() < this->getMovementLogic().spawn_x + this->getMovementLogic().x_max_displacement) {
		/*
		NOTE:
			- Moving right, not at the right boundary for movement logic
		*/

		this->setRunningState(true);
		this->setX(this->getX() + this->getRunSpeed());
		return;
	}

	else if (this->getDirectionFacing() == Direction::LEFT && this->getX() - this->getRunSpeed() > this->getMovementLogic().spawn_x) {
		/*
		NOTE:
			- Moving left, not at the left boundary for movement logic
		*/
		this->setRunningState(true);
		this->setX(this->getX() - this->getRunSpeed());
		return;
	}

	else if (this->getDirectionFacing() == Direction::RIGHT && this->getX() + this->getRunSpeed() >= this->getMovementLogic().spawn_x + this->getMovementLogic().x_max_displacement) {
		this->setRunningState(false);
		/*
		NOTE:
			- The following code that sets the x-coordinate to ensure
			if the Enemy crosses or comes close to its boundary, its position, 
			direction facing is set inwards into the boundary, towards 
			the other end.
		*/

		this->setX(this->getMovementLogic().spawn_x + this->getMovementLogic().x_max_displacement - PIXEL_ERROR);
		this->setDirectionFacing(Direction::LEFT);
		return;
	}

	else if (this->getDirectionFacing() == Direction::LEFT && this->getX() - this->getRunSpeed() <= this->getMovementLogic().spawn_x) {
		this->setRunningState(false);
		/*
		NOTE:
			- The following code that sets the x-coordinate is basically saying
			that we don't want the Enemy leaving its spawn_x boundary.
		*/

		this->setX(this->getMovementLogic().spawn_x + PIXEL_ERROR);
		this->setDirectionFacing(Direction::RIGHT);
		return;
	}
}

void Enemy::jump() {}

void Enemy::move() {
	if (!this->isJumping()) {
		this->fall();
	}

	if (!this->isAttacking()) {
		this->run();
	}
}
