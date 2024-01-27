#include "Settings.h"

#include <Master.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Settings::Settings()
{
    /*
    NOTE:
        - Do not use.
    */
}

Settings::Settings(Master *context) : Navigation(context)
{
    /*
    NOTE:
        - Following the example of another navigation source file.
    */
    Button dummy = Button();
    this->buttons = {
        {"back", dummy}};

    /*
    NOTE:
        - Loading assets have their own functions just to not clump
        the constructor.
    */
    this->loadButtons();
}

Settings::~Settings()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

void Settings::loadButtons()
{
    /*
    NOTE:
        - The starting coordinate of the buttons is initialized to
        `0`. We will align it later to the center.
    */

    const int START_X = 0, START_Y = 400, SPACING_Y = 5;
    int greatest_y = START_Y;
    for (int i = 0; i < this->buttons.size(); i++)
    {
        /*
        NOTE:
            - This part is just constructing the buttons. The prefix
            in the pair will determine its corresponding image asset.
        */
        Coordinates position = Coordinates(START_X, SPACING_Y + greatest_y);
        SDL_Renderer *rend = this->getContext()->getRenderer();
        this->buttons[i].second = Creator().createButton(rend, this->buttons[i].first, position);

        /*
        NOTE:
            - Updating the greatest y-coordinate to determine where
            the next button will go.
        */
        greatest_y = this->buttons[i].second.getBottomBound() + SPACING_Y;

        /*
        NOTE:
            - Centering/aligning the buttons. We need to reconstruct
            the button because we need to query the width and height
            information.
        */
        position = Coordinates(this->getContext()->getScreenWidth() / 2 -
                                   this->buttons[i].second.getWidth() / 2,
                               position.getY());

        this->buttons[i].second = Creator().createButton(
            rend, this->buttons[i].first, position);
    }
}

/*
SECTION 2: OTHER METHODS
*/
void Settings::switchState()
{
    UserEvent *actions = this->getContext()->getUserActions();

    /*
    NOTE:
        - We have to use the array of pointers because if
        we put the actual objects in the array then they would
        just be copies of the original object instead of the
        actual objects themselves.
    */
    for (int i = 0; i < this->buttons.size(); i++)
    {
        Button *button = &this->buttons[i].second;

        /*
        NOTE:
            - Now to see if the cursor is within the bounds of
            the button.
        */
        if (*actions->mouse_x >= button->getLeftBound() &&
            *actions->mouse_x <= button->getRightBound() &&
            *actions->mouse_y >= button->getTopBound() &&
            *actions->mouse_y <= button->getBottomBound())
        {
            /*
            NOTE:
                - We use the boolean value of the user event
                structure to directly set the button.
            */
            button->setHovering(true);
            button->setPressed(*actions->mouse_down);
        }
        else
        {
            button->setHovering(false);
            button->setPressed(false);
        }
    }

    /*
    NOTE:
        - Manipulating the context from here.
    */
    for (int i = 0; i < this->buttons.size(); i++)
    {
        string name = this->buttons[i].first;
        Button *button = &this->buttons[i].second;

        if (button->isPressed())
        {
            if (name == "back")
            {
                this->getContext()->setNavigation(
                    new Menu(this->getContext()));
            }
        }
    }
}

void Settings::update()
{
    /*
    NOTE:
        - Calling all the related functions (accounted for
        more number of functions in the future).
    */
    for (int i = 0; i < this->buttons.size(); i++)
    {
        this->buttons[i].second.update();
    }
    /*
    NOTE:
        - Switching pages
    */
    this->switchState();
}

void Settings::render()
{
    for (int i = 0; i < this->buttons.size(); i++)
    {
        this->buttons[i].second.render(this->getContext()->getRenderer(),
                                       false);
    }
}