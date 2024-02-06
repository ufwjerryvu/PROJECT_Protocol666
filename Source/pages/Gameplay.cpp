#include "Gameplay.h"

#include <Master.h>
#include <Creator.h>

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
    this->player = Creator().createPlayer(this);
    this->grounds = {Creator().createGround(this)};
    this->platforms = Creator().createArrayPlatforms(this);
}

Gameplay::~Gameplay()
{
    /*
    NOTE:
        - Deleting all the pointers and memory allocated on the heap
        for game objects.
    */
    delete player;

    for (Ground *ground : this->grounds)
    {
        delete ground;
    }
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
        - Making sure the camera doesn't go out of the dimensions of
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
    /*
    NOTE:
        - Updating things that need the camera to follow.
    */
    Coordinates camera = Coordinates(this->camera.x, this->camera.y);

    this->player->setRelativePosition(camera);
    
    for (Platform *platform : this->platforms)
    {
        platform->setRelativePosition(camera);
    }

    for (Ground *ground : this->grounds)
    {
        ground->setRelativePosition(camera);
    }
}

void Gameplay::updateCollisions()
{
    /*
    NOTE:
        - This is specific to collisions. Calls all the collision updates poss-
        ible.
    */
    this->player->Collidable::reset();
    this->player->collide(this->grounds);
    this->player->collide(this->platforms);
}

void Gameplay::update()
{
    /*
    NOTE:
        - We first update the camera and the relative render position of the game-
        play objects.
    */
    this->updateCamera();
    this->updateRenderPos();

    /*
    NOTE:
        - Then, we udpate collisions.
    */
    this->updateCollisions();

    /*
    NOTE:
        - And then we update the gameplay objects themselves.
    */
    this->player->update();
}
void Gameplay::render()
{
    /*
    NOTE:
        - Render all the things that need to be rendered.
    */
    this->player->render();

    for (Ground *ground : this->grounds)
    {
        ground->render();
    }

    for (Platform *platform : this->platforms)
    {
        platform->render();
    }
}
