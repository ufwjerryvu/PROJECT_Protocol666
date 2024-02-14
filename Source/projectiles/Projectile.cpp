#include "Projectile.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Projectile::Projectile()
{
    /*
    NOTE:
        - Empty, probably for good.
    */
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
void Projectile::setTravelDirection(Direction direction) { this->setDirectionFacing(direction); }

Gameplay *Projectile::getContext() { return this->context; }
int Projectile::getDamage() { return this->damage; }
int Projectile::getVelocity() { return this->velocity; }
Direction Projectile::getTravelDirection() { return this->getDirectionFacing(); }