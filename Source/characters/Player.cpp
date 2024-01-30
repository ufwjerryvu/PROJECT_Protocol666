#include "Player.h"

#include <Gameplay.h>
#include <Master.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Player::Player(Gameplay *context) : Character(context)
{
	/*
	NOTE:
		- Calling the super constructors. Trace the inheritance
		to figure out what values are being initialized.
	*/
}

Player::~Player()
{
	/*
	TEMPORARY:
		- Empty, for now.
	*/
}

/*
SECTION 2: OTHER METHODS
*/
void Player::run()
{
	UserEvent *actions = this->getContext()->getContext()->getUserActions();
	Coordinates &position = this->getAbsolutePosition();
	/*
	NOTE:
		- Checking if either of the horizontal running keys has been pressed
		(i.e., 'A' and/or 'D') to set the running state of the player to true
		for animation purposes.
	*/
	if (actions->current_key_states[SDL_SCANCODE_A] || actions->current_key_states[SDL_SCANCODE_D])
	{
		this->setRunning(true);

		if (actions->current_key_states[SDL_SCANCODE_A] && !actions->current_key_states[SDL_SCANCODE_D])
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

			if (*actions->current_horizontal_key == SDL_SCANCODE_D && !*actions->simultaneous_horizontal_keys_pressed)
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
			if (position.getX() - this->Runnable::getSpeed() <= 0)
			{
				this->setRunning(false);
				/*
				NOTE:
					- The following code that sets the x-coordinate is basically saying
					that we don't want to leave a gap between the player and the edge
					of the screen.
				*/
				position.setX(0);
				return;
			}
			/*
			NOTE:
				- The player is running left.
			*/
			this->getAbsolutePosition().setX(this->getAbsolutePosition().getX() - this->Runnable::getSpeed());
		}
		else if (*actions->current_horizontal_key == SDL_SCANCODE_D)
		{
			this->setDirectionFacing(Direction::RIGHT);
			/*
			NOTE:
				- Checking if the player is going out of the right bound. If they
				are then stop them.
			*/
			if (position.getX() + this->Runnable::getSpeed() + this->getWidth() >= this->getContext()->getLevelWidth())
			{
				this->setRunning(false);
				return;
			}
			/*
			NOTE:
				- The player is running right.
			*/
			position.setX(position.getX() + this->Runnable::getSpeed());
		}
	}
	else
	{
		this->setRunning(false);
	}
}

void Player::roll()
{
	/*
	NOTE:
		- Defines the logic for the action of rolling. Press 'LEFT SHIFT' to roll.
		The player can roll before they jump.
	*/
	UserEvent *actions = this->getContext()->getContext()->getUserActions();
	Coordinates &position = this->getAbsolutePosition();

	/*
	TEMPORARY:
		- This section will be added in later.
	*/
	if (actions->current_key_states[SDL_SCANCODE_LSHIFT]) //&& !(this->isAttacking() || this->isFalling() || this->isJumping()))
	{
		this->setRolling(true);
		this->setRunning(false);
	}

	if (this->isRolling())
	{
		if (this->getDirectionFacing() == Direction::LEFT)
		{
			/*
			NOTE:
				- Checking if the player is going out of the left bound. If they
				are then stop them.
			*/
			if (position.getX() - this->Rollable::getSpeed() <= 0)
			{
				this->setRolling(false);
				/*
				NOTE:
					- The following code that sets the x-coordinate is basically saying
					that we don't want to leave a gap between the player and the edge
					of the screen.
				*/
				position.setX(0);
				return;
			}
			/*
			NOTE:
				- The player is rolling left.
			*/
			position.setX(position.getX() - this->Rollable::getSpeed());
		}

		if (this->getDirectionFacing() == Direction::RIGHT)
		{
			/*
			NOTE:
				- Checking if the player is going out of the right bound. If they
				are then stop them.
			*/
			if (position.getX() + this->Rollable::getSpeed() + this->getWidth() >= this->getContext()->getLevelWidth())
			{
				this->setRolling(false);
				return;
			}
			/*
			NOTE:
				- The player is rolling right.
			*/
			position.setX(position.getX() + this->Rollable::getSpeed());
		}
	}
}

void Player::jump()
{
	/*
	TEMPORARY:
		- Empty, for now.
	*/
}

void Player::move()
{
	/*
	NOTE:
		- `fall()` can only be called if the character is mid air,
		while not in jumping motion.

		- `jump()` can only be called if the character is currently on
		a platform, and is not falling mid air.

	*/
	if (!this->isJumping() && this->getAbsolutePosition().getY() <=
								  this->getContext()->getLevelHeight())
	{
		this->fall();
	}

	if (!this->isFalling())
	{
		/*
		NOTE:
			- This doesn't mean that we're going to make
			the player's character jump. The function still
			depends on the user's input.
		*/
		this->jump();
	}

	if (!this->isRolling() || this->isFalling() || this->isJumping())
	{
		this->run();
	}

	this->roll();
}

void Player::update()
{
	/*
	NOTE:
		- We need to call the `move()` method before we query
		what the player is doing.
	*/
	this->move();

	/*
	TEMPORARY:
		- This is slightly more complicated and has more
		actions.
	*/
	if (!this->isRunning() && !this->isRolling())
		this->getAnimator().setKey("idle");

	if (this->isRunning())
		this->getAnimator().setKey("run");

	if (this->isRolling())
		this->getAnimator().setKey("roll");

	if (this->isFalling())
		this->getAnimator().setKey("fall");

	this->setTexture(this->getAnimator().getCurrentFrame());

	if (this->getAnimator().increment())
	{
		if (this->getAnimator().getKey() == "roll")
		{
			this->setRolling(false);
		}
	}
}