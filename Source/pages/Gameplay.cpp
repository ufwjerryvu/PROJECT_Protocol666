#include "Gameplay.h"

#include <Master.h>
#include <Player.h>
#include <FileHandler.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Gameplay::Gameplay()
{
    /*
    NOTE:
        - Do not use. Ever.
    */
}

Gameplay::Gameplay(Master *context)
{
    /*
    NOTE:
        - Context is set to the master as part of the navigation
        scheme.
    */
    this->context = context;
    this->player = new Player(this);
    this->player->setAbsolutePosition(Coordinates(100, 100));
    this->player->setTexture(FileHandler().loadTexture(this->context->getRenderer(), "Assets/Sprite/Character/Player/Ragdoll/idle1.png"));
}
Gameplay::~Gameplay()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

/*
SECTION 2: SETTERS AND GETTERS
*/
Master *Gameplay::getContext() { return this->context; }
int Gameplay::getLevelWidth() { return this->lwidth; }
int Gameplay::getLevelHeight() { return this->lheight; }

/*
SECTION 3: OTHER METHODS
*/
void Gameplay::update()
{
    this->player->update();
}
void Gameplay::render()
{
    this->player->render();
}