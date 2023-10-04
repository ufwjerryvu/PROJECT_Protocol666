/*
@ COLLABORATORS: Khanh Nguyen
@ CLASS DESIGNERS: Khanh Nguyen
*/

#pragma once

#include "../Players/Player.h"

class Enemy : public Character {
private:
	string name;
	Movement movement_logic;
	Damage damage_dealt;
	int update_interval;

	/*
	NOTE:
		- `name` is the Enemy's categorized names (e.g., Zombie, Raider, etc.)

		- `movement_logic` is defined in the Movement structure which its unit
		is in pixels.

		- Similarly, `damage_dealt` is defined in the Damage structure which 
		is in Health Points (presumed Player has 100 max HP).

		- `update_interval` is used as a mechanism to delay an Enemy's action, such as 
		idle rotations.
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
	bool setUpdateInterval(int update_interval);

	/*
	SECTION 2B: GETTERS
	*/
	string getName();
	Movement getMovementLogic();
	Damage getDamageDealt();
	int getAttackDamage();
	int getUpdateInterval();

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
		different attacks (Range, Melee, etc...).
	*/

	virtual void detectPlayer(Player& player, vector<Ground>& grounds, vector<Platform>& platforms) = 0;
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

	this->setUpdateInterval(0);
};

Enemy::Enemy(int x, int y, Animation animation, string name, Movement movement_logic, Damage damage_dealt)
	: Character(x, y, animation) {
	this->setName(name);
	this->setMovementLogic(movement_logic);
	this->setDamageDealt(damage_dealt);
	this->setUpdateInterval(0);

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

bool Enemy::setUpdateInterval(int update_interval) {
	bool success = true;

	this->update_interval = update_interval;

	return success;
}

/*
SECTION 2B: GETTERS
*/

string Enemy::getName() { return this->name; };
Movement Enemy::getMovementLogic() { return this->movement_logic; };
Damage Enemy::getDamageDealt() { return this->damage_dealt; };
int Enemy::getAttackDamage() { return this->getDamageDealt().attack; }
int Enemy::getUpdateInterval() { return this->update_interval; };

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
	const int PIXEL_RANGE = 5;

	bool at_platform_edge = false;

	vector<int> potential_platforms;
	bool current_platform_found = false;
	int index_of_current_platform = 0;

	for (int i = 0; i < platforms.size(); i++) {
		if (this->getBottomBound() >= platforms[i].getTopBound() - PIXEL_RANGE && this->getBottomBound() <= platforms[i].getTopBound() + PIXEL_RANGE) {
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
		if (this->getLeftBound() > platforms[potential_platforms[j]].getLeftBound() - PIXEL_RANGE && this->getRightBound() < platforms[potential_platforms[j]].getRightBound() + PIXEL_RANGE) {
			/*
			NOTE:
				- Checks for the left and right boundary to identify
				which platform is the current platform that the Enemy 
				is standing on or floating above.
			*/
			
			index_of_current_platform = potential_platforms[j];
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

	if (this->getRightBound() >= platforms[index_of_current_platform].getRightBound() - PIXEL_RANGE || this->getLeftBound() <= platforms[index_of_current_platform].getLeftBound() + PIXEL_RANGE) {
		at_platform_edge = true;
		cout << "Platform edge" << endl;
		cout << "Plat right bound: " << platforms.at(index_of_current_platform).getRightBound() << endl << "Plat left bound: " << platforms.at(index_of_current_platform).getLeftBound() << endl << "Plat top: " << platforms.at(index_of_current_platform).getTopBound() << endl << "Plat X: " << platforms.at(index_of_current_platform).getX() << endl << "Plat Y: " << platforms.at(index_of_current_platform).getY() << endl << endl;
		
		cout << "Enemy right: " << this->getRightBound() << endl << "Enemy left: " << this->getLeftBound() << endl << "Enemy bottom: " << this->getBottomBound() << endl << "Enemy x: " << this->getX() << endl << "Enemy y: " << this->getY() << endl << endl;
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
	const int PIXEL_RANGE = 8;
	
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
		if (this->getBottomBound() >= grounds[i].getTopBound() - PIXEL_RANGE && this->getBottomBound() <= grounds[i].getTopBound() + PIXEL_RANGE) {
			/*
			NOTE: 
				- Find Ground instances that are under the Enemy y-level.
			*/

			potential_grounds.push_back(i);
		}
	}

	for (int j = 0; j < potential_grounds.size(); j++) {
		if (this->getLeftBound() > grounds[potential_grounds[j]].getLeftBound() - PIXEL_RANGE && this->getRightBound() < grounds[potential_grounds[j]].getRightBound() + PIXEL_RANGE) {
			/*
			NOTE:
				- Find the Ground instance that has the Enemy
				within boundary
			*/

			index_of_current_ground = potential_grounds[j];
			current_ground_found = true;
			break;
		}
	}

	if (!current_ground_found) {
		return at_ground_edge;
	}

	if (this->getRightBound() >= grounds.at(index_of_current_ground).getRightBound() - PIXEL_RANGE || this->getX() <= grounds.at(index_of_current_ground).getLeftBound() + PIXEL_RANGE) {
		/*
		NOTE:
			- Check if the Enemy is at the Ground instance's boundary
		*/
		at_ground_edge = true;
		cout << "Ground edge" << endl;
	}

	return at_ground_edge;
}

void Enemy::run() {
	this->setRunningState(true);
	if (this->getDirectionFacing() == Direction::LEFT) {
		this->setX(this->getX() - this->getRunSpeed());
	}
	else if (this->getDirectionFacing() == Direction::RIGHT) {
		this->setX(this->getX() + this->getRunSpeed());
	}
}

void Enemy::jump() {
	/*
	NOTE:
		- This function is kept similar to the Player's jump() function,
		for simplicity and consistency. 

		- Changes will be considered as progress is made.
	*/
	const int FRAME_UPDATE_INTERVAL = 3;

	if (this->isJumping()) {
		/*
		NOTE:
			- If the enemy is jumping mid air, jump() continues to increase the y
			coordinate of this enemy.
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
		- If Enemy is not mid-jump, initiate jump() sequence 
		by setting default attributes for a jump.

	*/
	else if (!this->isJumping()) {
		this->setJumpingState(true);
		this->setVerticalVelocity(this->getInitialJumpVelocity());
		this->setVerticalUpdateInterval(0);
	}
}

void Enemy::move() {
	/*
	NOTE:
		- `move()` function is kept similar to the Player's move() function.
		
		- `jump()` will be called in the condition that the Enemy is already
		jumping, which jump() will be called respectively to their enemy 
		class.

		- By default, the Enemy is set to `run()` at all times, except while
		attacking Player.
	*/
	if (!this->isJumping() && this->getY() <= this->getLevelHeight()) {
		this->fall();
	}

	if (this->isJumping()) {
		this->jump();
	}

	if (!this->isAttacking()) {
		this->run();
	}
}