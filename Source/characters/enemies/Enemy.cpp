#include "Enemy.h"

#include <Gameplay.h>
#include <Master.h>

/*
SECTION 1: CONSTRUCTOR AND DESTRUCTORS
*/
Enemy::Enemy(Gameplay *context) : Character(context) {
	this->setDamageDealt(damage_dealt);
	// this->setKnockback(knockback); To be implemented

	/* 
	NOTE: 
		- By default, Enemy needs to be facing the right as 
		they spawn, to ensure the consistency of their movement.
	*/
	this->setUpdateInterval(0);
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

bool Enemy::setDamageDealt(Damage damage_dealt) {
	bool success = true;

	this->damage_dealt = { damage_dealt.attack, damage_dealt.collision };

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

bool Enemy::setAttackRange(int attack_range) {
	bool success = true;

	this->attack_range = attack_range;

	return success;
}

/*
SECTION 2B: GETTERS
*/

Damage Enemy::getDamageDealt() { return this->damage_dealt; };
int Enemy::getAttackDamage() { return this->getDamageDealt().attack; };
int Enemy::getUpdateInterval() { return this->update_interval; };
int Enemy::getAttackRange() { return this->attack_range; };

/*
SECTION 3: OTHER METHODS
*/

bool Enemy::collide(vector<Ground *> &args) 
{
	/*
	NOTE:
		- Code taken from Player's collide() function, as collision
		detection is similar for both Player and Enemy.
	*/

	/*
	NOTE:
		- Looping through the `Ground` blocks and setting the collision flags to
		whichever direction that collision is detected in.
	*/
	for (int i = 0; i < args.size(); i++)
	{
		if (this->Collidable::checkCollision(*args[i]))
		{
			/*
			NOTE:
				- Detecting collision on the left.
			*/
			if (this->getLeftBound() <= (*args[i]).getRightBound() &&
				this->getLeftBound() >= (*args[i]).getLeftBound())
			{
				this->Collidable::setCollisionDirection(Direction::LEFT, true);
			}

			/*
			NOTE:
				- Detecting collision on the right.
			*/
			if (this->getRightBound() >= (*args[i]).getLeftBound() &&
				this->getRightBound() <= (*args[i]).getRightBound())
			{
				this->Collidable::setCollisionDirection(Direction::RIGHT, true);
			}

			/*
			NOTE:
				- Detecting collision at the bottom.
			*/
			if (this->getBottomBound() >= (*args[i]).getTopBound() &&
				this->getBottomBound() <= (*args[i]).getBottomBound())
			{
				this->Collidable::setCollisionDirection(Direction::DOWN, true);

				/*
				NOTE:
					- This is to make sure that the player stays on top of the
					`Ground` object(s).
				*/

				const int PIXEL_ERROR_MARGIN = 3;
				Coordinates &position = this->getAbsolutePosition();

				position.setY((*args[i]).getAbsolutePosition().getY() -
							  this->getHeight() + PIXEL_ERROR_MARGIN);
			}
		}
	}
}

bool Enemy::collide(vector<Platform *> &args) 
{
	/*
	NOTE:
		- Looping through the blocks of `Platform` and setting only the collision
		flag for the bottom bound of the player because the player can basically
		jump up through a platform but once they jump over the platform they can
		rest on the platform.
	*/
	for (int index = 0; index < args.size(); index++)
	{
		if ((*args[index]).checkCollision((*this)))
		{
			if (this->getBottomBound() >= (*args[index]).getTopBound() &&
				this->getBottomBound() <= (*args[index]).getBottomBound())
			{

				/*
				NOTE:
					- Adding the extra collision detection margin is sort of a
					band- aid solution but this code is to prevent the player
					from catapulting upwards jumping halfway through the platform.
				*/
				const int PIXEL_ERROR_MARGIN = 3;
				const int EXTRA_DETECTION_MARGIN = 12;
				if (this->getBottomBound() <= (*args[index]).getTopBound() +
												  PIXEL_ERROR_MARGIN + EXTRA_DETECTION_MARGIN)
				{
					this->setCollisionDirection(Direction::DOWN, true);
				}
				/*
				NOTE:
					- This is to make sure that the player stays on top of the
					platform.
				*/
				if (!this->isJumping() && this->checkCollisionDirection(Direction::DOWN))
				{
					Coordinates &position = this->getAbsolutePosition();
					position.setY((*args[index]).getAbsolutePosition().getY() -
								  this->getHeight() + PIXEL_ERROR_MARGIN);
				}
			}
		}
	}
}

/*
NOTE:
	- To be implemented later, undecided on its necessity.
*/

// bool Enemy::atPlatformBoundary(vector<Platform>& platforms) {
// 	/*
// 	NOTE:
// 		- at_platform_edge is a boolean indicating whether 
// 		the Enemy is near the edge of the Platform, where it 
// 		would fall if it continues walking in its current direction.

// 		- potential_platform checks for all platforms that has
// 		the current y-level as the Enemy.

// 		- current_platform_found and index_of_current_platform is 
// 		used to traverse through the platforms vector and identify 
// 		which specific platform is the Enemy currently on to 
// 		detect its boundary (left and right bound).
// 	*/
// 	const int PIXEL_RANGE = 5;

// 	bool at_platform_edge = false;

// 	vector<int> potential_platforms;
// 	bool current_platform_found = false;
// 	int index_of_current_platform = 0;

// 	for (int i = 0; i < platforms.size(); i++) {
// 		if (this->getBottomBound() >= platforms[i].getTopBound() - PIXEL_RANGE && this->getBottomBound() <= platforms[i].getTopBound() + PIXEL_RANGE) {
// 			/*
// 			NOTE:
// 				- This loop is inefficient as it detects any platform
// 				that is under the y-level of the current Enemy, however
// 				this is to prevent the Enemy to continuously walk in one
// 				direction mid-air, passing another platform.
// 			*/

// 			potential_platforms.push_back(i);
// 		}
// 	}
	
// 	for (int j = 0; j < potential_platforms.size(); j++) {
// 		if (this->getLeftBound() > platforms[potential_platforms[j]].getLeftBound() - PIXEL_RANGE && this->getRightBound() < platforms[potential_platforms[j]].getRightBound() + PIXEL_RANGE) {
// 			/*
// 			NOTE:
// 				- Checks for the left and right boundary to identify
// 				which platform is the current platform that the Enemy 
// 				is standing on or floating above.
// 			*/
			
// 			index_of_current_platform = potential_platforms[j];
// 			current_platform_found = true;
// 			break;
// 		}
// 	}
	
// 	/*
// 	NOTE:
// 		- If no platforms are identified for the Enemy, by default
// 		the Enemy is not at the edge of any platform.
// 	*/

// 	if (!current_platform_found) {
// 		return at_platform_edge;
// 	}

// 	/*
// 	NOTE:
// 		- Platforms are detected, Enemy must now check if its bounds 
// 		to return whether the Enemy is at the platform's boundary.
// 	*/

// 	if (this->getRightBound() >= platforms[index_of_current_platform].getRightBound() - PIXEL_RANGE || this->getLeftBound() <= platforms[index_of_current_platform].getLeftBound() + PIXEL_RANGE) {
// 		at_platform_edge = true;
// 		cout << "Platform edge" << endl;
// 		cout << "Plat right bound: " << platforms.at(index_of_current_platform).getRightBound() << endl << "Plat left bound: " << platforms.at(index_of_current_platform).getLeftBound() << endl << "Plat top: " << platforms.at(index_of_current_platform).getTopBound() << endl << "Plat X: " << platforms.at(index_of_current_platform).getX() << endl << "Plat Y: " << platforms.at(index_of_current_platform).getY() << endl << endl;
		
// 		cout << "Enemy right: " << this->getRightBound() << endl << "Enemy left: " << this->getLeftBound() << endl << "Enemy bottom: " << this->getBottomBound() << endl << "Enemy x: " << this->getX() << endl << "Enemy y: " << this->getY() << endl << endl;
// 	}

// 	return at_platform_edge;
// }

// bool Enemy::atGroundBoundary(vector<Ground>& grounds) {
// 	/* 
// 	NOTE:
// 		- In cases of having multiple Ground in the vector,
// 		this function detects its boundary and prevent the
// 		Character from falling at its boundaries.
// 	*/
// 	const int PIXEL_RANGE = 8;
	
// 	bool at_ground_edge = false;

// 	vector<int> potential_grounds;
// 	int index_of_current_ground = 0;
// 	bool current_ground_found = false;

// 	if (this->getX() <= 0 || this->getX() >= this->getLevelWidth()) {
// 		/* 
// 		NOTE:
// 			- First check to see if the Enemy is going out of the screen.
// 		*/

// 		at_ground_edge = true;
// 		return at_ground_edge;
// 	}

// 	for (int i = 0; i < grounds.size(); i++) {
// 		if (this->getBottomBound() >= grounds[i].getTopBound() - PIXEL_RANGE && this->getBottomBound() <= grounds[i].getTopBound() + PIXEL_RANGE) {
// 			/*
// 			NOTE: 
// 				- Find Ground instances that are under the Enemy y-level.
// 			*/

// 			potential_grounds.push_back(i);
// 		}
// 	}

// 	for (int j = 0; j < potential_grounds.size(); j++) {
// 		if (this->getLeftBound() > grounds[potential_grounds[j]].getLeftBound() - PIXEL_RANGE && this->getRightBound() < grounds[potential_grounds[j]].getRightBound() + PIXEL_RANGE) {
// 			/*
// 			NOTE:
// 				- Find the Ground instance that has the Enemy
// 				within boundary
// 			*/

// 			index_of_current_ground = potential_grounds[j];
// 			current_ground_found = true;
// 			break;
// 		}
// 	}

// 	if (!current_ground_found) {
// 		return at_ground_edge;
// 	}

// 	if (this->getRightBound() >= grounds.at(index_of_current_ground).getRightBound() - PIXEL_RANGE || this->getX() <= grounds.at(index_of_current_ground).getLeftBound() + PIXEL_RANGE) {
// 		/*
// 		NOTE:
// 			- Check if the Enemy is at the Ground instance's boundary
// 		*/
// 		at_ground_edge = true;
// 		cout << "Ground edge" << endl;
// 	}

// 	return at_ground_edge;
// }

void Enemy::run() {
	this->setRunning(true);
	Coordinates &position = this->getAbsolutePosition();
	/*
	NOTE:
		- This function is kept simple, to keep the Enemy moving
		in its current direction.
	*/
	if (this->getDirectionFacing() == Direction::LEFT) {
		position.setX(position.getX() - this->Runnable::getSpeed());
	}
	else if (this->getDirectionFacing() == Direction::RIGHT) {
		position.setX(position.getX() + this->Runnable::getSpeed());
	}
}

void Enemy::jump() {
	/*
	NOTE:
		- This function is kept similar to the Player's jump() function,
		for simplicity and consistency. 

		- Changes will be considered as progress is made.
	*/
	if (this->isJumping())
	{
		/*
		NOTE:
			- If the character is jumping mid air, `jump()` continues to increase the y
			coordinate of this player.
		*/

		if (this->Verticality::getVelocity() == 0)
		{
			/*
			NOTE:
				- Jump is at its highest point, calls off the jump() function
			*/
			this->setJumping(false);
			this->setFalling(true);
			this->Verticality::reset();
			this->Verticality::setVelocity(0);
		}

		else if (this->Verticality::getVelocity() > 0)
		{
			/*
			NOTE:
				- In a static jump, if 'W' key is pressed, the jump continues until
				max jump height is reached

				- During this jump, gravitational acceleration is in effect, slowing
				the player's jump/vertical velocity nearing the max jump height.

				- A frame update interval is added to demonstrate the deceleration of
				the vertical velocity as vertical velocity can only be change once
				a frame update interval is met.

			*/

			if (this->Verticality::getCounter() >= this->Verticality::getInterval())
			{
				this->Verticality::setVelocity(this->Verticality::getVelocity() -
											   this->Fallable::getGravitationalAcceleration());
				this->Verticality::reset();
			}

			else
			{
				this->Verticality::increment();
				Coordinates &position = this->getAbsolutePosition();
				position.setY(position.getY() - this->Verticality::getVelocity());
			}
		}
	}
}

void Enemy::move() {
	/*
	NOTE:
		- Move() function is kept similar to the Player's move() function.
		
		- Jump() will be called in the condition that the Enemy is already
		jumping, which jump() will be called respectively to their enemy 
		class.

		- By default, the Enemy is set to run() at all times, except while
		attacking Player.
	*/
	if (!this->isJumping() && this->getAbsolutePosition().getY() <= this->getContext()->getLevelHeight()) {
		this->fall();
	}

	if (this->isJumping()) {
		this->jump();
	}

	/*
	NOTE:
		- To be implemented later when Attackable is implemented.
	*/
	// if (!this->isAttacking()) {
	// 	this->run();
	// }

}