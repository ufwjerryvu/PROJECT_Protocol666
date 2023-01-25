/*
@ COLLABORATORS: An Nguyen, Jerry Vu, An Luu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

enum class Direction {
    NONE,
    LEFT, 
    RIGHT,
    UP,
    DOWN
};

struct Animation {
    vector<SDL_Texture*> frames_idle;
    vector<SDL_Texture*> frames_running;

    int current_frame_idle;
    int current_frame_running;
};

class Character : public Sprite {
private:
    Animation animation;

    Direction facing_direction;

    bool is_running;
    bool is_attacking;

    /*
    NOTE :
        -Speed is in pixels per frame.

        - Maximum jump height is in pixels.
    */
    int run_speed;
    int max_jump_height;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Character();
    Character(int x, int y, Animation animation);
    ~Character();

    /*
    SECTION 2A: SETTERS
    */
    bool setAnimation(Animation animation);
    bool setDirectionFacing(Direction facing);
    bool setRunningState(bool is_running);
    bool setAttackingState(bool is_attacking);
    bool setRunSpeed(int pixels_per_frame);
    bool setMaxJumpHeight(int pixels);

    /*
    SECTION 2B: GETTERS
    */
    Animation getAnimation();
    Direction getDirectionFacing();
    bool isRunning();
    bool isAttacking();
    int getRunSpeed();
    int getMaxJumpHeight();

    /*
    SECTION 3: OTHER METHODS
    */
    
    /*
    NOTE:
        - The move() function will contain the run() and
        jump() functions.
    */
    virtual void run() = 0;
    virtual void jump() = 0;
    virtual void move() = 0;

    virtual void setNextFrame() = 0;
    virtual void update() = 0;
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Character::Character() : Sprite() {
    /*
    NOTE:
        - This constructor calls the default constructor of the base
        class `Sprite`, initializing everything to the default values.

        - Do not call the default constructor if not needed.
    */
    this->setDirectionFacing(Direction::NONE);

    this->setRunningState(false);
    this->setAttackingState(false);

    this->setRunSpeed(0);
    this->setMaxJumpHeight(0);
}

Character::Character(int x, int y, Animation animation) : Sprite(x, y, NULL) {
    this->setAnimation(animation);
    
    /*
    NOTE:
        - Setting the character to the first idle
        frame as soon as they are created.
    */
    if (animation.frames_idle.size() > 0) {
        this->setTexture(animation.frames_idle[0]);
    }

    this->setDirectionFacing(Direction::NONE);

    this->setRunningState(false);
    this->setAttackingState(false);

    this->setRunSpeed(0);
    this->setMaxJumpHeight(0);

    this->animation.current_frame_idle = 0;
    this->animation.current_frame_running = 0;
}

Character::~Character() {
    /*
    NOTE:
        - Empty for now.
    */
}

/*
SECTION 2A: SETTERS
*/
bool Character::setAnimation(Animation animation) {
    bool success = true;

    /*
    NOTE:
        - We add this layer of security to check if the vector 
        for idle frames is empty.
    */

    if (animation.frames_idle.size() <= 0) {
        cerr << "Error from Character::setAnimation(): no elements "
            << "are present in the frames_idle vector." << endl;
        success = false;
        return success;
    }

    /*
    NOTE:
        - Again, if any of the textures in the vector is
        NULL then the method returns false.
    */
    for (int index = 0; index < this->animation.frames_idle.size(); index++) {
        if (this->animation.frames_idle[index] == NULL) {
            cerr << "Error from Character::setAnimation(): a null "
                << "pointer has been detected in the frames_idle vector." << endl;
            success = false;
            return success;
        }
    }

    /*
    NOTE:
    - We add this layer of security to check if the vector
    for running frames is empty.
    */

    if (animation.frames_running.size() <= 0) {
        cerr << "Error from Character::setAnimation(): no elements "
            << "are present in the frames_running vector." << endl;
        success = false;
        return success;
    }

    /*
    NOTE:
        - Again, if any of the textures in the vector is
        NULL then the method returns false.
    */
    for (int index = 0; index < this->animation.frames_running.size(); index++) {
        if (this->animation.frames_running[index] == NULL) {
            cerr << "Error from Character::setAnimation(): a null "
                << "pointer has been detected in the frames_running vector." << endl;
            success = false;
            return success;
        }
    }

    this->animation = animation;

    return success;
}

bool Character::setDirectionFacing(Direction facing) {
    bool success = true;

    this->facing_direction = facing;

    return true;
}

bool Character::setRunningState(bool is_running) {
    bool success = true;

    /*
    NOTE:
        - `is_moving` is synonymous with `is_running`.
        They are interchangeable.
    */
    this->is_running = is_running;

    return success;
}

bool Character::setAttackingState(bool is_attacking) {
    bool success = true;

    this->is_attacking = is_attacking;

    return success;
}

bool Character::setRunSpeed(int pixels_per_frame) {
    bool success = true;

    this->run_speed = pixels_per_frame;

    return true;
}

bool Character::setMaxJumpHeight(int pixels) {
    bool success = true;

    this->max_jump_height = pixels;

    return true;
}

/*
SECTION 2B: GETTERS
*/
Animation Character::getAnimation() { return this->animation; }
Direction Character::getDirectionFacing() { return this->facing_direction; }
bool Character::isRunning() { return this->is_running; }
bool Character::isAttacking() { return this->is_attacking; }
int Character::getRunSpeed() { return this->run_speed; }
int Character::getMaxJumpHeight() { return this->max_jump_height; }

/*
SECTION 3: OTHER FUNCTIONS
*/