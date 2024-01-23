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
        - Using the super constructor. Also loading the buttons.
        Loading assets have their own functions just to not clump
        the constructor. We might need more assets in the future.
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
        - Loading the buttons in the file.
    */
    FileHandler file = FileHandler();

    /*
    NOTE:
        - The pair consists of the prefix (first) and the pointer
        to the button (second).
    */
    pair<string, Button *> list[] = {
        {"back", &this->back}};

    /*
    NOTE:
        - The starting coordinate of the buttons is initialized to
        `0`. We will align it later to the center.
    */

    const int START_X = 0, START_Y = 400, SPACING_Y = 5;
    int greatest_y = START_Y;
    for (int i = 0; i < sizeof(list) / sizeof(pair<string, Button *>); i++)
    {
        /*
        NOTE:
            - This part is just constructing the buttons. The prefix
            in the pair will determine its corresponding image asset.
        */
        string path = "Assets/Sprite/Button/" + list[i].first + "_idle.png";

        Coordinates position = Coordinates(START_X, SPACING_Y + greatest_y);
        SDL_Texture *texture = file.loadTexture(this->getContext()->getRenderer(), path);

        (*list[i].second) = Button(position, texture);

        /*
        NOTE:
            - Updating the greatest y-coordinate to determine where
            the next button will go.
        */
        greatest_y = list[i].second->getBottomBound() + SPACING_Y;

        /*
        NOTE:
            - Centering/aligning the buttons. We need to reconstruct
            the button because we need to query the width and height
            information.
        */
        position = Coordinates(this->getContext()->getScreenWidth() / 2 -
                                   list[i].second->getWidth() / 2,
                               position.getY());
        (*list[i].second) = Button(position, texture);
    }
}

/*
SECTION 2: OTHER METHODS
*/
void Settings::switchState()
{
    Button *buttons[] = {&this->back};

    UserEvent *actions = this->getContext()->getUserActions();

    /*
    NOTE:
        - We have to use the array of pointers because if
        we put the actual objects in the array then they would
        just be copies of the original object instead of the
        actual objects themselves.
    */
    for (Button *button : buttons)
    {
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
            button->setPressed(*actions->mouse_down);
        }
    }

    /*
    NOTE:
        - Manipulating the context from here.
    */
    if (this->back.isPressed())
    {
        /*
        NOTE:
            - Switching back to the main menu.
        */
        this->getContext()->setNavigation(new Menu(this->getContext()));
    }
}

void Settings::update()
{
    /*
    NOTE:
        - Calling all the related functions (accounted for 
        more number of functions in the future).
    */

    /*
    NOTE:
        - Switching pages
    */
    this->switchState();
}

void Settings::render()
{
    /*
    TEMPORARY:
        - Rendering all the buttons. Would be better if this was
        done using a loop instead.
    */
    this->back.render(this->getContext()->getRenderer(), false);
}