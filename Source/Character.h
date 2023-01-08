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
    RIGHT
};

class Character : public Sprite {
private:
    Direction facing_direction;

    bool is_moving;
    bool is_attacking;

    vector<SDL_Texture*> anm_frames_moving;
    vector<SDL_Texture*> anm_frames_idle;

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
    /*
    SECTION 2B: GETTERS
    */
    vector<SDL_Texture*> getAnimationFramesMoving();
    vector<SDL_Texture*> getAnimationFramesIdle();
    bool isMoving();
    bool isAttacking();

    /*
    SECTION 3: OTHER METHODS
    */
    virtual void setNextFrame() = 0;
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
}

Character::Character(int x, int y, vector<SDL_Texture*> anm_frames_moving, vector<SDL_Texture*> anm_frames_idle) : Sprite(x, y, NULL) {
    this->setAnimationFramesMoving(anm_frames_moving);
    this->setAnimationFramesIdle(anm_frames_idle);

    if (anm_frames_idle.size() > 0) {
        this->setTexture(anm_frames_idle[0]);
    }
}

Character::~Character() {
}

/*
SECTION 2A: SETTERS
*/
bool Character::setAnimationFramesMoving(vector<SDL_Texture*> anm_frames_moving) {
    bool success = true;

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

    for (int index = 0; index < this->anm_frames_idle.size(); index++) {
        if (this->anm_frames_idle[index] == NULL) {
            success = false;
            return success;
        }
    }

    this->anm_frames_idle = anm_frames_idle;

    return success;
}

/*
SECTION 2B: GETTERS
*/

vector<SDL_Texture*> Character::getAnimationFramesMoving() { return this->anm_frames_moving; }
vector<SDL_Texture*> Character::getAnimationFramesIdle() { return this->anm_frames_idle; }
bool Character::isMoving() { return this->is_moving; }
bool Character::isAttacking() { return this->is_attacking; }

/*
SECTION 3: OTHER FUNCTIONS
*/