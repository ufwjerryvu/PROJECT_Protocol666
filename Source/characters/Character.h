#pragma once

#include <Systems.h>

#include <Coordinates.h>
#include <Sprite.h>
#include <Runnable.h>
#include <Rollable.h>
#include <Jumpable.h>
#include <Fallable.h>
#include <Collidable.h>
#include <Animation.h>
#include <Animator.h>
#include <Ground.h>

class Gameplay;

struct Damage {
	/*
	NOTE:
		- Damage structure is used to store the damage dealt by the Enemy
		to the Player.

		- 'attack' is the damage dealt by the Enemy's attack.

		- 'collision' is the damage dealt by the Enemy's collision with the Player.
	*/

	int attack;
	int collision;
};

struct Knockback {
    /*
    NOTE:
        - Knockback structure is used to store the knockback dealt by the Enemy
        to the Player.

        - 'attack' is the knockback dealt by the Enemy's attack.

        - 'collision' is the knockback dealt by the Enemy's collision with the Player.
    */

    int attack;
    int collision;
};

class Character : virtual public Sprite, virtual public Runnable,
        virtual public Jumpable, virtual public Fallable, 
        virtual public Collidable
{
private:
    Gameplay *context;
    Animator<string> animator;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Character(Gameplay *context);
    ~Character();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setAnimator(Animator<string> animator);
    Gameplay *getContext();
    Animator<string> &getAnimator();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual bool collide(vector<Ground *> &args) = 0;
    // virtual bool collide(vector<Platform>& args) = 0;

    virtual void run() = 0;
    virtual void jump() = 0;
    void fall();
    virtual void move() = 0;

    virtual void update() = 0;
    void render();
};