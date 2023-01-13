/*
@ COLLABORATORS: An Nguyen, Jerry Vu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

enum Direction {
    NONE,
    LEFT, 
    RIGHT,
    UP,
    DOWN
};

class Character : public Sprite {
private:
    vector<SDL_Texture*> anm_frames_moving;
    vector<SDL_Texture*> anm_frames_idle;

    Direction facing_direction;

    bool is_moving;
    bool is_attacking;

    /*
    NOTE :
        -Speed is in pixels per frame.

        - Maximum jump height is in pixels.
    */
    int run_speed;
    int max_jump_height;

protected:
    int current_frame_moving;
    int current_frame_idle;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Character();
    Character(int x, int y, vector<SDL_Texture*> anm_frames_moving, vector<SDL_Texture*> anm_frames_idle);
    ~Character();

    /*
    SECTION 2A: SETTERS
    */
    bool setAnimationFramesMoving(vector<SDL_Texture*> anm_frames_moving);
    bool setAnimationFramesIdle(vector<SDL_Texture*> anm_frames_idle);
    bool setMovingState(bool is_moving);
    bool setAttackingState(bool is_attacking);
    bool setDirectionFacing(Direction facing);

    /*
    SECTION 2B: GETTERS
    */
    vector<SDL_Texture*> getAnimationFramesMoving();
    vector<SDL_Texture*> getAnimationFramesIdle();
    bool isMoving();
    bool isAttacking();
    Direction getDirectionFacing();

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
    */
    this->facing_direction = NONE;
    this->is_attacking = false;
    this->is_moving = false;
    
    this->current_frame_idle = 0;
    this->current_frame_moving = 0;

    this->run_speed = 0;
    this->max_jump_height = 0;
}

Character::Character(int x, int y, vector<SDL_Texture*> anm_frames_moving, vector<SDL_Texture*> anm_frames_idle) : Sprite(x, y, NULL) {
    this->setAnimationFramesMoving(anm_frames_moving);
    this->setAnimationFramesIdle(anm_frames_idle);
    
    /*
    NOTE:
        - Setting the character to the first idle
        frame as soon as they are created.
    */
    if (anm_frames_idle.size() > 0) {
        this->setTexture(anm_frames_idle[0]);
    }

    this->current_frame_idle = 0;
    this->current_frame_moving = 0;

    this->run_speed = 0;
    this->max_jump_height = 0;
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
bool Character::setAnimationFramesMoving(vector<SDL_Texture*> anm_frames_moving) {
    bool success = true;

    /*
    NOTE:
        - If there are no textures in the vector then
        the function will return a failure flag. I.e.,
        the vector's size is 0.
    */

    if (anm_frames_moving.size() <= 0) {
        success = false;
        return success;
    }

    /*
    NOTE:
        - And if any of the textures in the vector is
        NULL then the method returns false.
    */
    for (int index = 0; index < this->anm_frames_moving.size(); index++) {
        if (this->anm_frames_moving[index] == NULL) {
            success = false;
            return success;
        }
    }

    this->anm_frames_moving = anm_frames_moving;

    return success;
}
bool Character::setAnimationFramesIdle(vector<SDL_Texture*> anm_frames_idle) {
    bool success = true;

    /*
    NOTE:
        - Similar to setAnimationFramesMoving(), we 
        add this layer of security.
    */
    if (anm_frames_idle.size() <= 0) {
        success = false;
        return success;
    }

    /*
    NOTE:
        - Again, if any of the textures in the vector is
        NULL then the method returns false.
    */
    for (int index = 0; index < this->anm_frames_idle.size(); index++) {
        if (this->anm_frames_idle[index] == NULL) {
            success = false;
            return success;
        }
    }

    this->anm_frames_idle = anm_frames_idle;

    return success;
}

bool Character::setMovingState(bool is_moving) {
    bool success = true;

    /*
    NOTE:
        - `is_moving` is synonymous with `is_running`.
        They are interchangeable.
    */
    this->is_moving = is_moving;

    return success;
}

bool Character::setAttackingState(bool is_attacking) {
    bool success = true;

    this->is_attacking = is_attacking;

    return success;
}

bool Character::setDirectionFacing(Direction facing) {
    bool success = true;

    this->facing_direction = facing;

    return true;
}

/*
SECTION 2B: GETTERS
*/

vector<SDL_Texture*> Character::getAnimationFramesMoving() { return this->anm_frames_moving; }
vector<SDL_Texture*> Character::getAnimationFramesIdle() { return this->anm_frames_idle; }
bool Character::isMoving() { return this->is_moving; }
bool Character::isAttacking() { return this->is_attacking; }
Direction Character::getDirectionFacing() { return this->facing_direction; }

/*
SECTION 3: OTHER FUNCTIONS
*/