#pragma once

#include <Character.h>
#include <Runnable.h>
#include <Ground.h>
#include <Platform.h>

class Enemy : public Character {
private:
	Damage damage_dealt;
	int update_interval;
	int attack_range;

	/*
	NOTE:
		- Damage_dealt is defined in Damage which is in Health Points 
		(presumed Player has 100 max HP).

		- Update_interval is used as a mechanism to delay Enemy's action, such as 
		idle rotations.

		- attack_range is the range of the Enemy's attack, which is used to detect
		Player's presence in the Enemy's range of attack.
	*/

public:
	/*
	SECTION 1: CONSTRUCTOR AND DESTRUCTORS
	*/
	Enemy();
	Enemy(Gameplay *gameplay);
	~Enemy();

	/*
	SECTION 2A: SETTERS
	*/
	void setDamageDealt(Damage damage_dealt);
	void setAttackDamage(int attack_damage);
	void setUpdateInterval(int update_interval);
	void setAttackRange(int attack_range);

	/*
	SECTION 2B: GETTERS
	*/
	Damage getDamageDealt();
	int getAttackDamage();
	int getUpdateInterval();
	int getAttackRange();

	/*
	SECTION 3: OTHER METHODS
	*/
	bool collide(vector<Ground *> &args);
	bool collide(vector<Platform *> &args);
	
	/*
	NOTE:
		- atPlatformBoundary() and atGroundBoundary() are used to detect the boundary
		of the Enemy, where the Enemy would fall if it continues walking in its current
		direction.

		- Temporarily disabled, for its use is not yet implemented.

	bool atPlatformBoundary(vector<Platform>& platforms);
	bool atGroundBoundary(vector<Ground>& grounds); 
	*/
	virtual void attack() = 0;

	void run();
	void jump();
	void move();

	/*
	NOTE:
		- chasePlayer() is virtual, potentially, as different Enemy
		has different field of vision.

		- Attack() is virtual, potentially, since different Enemy has 
		different attacks (Range, Melee, etc...).
	*/

	virtual void chasePlayer(Player& player, vector<Ground>& grounds, vector<Platform>& platforms) = 0;
	
};