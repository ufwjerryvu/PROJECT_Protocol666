#include "Menu.h"

#include <Master.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Menu::Menu()
{
    /*
    NOTE:
        - Do not use.
    */
}

Menu::Menu(Master *context) : Navigation(context)
{
    /*
    NOTE:
        - Using the super constructor. Also loading the buttons.
        Loading assets have their own functions just to not clump
        the constructor. We might need more assets in the future.
    */
    this->loadButtons();
}

Menu::~Menu()
{
    /*
    TEMPORARY:
        - Empty, for now.
    */
}

void Menu::loadButtons()
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
        {"play", &this->play},
        {"instructions", &this->instructions},
        {"settings", &this->settings},
        {"about", &this->about},
        {"quit", &this->quit}};

    /*
    NOTE:
        - The starting coordinate of the buttons is initialized to
        `0`. We will align it later to the center.
    */

    const int START_X = 0, START_Y = 130, SPACING_Y = 5;
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
void Menu::switchState()
{
    Button *buttons[] = {&this->play, &this->settings, &this->about,
                         &this->instructions, &this->quit};

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
    if (this->play.isPressed())
    {
        /*
        TEMPORARY:
            - Empty for now.
        */
    }
    else if (this->settings.isPressed())
    {
        /*
        NOTE:
            - Switching the page to settings.
        */
        this->getContext()->setNavigation(new Settings(this->getContext()));
    }
    else if (this->instructions.isPressed())
    {
        /*
        NOTE:
            - Switching the page to instructions.
        */
        this->getContext()->setNavigation(new Instructions(this->getContext()));
    }
    else if (this->about.isPressed())
    {
        /*
        NOTE:
            - Switching the page to about.
        */
        this->getContext()->setNavigation(new About(this->getContext()));
    }
    else if (this->quit.isPressed())
    {
        /*
        NOTE:
            - Exiting the program but also freeing the memory.
        */
        this->getContext()->close();
        exit(0);
    }
}

void Menu::update()
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

void Menu::render()
{
    /*
    TEMPORARY:
        - Rendering all the buttons. Would be better if this was
        done using a loop instead.
    */
    this->play.render(this->getContext()->getRenderer(), false);
    this->about.render(this->getContext()->getRenderer(), false);
    this->instructions.render(this->getContext()->getRenderer(), false);
    this->settings.render(this->getContext()->getRenderer(), false);
    this->quit.render(this->getContext()->getRenderer(), false);
}