#include "FiftyCalibre.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
FiftyCalibre::FiftyCalibre(Gameplay *context) : Projectile(context)
{
    /*
    NOTE:
        - Empty, probably for good.
    */
}
FiftyCalibre::~FiftyCalibre()
{
    /*
    TEMPORARY:
        - Empty, probably for now.
    */
}
/*
SECTION 2: SETTERS AND GETTERS
*/
/*
SECTION 3: OTHER METHODS
*/
void FiftyCalibre::move()
{
    /*
    NOTE:
        - Direction must be either of the horizontal ones and differ from the default
        in order to be moved and updated.
    */
    if (this->getTravelDirection() == Direction::NONE)
    {
        cerr << "Error: must initialize a direction for projectile before usage." << endl;
        assert(false);
    }

    /*
    NOTE:
        - Setting the positions according to the direction of travel.
    */
    Coordinates &position = this->getAbsolutePosition();
    if (this->getTravelDirection() == Direction::RIGHT)
    {
        position.setX(position.getX() + this->getVelocity());
    }
    else if (this->getTravelDirection() == Direction::LEFT)
    {
        position.setX(position.getX() - this->getVelocity());
    }
}

void FiftyCalibre::update(){
    this->move();

    /*
    NOTE:
        - If the object goes out of bounds then we mark it for deletion. The managing
        class must delete it in the list as well as dynamically.
    */
    Coordinates& position = this->getAbsolutePosition();
    if(position.getX() < 0 || position.getX() > this->getContext()->getLevelWidth()){
        this->markDelete(true);
    }
}