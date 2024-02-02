#include "Collidable.h"

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Collidable::Collidable()
{
    /*
    NOTE:
        - We need to set collisions in all directions to `false`.
    */
    this->reset();
}

Collidable::~Collidable()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
bool Collidable::checkCollision(Collidable &object)
{
    /*
    NOTE:
        - The if statement below checks for non-collision. Kudos to An B Luu
        for doing things differently -- that was not a compliment. Man's mad.

        - I also fixed up the code to make it less redundant. The code is now
        a quarter of what it was.
    */

    if (this->getLeftBound() > object.getRightBound() ||
        this->getRightBound() < object.getLeftBound() ||
        this->getTopBound() > object.getBottomBound() ||
        this->getBottomBound() < object.getTopBound())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Collidable::setCollisionDirection(Direction direction, bool collided)
{
    /*
    NOTE:
        - Mapping the direction to the fact that it's been collided.
    */
    this->directions[direction] = collided;
}

bool Collidable::checkCollisionDirection(Direction direction)
{
    /*
    NOTE:
        - Simple.
    */
    return this->directions[direction];
}

void Collidable::reset()
{
    /*
    NOTE:
        - Resets all directions to `false`.
    */
    this->directions[Direction::LEFT] = false;
    this->directions[Direction::RIGHT] = false;
    this->directions[Direction::UP] = false;
    this->directions[Direction::DOWN] = false;
}