#include "Projectile.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Projectile::Projectile(Gameplay *context) : Sprite(), Collidable(), Moveable()
{
    /*
    NOTE:
        - Enforcing the default states.
    */
    this->context = context;
    this->setTravelDirection(Direction::NONE);
}
Projectile::~Projectile()
{
    /*
    TEMPORARY:
        - Empty, probably for now.
    */
}
/*
SECTION 2: SETTERS AND GETTERS
*/
void Projectile::setContext(Gameplay *context) { this->context = context; }
void Projectile::setDamage(int damage) { this->damage = damage; }
void Projectile::setVelocity(int velocity) { this->velocity = velocity; }

void Projectile::setTravelDirection(Direction direction)
{
    /*
    NOTE:
        - For these types of objects, we only allow them to travel left or right.
        Anything other than that will be thrown an error.
    */
    if (direction != Direction::RIGHT && direction != Direction::LEFT &&
        direction != Direction::NONE)
    {
        cerr << "Error: default projectiles can only travel horizontally." << endl;
        assert(false);
    }

    this->setDirectionFacing(direction);
}

void Projectile::markDelete(bool mark) { this->marked = mark; }

Gameplay *Projectile::getContext() { return this->context; }
int Projectile::getDamage() { return this->damage; }
int Projectile::getVelocity() { return this->velocity; }
Direction Projectile::getTravelDirection() { return this->getDirectionFacing(); }
bool Projectile::isMarkedForDeletion() { return this->marked; }