#pragma once

#include <Systems.h>

#include <Projectile.h>

class Gameplay;

class LaserBeam : public Projectile
{
private:
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    LaserBeam(Gameplay *context);
    ~LaserBeam();
    /*
    SECTION 2: SETTERS AND GETTERS
    */
    /*
    SECTION 3: OTHER METHODS
    */
    void move();
    void update();
};