#include "Character.h"

#include <Gameplay.h>
#include <Master.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Character::Character(Gameplay *context)
{
    /*
    NOTE:
        - Just a good ol' regular constructor.
    */
    this->context = context;
}
Character::~Character()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}
/*
SECTION 2: SETTERS AND GETTERS
*/
void Character::setAnimator(Animator<string> animator)
{
    this->animator = animator;
}

Gameplay *Character::getContext()
{
    return this->context;
}

Animator<string> &Character::getAnimator()
{
    return this->animator;
}
/*
SECTION 3: OTHER METHODS
*/

void Character::fall()
{
    /*
    NOTE:
        - An attempt at disabling `jump()` after reaching the max height:
        first, we set the jump state to false and we then set the falling
        state to true right after.

        - As the Character falls, fall velocity is 0, which increments by
        the gravitational acceleration per game update interval.
    */
    Coordinates &position = this->getAbsolutePosition();
    Gameplay *context = this->getContext();
    /*

    NOTE:
        - If a character is detecting collision beneath
        it then set the falling state to false and vertical
        velocity to 0.
    */
    // if (this->getCollisionDirections().bottom)
    // {
    //     this->setFallingState(false);
    //     this->setVerticalVelocity(0);
    // }
    // else
    // {
    //     this->setFallingState(true);
    // }
    this->setFalling(true);

    /*
    NOTE:
        - Incorporated the horizontal bounds to make sure characters
        don't fall through the bottom of the screen.
    */
    const int PIXEL_ERROR_MARGIN = 3;

    if (position.getY() >= context->getLevelHeight() - this->getHeight() - PIXEL_ERROR_MARGIN &&
        position.getY() <= context->getLevelHeight() - this->getHeight() + PIXEL_ERROR_MARGIN)
    {
        this->setFalling(false);
    }

    /*
    NOTE:
        - This is to make sure that none of the characters
        fall through the bottom of the screen.
    */
    if (position.getY() + this->getHeight() >= context->getLevelHeight())
    {
        position.setY(context->getLevelHeight() - this->getHeight());
        this->Verticality::setVelocity(0);
        this->setFalling(false);
        return;
    }

    if (this->isFalling())
    {
        /*
        NOTE:
            - Fixed the condition up a little bit. The vertical update interval
            must be larger.
        */

        if (this->Verticality::getVelocity() < this->Fallable::getTerminalVelocity() &&
            this->Verticality::getCounter() >= this->Verticality::getInterval())
        {
            /*
            NOTE:
                - Changed vertical velocity if vertical velocity has not reached
                terminal velocity.

                - This change is done by adding the gravitational acceleration
                each time an update interval is met.
            */
            this->Verticality::setVelocity(this->Verticality::getVelocity() +
                                           this->Fallable::getGravitationalAcceleration());
            this->Verticality::reset();
        }

        else
        {
            
            this->Verticality::increment();
            position.setY(position.getY() + this->Verticality::getVelocity());
        }
    }
}

void Character::render()
{
    /*
    NOTE:
        - A scrolling level (or a camera that follows the sprite) has
        been implemented. This function will always have the camera
        follow the character.
    */

    SDL_Rect &viewport = this->getViewport();

    viewport.x = this->getRelativePosition().getX();
    viewport.y = this->getRelativePosition().getY();

    SDL_Renderer *renderer = this->getContext()->getContext()->getRenderer();

    if (this->getDirectionFacing() == Direction::LEFT)
    {
        /*
        NOTE:
            - By default, all character textures will be facing right. We flip
            it if the player is trying to go left. We use `SDL_RenderCopyEx()`
            instead of `SDL_RenderCopy()` for this purpose.
        */
        const SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

        if (SDL_RenderCopyEx(renderer, this->getTexture(), NULL, &viewport, 0.00,
                             NULL, flip))
        {
            cerr << "Error: unable to render the current texture." << endl;
            assert(false);
        }
    }
    else if (this->getDirectionFacing() == Direction::RIGHT ||
             this->getDirectionFacing() == Direction::NONE)
    {
        if (SDL_RenderCopy(renderer, this->getTexture(), NULL, &viewport))
        {
            cerr << "Error: unable to render the current texture." << endl;
            assert(false);
        }
    }
}