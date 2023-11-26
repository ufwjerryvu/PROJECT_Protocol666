/*
@ COLLABORATORS: An Nguyen, Jerry Vu, An Luu, Khanh Nguyen
@ CLASS DESIGNERS: Jerry Vu, Khanh Nguyen
*/

#pragma once

#include "Sprite.h"

struct CharacterAnimation {
    vector<SDL_Texture*> frames_idle;
    vector<SDL_Texture*> frames_running;
    vector<SDL_Texture*> frames_jumping;
    vector<SDL_Texture*> frames_falling;
    vector<SDL_Texture*> frames_rolling;
    vector<SDL_Texture*> frames_shooting_idle;
    vector<SDL_Texture*> frames_shooting_running;
    vector<SDL_Texture*> frames_shooting_jumping;
    vector<SDL_Texture*> frames_shooting_falling;

    int current_frame_idle = 0;
    int current_frame_running = 0;
    int current_frame_jumping = 0;
    int current_frame_falling = 0;
    int current_frame_rolling = 0;
    int current_frame_shooting_idle = 0;
    int current_frame_shooting_running = 0;
    int current_frame_shooting_jumping = 0;
    int current_frame_shooting_falling = 0;
};

struct Damage {
    int collision = 0;
    int attack = 0;
    int self_destruct = 0;
};

struct Movement {
    int spawn_x = 0;
    int spawn_y = 0;

    int x_max_displacement = 0;
    int y_max_displacement = 0;

    int x_direction_velocity = 0;
    int y_direction_velocity = 0;
};

struct Knockback {
    int self = 0;
    int attack = 0;
    int contact = 0;
};

class Character : public Sprite {
private:
    CharacterAnimation animation;

    Collision collided;

    Direction facing_direction;

    Knockback knockback;

    bool is_running;
    bool is_jumping;
    bool is_falling;
    bool is_rolling;
    bool is_attacking;


    /*
    NOTE:
        - The member attributes below are motion-related 
        attributes.

        - Speed is in pixels per frame.

        - Gravitational acceleration is in pixels per frame

        - Fall velocity is in pixels per frame

        - Terminal velocity is in pixels per frame
    */
    int run_speed;
    int gravitational_acceleration;
    int vertical_velocity;
    int initial_jump_velocity;
    int terminal_fall_velocity;
    int vertical_update_interval;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Character();
    Character(int x, int y, CharacterAnimation animation);
    ~Character();

    /*
    SECTION 2A: SETTERS
    */
    bool setAnimation(CharacterAnimation animation);
    bool setCollision(Collision collided);
    bool setDirectionFacing(Direction facing);
    bool setKnockback(Knockback knockback);
    bool setRunningState(bool is_running);
    bool setJumpingState(bool is_jumping);
    bool setFallingState(bool is_falling);
    bool setRollingState(bool is_rolling);
    bool setAttackingState(bool is_attacking);
    bool setRunSpeed(int pixels_per_frame);
    bool setGravitationalAcceleration(float grav_accel);
    bool setVerticalVelocity(int vertical_velocity);
    bool setIntialJumpVelocity(int initial_jump_velocity);
    bool setTerminalFallVelocity(int terminal_fall_velocity);
    bool setVerticalUpdateInterval(int vertical_update_interval);

    /*
    SECTION 2B: GETTERS
    */
    CharacterAnimation getAnimation();
    Collision getCollisionDirections();
    Direction getDirectionFacing();
    Knockback getKnockback();
    bool isRunning();
    bool isJumping();
    bool isFalling();
    bool isRolling();
    bool isAttacking();
    int getRunSpeed();
    int getGravitationalAcceleration();
    int getVerticalVelocity();
    int getInitialJumpVelocity();
    int getTerminalFallVelocity();
    int getVerticalUpdateInterval();

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
    void fall();
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

    /*
    NOTE:
        - Setting everything related to motion.
    */
    this->setRunningState(false);
    this->setAttackingState(false);
    
    /*
    NOTE:
        - Overridable here means these are the default values for
        all characters. If different types of characters need
        different values of motion then they can specify it in their
        constructors or elsewhere -- preferably in the constructors.
    */
    const int OVERRIDABLE_RUN_SPEED = 0,
        OVERRIDABLE_GRAV_ACCEL = 0,
        OVERRIDABLE_INITIAL_VERTICAL_VELOCITY = 0,
        OVERRIDABLE_INITIAL_JUMP_VELOCITY = 0,
        OVERRIDABLE_TERMINAL_VELOCITY = 0,
        OVERRIDABLE_INITIAL_VERT_UPDATE_INTERVAL = 0;

    this->setRunSpeed(OVERRIDABLE_RUN_SPEED);
    this->setGravitationalAcceleration(OVERRIDABLE_GRAV_ACCEL);
    this->setVerticalVelocity(OVERRIDABLE_INITIAL_VERTICAL_VELOCITY);
    this->setIntialJumpVelocity(OVERRIDABLE_INITIAL_JUMP_VELOCITY);
    this->setTerminalFallVelocity(OVERRIDABLE_TERMINAL_VELOCITY);
    this->setVerticalUpdateInterval(OVERRIDABLE_INITIAL_VERT_UPDATE_INTERVAL);
}

Character::Character(int x, int y, CharacterAnimation animation) : Sprite(x, y, NULL) {
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

    /*
    NOTE:
        - Setting everything related to motion.
    */
    this->setRunningState(false);
    this->setAttackingState(false);

    /*
    NOTE:
        - Overridable here means these are the default values for
        all characters. If different types of characters need
        different values of motion then they can specify it in their
        constructors or elsewhere -- preferably in the constructors.
    */
    const int OVERRIDABLE_RUN_SPEED = 0,
        OVERRIDABLE_GRAV_ACCEL = 2,
        OVERRIDABLE_INITIAL_VERTICAL_VELOCITY = 0,
        OVERRIDABLE_INITIAL_JUMP_VELOCITY = 16,
        OVERRIDABLE_TERMINAL_VELOCITY = 10,
        OVERRIDABLE_INITIAL_VERT_UPDATE_INTERVAL = 0;

    this->setRunSpeed(OVERRIDABLE_RUN_SPEED);
    this->setGravitationalAcceleration(OVERRIDABLE_GRAV_ACCEL);
    this->setVerticalVelocity(OVERRIDABLE_INITIAL_VERTICAL_VELOCITY);
    this->setIntialJumpVelocity(OVERRIDABLE_INITIAL_JUMP_VELOCITY);
    this->setTerminalFallVelocity(OVERRIDABLE_TERMINAL_VELOCITY);
    this->setVerticalUpdateInterval(OVERRIDABLE_INITIAL_VERT_UPDATE_INTERVAL);
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
bool Character::setAnimation(CharacterAnimation animation) {
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

    /*
    NOTE:
        - We add this layer of security to check if the vector
        for jumping frames is empty.
    */

    if (animation.frames_jumping.size() <= 0) {
        cerr << "Error from Character::setAnimation(): no elements "
            << "are present in the frames_jumping vector." << endl;
        success = false;
        return success;
    }

    /*
    NOTE:
        - Again, if any of the textures in the vector is
        NULL then the method returns false.
    */
    for (int index = 0; index < this->animation.frames_jumping.size(); index++) {
        if (this->animation.frames_jumping[index] == NULL) {
            cerr << "Error from Character::setAnimation(): a null "
                << "pointer has been detected in the frames_jumping vector." << endl;
            success = false;
            return success;
        }
    }

    /*
    NOTE:
        - We add this layer of security to check if the vector
        for falling frames is empty.
    */

    if (animation.frames_falling.size() <= 0) {
        cerr << "Error from Character::setAnimation(): no elements "
            << "are present in the frames_falling vector." << endl;
        success = false;
        return success;
    }

    /*
    NOTE:
        - Again, if any of the textures in the vector is
        NULL then the method returns false.
    */
    for (int index = 0; index < this->animation.frames_falling.size(); index++) {
        if (this->animation.frames_falling[index] == NULL) {
            cerr << "Error from Character::setAnimation(): a null "
                << "pointer has been detected in the frames_falling vector." << endl;
            success = false;
            return success;
        }
    }

    this->animation = animation;

    return success;
}

bool Character::setCollision(Collision collided) {
    bool success = true;

    this->collided = collided;

    return success;
}

bool Character::setDirectionFacing(Direction facing) {
    bool success = true;

    this->facing_direction = facing;

    return true;
}

bool Character::setKnockback(Knockback knockback) {
	bool success = true;

	this->knockback = knockback;

	return success;
}

bool Character::setRunningState(bool is_running) {
    bool success = true;

    this->is_running = is_running;

    return success;
}

bool Character::setJumpingState(bool is_jumping) {
    bool success = true;

    this->is_jumping = is_jumping;

    return success;
}

bool Character::setFallingState(bool is_falling) {
    bool success = true;

    this->is_falling = is_falling;

    return success;
}

bool Character::setRollingState(bool is_rolling) {
    bool success = true;

    this->is_rolling = is_rolling;

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

bool Character::setGravitationalAcceleration(float grav_accel) {
    bool success = true;

    this->gravitational_acceleration = grav_accel;

    return success;
}

bool Character::setVerticalVelocity(int vertical_velocity) {
    bool success = true;

    this->vertical_velocity = vertical_velocity;

    return success;
}

bool Character::setIntialJumpVelocity(int initial_jump_velocity) {
    bool success = true;

    this->initial_jump_velocity = initial_jump_velocity;

    return success;
}

bool Character::setTerminalFallVelocity(int terminal_fall_velocity) {
    bool success = true;

    this->terminal_fall_velocity = terminal_fall_velocity;

    return success;
}

bool Character::setVerticalUpdateInterval(int vertical_update_interval) {
    bool success = true;

    this->vertical_update_interval = vertical_update_interval;

    return success;
}

/*
SECTION 2B: GETTERS
*/
CharacterAnimation Character::getAnimation() { return this->animation; }
Collision Character::getCollisionDirections() { return this->collided; }
Direction Character::getDirectionFacing() { return this->facing_direction; }
Knockback Character::getKnockback() { return this->knockback; }
bool Character::isRunning() { return this->is_running; }
bool Character::isJumping() { return this->is_jumping; }
bool Character::isFalling() { return this->is_falling; }
bool Character::isRolling() { return this->is_rolling; }
bool Character::isAttacking() { return this->is_attacking; }
int Character::getRunSpeed() { return this->run_speed; }
int Character::getGravitationalAcceleration() { return this->gravitational_acceleration; }
int Character::getVerticalVelocity() { return this->vertical_velocity; }
int Character::getInitialJumpVelocity() { return this->initial_jump_velocity;  }
int Character::getTerminalFallVelocity() { return this->terminal_fall_velocity; }
int Character::getVerticalUpdateInterval() { return this->vertical_update_interval; }
/*
SECTION 3: OTHER FUNCTIONS
*/
void Character::fall() {
    /*
    NOTE:
        - An attempt at disabling jump() after reaching the max height:
        first, we set the jump state to false and we then set the falling
        state to true right after.

        - As the Character falls, fall_velocity is 0, which increments by 
        the gravitational_acceleration per game update interval.
    */

    /*
    NOTE:
        - If a character is detecting collision beneath
        it then set the falling state to false and vertical
        velocity to 0.
    */
    if (this->getCollisionDirections().bottom) {
        this->setFallingState(false);
        this->setVerticalVelocity(0);
    }
    else {
        this->setFallingState(true);
    }

    /*
    NOTE:
        - Incorporated the horizontal bounds to make sure characters
        don't fall through the bottom of the screen.
    */
    const int PIXEL_ERROR_MARGIN = 3;

    if (this->getY() >= this->getLevelHeight() - this->getHeight() - PIXEL_ERROR_MARGIN
        && this->getY() <= this->getLevelHeight() - this->getHeight() + PIXEL_ERROR_MARGIN) {
        this->setFallingState(false);
    }

    /*
    NOTE:
        - This is to make sure that none of the characters
        fall through the bottom of the screen.
    */
    if (this->getY() + this->getHeight() >= this->getLevelHeight()) {
        this->setY(this->getLevelHeight() - this->getHeight());
        this->setVerticalVelocity(0);
        this->setFallingState(false);
        return;
    }
    
    if (this->isFalling()) {
        const int FRAME_UPDATE_INTERVAL = 3;

        /*
        NOTE:
            - Fixed the condition up a little bit. The vertical update interval
            must be larger than the 
        */
        if (this->getVerticalVelocity() != this->getTerminalFallVelocity() && this->getVerticalUpdateInterval() >= FRAME_UPDATE_INTERVAL) {
            /*
            NOTE:
                - Changed fall_velocity if fall_velocity has not reached 
                terminal_velocity.

                - This change is done by adding the gravitational_acceleration
                each time an update interval is met.

                - The update interval is set to be 3 frames, using FRAME_UPDATE_INTERVAL,
                the vertical_velocity is unadjusted at 0, 1, 2 interval frame; updates 
                vertical_velocity after 2nd-interval frame fall() call finishes.
            */

            this->setVerticalVelocity(this->getVerticalVelocity() + this->getGravitationalAcceleration());
            this->setVerticalUpdateInterval(0);
        }

        else {
            this->setVerticalUpdateInterval(this->getVerticalUpdateInterval() + 1);
            this->setY(this->getY() + this->getVerticalVelocity());
        }
    }
}
