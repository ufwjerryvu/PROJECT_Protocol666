#pragma once 

#include <Systems.h>

#include <Sprite.h>
#include <Collidable.h>
#include <Moveable.h>

class Gameplay;

class Projectile : virtual public Sprite, virtual public Collidable,
            virtual private Moveable{
private:
    Gameplay *context;
    int damage;
    int velocity;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Projectile();
    ~Projectile();
    /*
    SECTION 2: SETTERS AND GETTERS
    */
    void setContext(Gameplay* context);
    void setDamage(int damage);
    void setVelocity(int velocity);
    void setTravelDirection(Direction direction);

    Gameplay* getContext();
    int getDamage();
    int getVelocity();
    Direction getTravelDirection();
    /*
    SECTION 3: OTHER METHODS
    */
    virtual void move() = 0;
    virtual void update() = 0;
};