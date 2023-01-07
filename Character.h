/*
@ COLLABORATORS: An Nguyen
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Sprite.h"

class Character : public Sprite {
private:
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

	/*
	SECTION 3: OTHER METHODS
	*/

};


/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Character::Character() {
    /*
    NOTE:
        - Initializing everything to default values.
    */
    Sprite::setX(0);
    Sprite::setY(0);

    this->anm_frames_moving = NULL;
    this->anm_frames_idle = NULL;   
}

Character::Character(int x, int y, vector<SDL_Texture*> anm_frames_moving, vector<SDL_Texture*> anm_frames_idle) {
    Sprite::setX(int x);
    Sprite::setY(int y);
    
    this->setAnimationFramesMoving(anm_frames_moving);
    this->setAnimationFramesIdle(anm_frames_idle);
}

Character::~Character() {
}

/*
SECTION 2A: SETTERS
*/
bool Character::setAnimationFramesMoving(vector<SDL_Texture*> anm_frames_moving) {
    bool success = true;

    if (anm_frames_moving == NULL) {
        success = false;
    }

	this->anm_frames_moving = anm_frames_moving;
	
    return success;
}
bool Character::setAnimationFramesIdle(vector<SDL_Texture*> anm_frames_idle) {
    bool success = true;

    if (anm_frames_idle == NULL) {
        success = false;
    }

	this->anm_frames_idle = anm_frames_idle;
	
    return success;
}

/*
SECTION 2B: GETTERS
*/

vector<SDL_Texture*> Character::getAnimationFramesMoving() { return this->anm_frames_moving; }
vector<SDL_Texture*> Character::getAnimationFramesIdle() { return this->anm_frames_idle; }