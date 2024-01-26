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
    NOTE:
        - Deleting all the pointers and memory allocated on the heap
        for game objects.
    */
    delete player;
}

/*
SECTION 2: SETTERS AND GETTERS
*/
Master *Gameplay::getContext() { return this->context; }
int Gameplay::getLevelWidth() { return this->level_width; }
int Gameplay::getLevelHeight() { return this->level_height; }

/*
SECTION 3: OTHER METHODS
*/
void Gameplay::updateCamera()
{
    /*
    NOTE:
        - The code below centers the player.

        - Code modified from lazyfoo.net.
    */
    Coordinates position = player->getAbsolutePosition();
    int screen_width = this->context->getScreenWidth();
    int screen_height = this->context->getScreenHeight();

    camera.x = (position.getX() + this->player->getWidth() / 2) - screen_width / 2;
    camera.y = (position.getY() + this->player->getHeight() / 2) - screen_height / 2;

    /*
    NOTE:
        - Making sure the camera doesn't go out of the discrete_dimensions of
        the level. Again, the code was modified from lazyfoo.net.
    */
    if (this->camera.x < 0)
        this->camera.x = 0;

    if (this->camera.y < 0)
        this->camera.y = 0;

    if (this->camera.x > this->level_width - screen_width)
        this->camera.x = this->level_width - screen_width;

    if (this->camera.y > this->level_height - screen_height)
        this->camera.y = this->level_height - screen_height;
}

void Gameplay::updateRenderPos()
{
    this->player->setRelativePosition(Coordinates(this->camera.x, this->camera.y));
}

void Gameplay::update()
{
    this->updateCamera();
    this->updateRenderPos();
    
    this->player->update();
}
void Gameplay::render()
{
    this->player->render();
}
