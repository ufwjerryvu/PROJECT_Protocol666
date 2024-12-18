#pragma once

#include <Systems.h>

#include <Direction.h>
#include <Sprite.h>

class Collidable : virtual public Sprite{
private:
    map<Direction, bool> directions;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Collidable();
    ~Collidable();

    /*
    SECTION 2: SETTERS AND GETTERS
    */
    bool checkCollision(Collidable& object);
    
    void setCollisionDirection(Direction direction, bool collided);
    bool checkCollisionDirection(Direction direction);

    /*
    SECTION 3: OTHER METHODS
    */
    void reset();
};