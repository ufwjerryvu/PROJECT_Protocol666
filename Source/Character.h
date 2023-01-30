/*
@ COLLABORATORS: An Nguyen, Jerry Vu, An Luu, Khanh Nguyen
@ CLASS DESIGNERS: Jerry Vu, Khanh Nguyen
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
    bool is_jumping;
    bool is_falling;
    bool is_attacking;

    /*
    NOTE :
        -Speed is in pixels per frame.

        - Maximum jump height is in pixels.

        - Gravitational acceleration is in pixels per frame

        - Gravitational acceleration is in pixels per frame
        
        - Fall velocity is in pixels per frame

        - Terminal velocity is in pixels per frame
    */

    int run_speed;
    int max_jump_height;

    int gravitational_acceleration;
    int fall_velocity;
    int terminal_velocity;

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
    bool setJumpingState(bool is_jumping);
    bool setFallingState(bool is_falling);
    bool setAttackingState(bool is_attacking);
    bool setRunSpeed(int pixels_per_frame);
    bool setMaxJumpHeight(int pixels);
    bool setGravitationalAcceleration(float grav_accel);
    bool setFallVelocity(int fall_velocity);
    bool setTerminalVelocity(int terminal_velocity);

    /*
    SECTION 2B: GETTERS
    */
    Animation getAnimation();
    Direction getDirectionFacing();
    bool isRunning();
    bool isJumping();
    bool isFalling();
    bool isAttacking();
    int getRunSpeed();
    int getMaxJumpHeight();
    int getGravitationalAcceleration();
    int getFallVelocity();
    int getTerminalVelocity();

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

        - Added new setters into the constructor for gravitational acceleration, fall velocity, and terminal velocity
    */
    this->setDirectionFacing(Direction::NONE);

    this->setRunningState(false);
    this->setAttackingState(false);
    
    const int temp_max_jump_height = 200;
    const int temp_grav_accel = 1;
    const int temp_terminal_velocity = 10;

    this->setRunSpeed(0);
    this->setMaxJumpHeight(temp_max_jump_height);
    this->setGravitationalAcceleration(temp_grav_accel);
    this->setFallVelocity(0);
    this->setTerminalVelocity(temp_terminal_velocity);
}

Character::Character(int x, int y, Animation animation) : Sprite(x, y, NULL) {
    this->setAnimation(animation);
    
    /*
    NOTE:
        - Setting the character to the first idle
        frame as soon as they are created.

        - Added new setters into the constructor for gravitational acceleration, fall velocity, and terminal velocity
    */
    if (animation.frames_idle.size() > 0) {
        this->setTexture(animation.frames_idle[0]);
    }

    this->setDirectionFacing(Direction::NONE);

    this->setRunningState(false);
    this->setAttackingState(false);

    const int temp_max_jump_height = 200;
    const int temp_grav_accel = 2;
    const int temp_terminal_velocity = 10;

    this->setRunSpeed(0);
    this->setMaxJumpHeight(temp_max_jump_height);
    this->setGravitationalAcceleration(temp_grav_accel);
    this->setFallVelocity(0);
    this->setTerminalVelocity(temp_terminal_velocity);

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

bool Character::setAttackingState(bool is_attacking) {
    bool success = true;

    this->is_attacking = is_attacking;

    return success;
}

bool Character::setRunSpeed(int pixels_per_frame) {
    bool success = true;

    this->run_speed = pixels_per_frame;

    return success;
}

bool Character::setMaxJumpHeight(int pixels) {
    bool success = true;

    this->max_jump_height = pixels;

    return success;
}

bool Character::setGravitationalAcceleration(float grav_accel) {
    bool success = true;
    
    this->gravitational_acceleration = grav_accel;

    return success;
}

bool Character::setFallVelocity(int fall_velocity) {
    bool success = true;
    
    this->fall_velocity = fall_velocity;

    return success;
}

bool Character::setTerminalVelocity(int terminal_velocity) {
    bool success = true;

    this->terminal_velocity = terminal_velocity;

    return success;
}

/*
SECTION 2B: GETTERS
*/
Animation Character::getAnimation() { return this->animation; }
Direction Character::getDirectionFacing() { return this->facing_direction; }
bool Character::isRunning() { return this->is_running; }
bool Character::isJumping() { return this->is_jumping; }
bool Character::isFalling() { return this->is_falling; }
bool Character::isAttacking() { return this->is_attacking; }
int Character::getRunSpeed() { return this->run_speed; }
int Character::getMaxJumpHeight() { return this->max_jump_height; }
int Character::getGravitationalAcceleration() { return this->gravitational_acceleration;  }
int Character::getFallVelocity() { return this->fall_velocity;  }
int Character::getTerminalVelocity() { return this->terminal_velocity;  }

/*
SECTION 3: OTHER FUNCTIONS
*/
void Character::fall() {
    
    /*
    NOTE:
        - An attempt at disabling jump() after reaching the max height:

    his->setJumpingState(false);
    this->setFallingState(true);

        - The assumption for using 400 in the conditional statement was to establish a platform

        - To assure the Character does not fall through the platform by any means, a slight tweak was made for terminal velocity

        - As the Character fall, fall_velocity is 0, which increments by the gravitational_acceleration per game update interval.
    */

    const int platform_y_coordinate = 400;

    if (this->getY() + this->getFallVelocity() >= platform_y_coordinate) {
        this->setFallVelocity(platform_y_coordinate - this->getY());
        this->setY(this->getY() + this->getFallVelocity());
    }

    else {
        this->setY(this->getY() + this->getFallVelocity());

        if (this->getFallVelocity() != this->getTerminalVelocity()) {
            this->setFallVelocity(this->getFallVelocity() + this->getGravitationalAcceleration());
        }
    }
}
