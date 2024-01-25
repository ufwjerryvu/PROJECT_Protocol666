#include "Player.h"

#include <Gameplay.h>
#include <Master.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Player::Player(Gameplay *context) : Character(context)
{
    /*
    TEMPORARY:
        - Setting the speed arbitrarily.
    */
}

Player::~Player()
{
}

/*
SECTION 2: OTHER METHODS
*/
void Player::run()
{
    /*
    NOTE:
        - Checking if either of the horizontal running keys has been pressed
        (i.e., 'A' and/or 'D') to set the running state of the player to true
        for animation purposes.
    */
    UserEvent *actions = this->getContext()->getContext()->getUserActions();

    if (actions->current_key_states[SDL_SCANCODE_A] || actions->current_key_states[SDL_SCANCODE_D])
    {
        this->setRunning(true);

        if (actions->current_key_states[SDL_SCANCODE_A] && actions->current_key_states[SDL_SCANCODE_D])
        {
            /*
            NOTE:
                - This is what happens when only one key ('A') is pressed.
            */
            *actions->simultaneous_horizontal_keys_pressed = false;
            *actions->current_horizontal_key = SDL_SCANCODE_A;
        }
        else if (!actions->current_key_states[SDL_SCANCODE_A] && actions->current_key_states[SDL_SCANCODE_D])
        {
            /*
            NOTE:
                - This is what happens when only one key ('D') is pressed.
            */
            *actions->simultaneous_horizontal_keys_pressed = false;
            *actions->current_horizontal_key = SDL_SCANCODE_D;
        }

        if (actions->current_key_states[SDL_SCANCODE_A] && actions->current_key_states[SDL_SCANCODE_D])
        {
            /*
            NOTE:
                - If two keys are being pressed down then the subsequent key
                is the final input.

                - For example, if 'D' was pressed first and 'A' is pressed
                after then 'A' becomes the final processed input and the
                player's character runs left.

                - We only change the value of `current_horizontal_key` if the
                flag that notes the concurrence of the two horizontal keys
                is not set.
            */

            if (*actions->current_horizontal_key == SDL_SCANCODE_D && !actions->simultaneous_horizontal_keys_pressed)
            {
                *actions->current_horizontal_key = SDL_SCANCODE_A;
            }
            else if (*actions->current_horizontal_key == SDL_SCANCODE_A && !*actions->simultaneous_horizontal_keys_pressed)
            {
                *actions->current_horizontal_key = SDL_SCANCODE_D;
            }

            *actions->simultaneous_horizontal_keys_pressed = true;
        }

        /*
        NOTE:
            - The variable `current_horizontal_key` ultimately decides
            the direction of the player's running motion and not
            `current_key_states`.
        */
        if (*actions->current_horizontal_key == SDL_SCANCODE_A)
        {
            this->setDirectionFacing(Direction::LEFT);
            /*
            NOTE:
                - Checking if the player is going out of the left bound. If they
                are then stop them.
            */
            if (this->getAbsolutePosition().getX() - this->Runnable::getSpeed() <= 0)
            {
                this->setRunning(false);
                /*
                NOTE:
                    - The following code that sets the x-coordinate is basically saying
                    that we don't want to leave a gap between the player and the edge
                    of the screen.
                */
                this->setAbsolutePosition(Coordinates(0, this->getAbsolutePosition().getY()));
                return;
            }
            /*
            NOTE:
                - The player is running left.
            */
            int nx = this->getAbsolutePosition().getX() - this->Runnable::getSpeed();
            int ny = 0 + this->getAbsolutePosition().getY();

            this->setAbsolutePosition(Coordinates(nx, ny));
        }
        else if (*actions->current_horizontal_key == SDL_SCANCODE_D)
        {
            this->setDirectionFacing(Direction::RIGHT);
            /*
            NOTE:
                - Checking if the player is going out of the right bound. If they
                are then stop them.
            */
            int cx = this->getAbsolutePosition().getX();
            int lwidth = this->getContext()->getLevelWidth();

            if (cx + this->Runnable::getSpeed() + this->getWidth() >= lwidth)
            {
                this->Runnable::setRunning(false);
                return;
            }
            /*
            NOTE:
                - The player is running right.
            */
            int nx = this->getAbsolutePosition().getX() + this->Runnable::getSpeed();
            int ny = 0 + this->getAbsolutePosition().getY();

            this->setAbsolutePosition(Coordinates(nx, ny));
        }
    }
    else
    {
        this->Runnable::setRunning(false);
    }
}
void Player::move() {
    this->run();
}

void Player::update() {
    this->move();
}