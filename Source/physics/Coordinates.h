/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#pragma once

#include <Systems.h>

class Coordinates
{
private:
    int x;
    int y;

public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Coordinates();
    Coordinates(int x, int y);
    ~Coordinates();

    /*
    SECTION 2A: SETTERS
    */
    void setX(int x);
    void setY(int y);
    void setCoordinates(int x, int y);

    /*
    SECTION 2B: GETTERS
    */
    int getX() const;
    int getY() const;
};

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Coordinates::Coordinates()
{
    /*
    NOTE:
        - Do not use.
    */
    this->setX(0);
    this->setY(0);
}
Coordinates::Coordinates(int x, int y)
{
    /*
    NOTE:
        - Simple construction.
    */
    this->setX(x);
    this->setY(y);
}

Coordinates::~Coordinates()
{
    /*
    NOTE:
        - Empty, for now.
    */
}

/*
SECTION 2A: SETTERS
*/

void Coordinates::setX(int x) { this->x = x; }
void Coordinates::setY(int y) { this->y = y; }

void Coordinates::setCoordinates(int x, int y)
{
    this->setX(x);
    this->setY(y);
}

/*
SECTION 2B: GETTERS
*/
int Coordinates::getX() const { return this->x; }
int Coordinates::getY() const { return this->y; }