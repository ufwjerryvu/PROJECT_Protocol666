#include "Collidable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Collidable::Collidable(){
    /*
    NOTE:
        - We need to set collisions in all directions to `false`.
    */
    this->directions[Direction::LEFT] = false;
    this->directions[Direction::RIGHT] = false;
    this->directions[Direction::UP] = false;
    this->directions[Direction::DOWN] = false;
}

/*
SECTION 2: SETTERS AND GETTERS
*/
bool Collidable::checkCollision(Collidable &object){
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

void Collidable::setCollisionDirection(Direction direction, bool collided){
    /*
    NOTE:
        - Mapping the direction to the fact that it's been collided.
    */
    this->directions[direction] = collided;
}

bool Collidable::checkCollisionDirection(Direction direction){
    /*
    NOTE:
        - Simple.
    */
   return this->directions[direction];
}