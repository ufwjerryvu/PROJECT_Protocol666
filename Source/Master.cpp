#include "Master.h"

#include <Navigation.h>
#include <Menu.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Master::Master(UserEvent user_actions)
{
    /*
    NOTE:
        - Initializing all SDL subsystems.
    */

    if (!this->initialize())
    {
        cerr << "Error from Master(): cannot initialize SDL subsystems." << endl;
    }

    /*
    NOTE:
        - Initializing the camera.
    */
    SDL_Rect camera = {0, 0, this->SCREEN_WIDTH, this->SCREEN_HEIGHT};
    this->user_actions = user_actions;

    /*
    NOTE:
         - Allocating a new object. Remember to free memory when the state
        changes or when the master class is closed. Since `Navigation` is
        the parent class of `Menu`, we need to dynamically allocate these
        things using pointers.
    */

    this->navigation = new Menu(this);
    // this->gameplay = Gameplay();
}

/*
SECTION 2: SYSTEM INITIALIZATIONS AND DESTRUCTIONS
*/
bool Master::initialize()
{
    bool success = true;

    /*
    NOTE:
        - Initializing the SDL video subsystems. This step is modified
        from lazyfoo.net.
    */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "Error from Master.initialize(): cannot initialize the SDL video subsystems." << endl;
        success = false;
        return success;
    }

    /*
    NOTE:
        - Attempting to create a window. This step is also modified
        from lazyfoo.net.
    */
    this->window = SDL_CreateWindow("Protocol 666", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->window == NULL)
    {
        cerr << "Error from Master.initialize(): cannot create window." << endl;
        success = false;
        return success;
    }

    /*
    NOTE:
        - Also modified from lazyfoo.net. All textures of the game
        objects will be rendered via this renderer. If it fails then
        nothing gets displayed.
    */
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == NULL)
    {
        cerr << "Error from Master.initialize(): cannot create renderer." << endl;
        success = false;
        return success;
    }

    /*
    NOTE:
        - Initializing the SDL IMG library, specifically to load
        in and display PNG images. Modified from lazyfoo.net.

        - The bitwise AND operation below is used to make sure
        the IMG_Init() function returns its argument. If the function
        doesn't return the value of its argument then the whole
        expression evaluates to 1, and 0 if vice versa.

        - In the document, IMG_INIT_PNG = 2. If IMG_Init(IMG_INIT_PNG)
        returns 2, then IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG is 2 & 2
        which would be evaluated to 1. At this point, we've successfully
        initiated the IMG subsystem for PNG images.

        - However, if IMG_Init(IMG_INIT_PNG) would return something else
        like 4, which presumably is the value for IMG_INIT_JPEG then
        the expression IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG is 4 & 2,
        which would then be evaluated to 0. A zero means we've failed
        to initialize the PNG subsystems.

        - This was just my rationale --- Jerry.
    */
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cerr << "Error from Master.initialize(): cannot initialize IMG subsystems." << endl;
        success = false;
        return success;
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 90, 90, 90, 90);
    }

    /*
    NOTE:
        - Modified from lazyfoo.net. A negative one means the
        TTF subsystem has failed to initialize.
    */
    if (TTF_Init() == -1)
    {
        cerr << "Error from Master.initialize(): could not initialize TTF subsystems." << endl;
        success = false;
        return success;
    }

    return success;
}

void Master::close()
{
    /*
    NOTE:
        - Deleting allocated memory.
    */
    delete this->navigation;
}

/*
SECTION 3: STATE CHANGES
*/
void Master::setNavigation(Navigation *page)
{
    /*
    NOTE:
        - We first need to dynamically free the memory from
        the old navigation member.
    */
    delete this->navigation;

    /*
    NOTE:
        - Now set the member. Memory is dynamically allocated
        upon calling the function. 
    */
    this->navigation = page;
}
// setGameplay(Gameplay gameplay){this->gameplay = gameplay;}

/*
SECTION 4: GETTERS
*/
SDL_Window *Master::getWindow() { return this->window; }
SDL_Renderer *Master::getRenderer() { return this->renderer; }
int Master::getScreenWidth() { return this->SCREEN_WIDTH; }
int Master::getScreenHeight() { return this->SCREEN_HEIGHT; }
UserEvent *Master::getUserActions() { return &this->user_actions; }
int Master::getFrameRate() { return this->FRAME_RATE; }

/*
SECTION 5: UPDATE AND DISPLAY
*/
void Master::update()
{
    /*
    NOTE:
        - Updates from multiple objects.
    */
    this->navigation->update();
    //this->gameplay.update();
}

void Master::render()
{
    /*
    NOTE:
        - Clearing everything in the renderer.
    */
    SDL_RenderClear(this->renderer);

    /*
    NOTE:
        - Rendering the current state.
    */
    this->navigation->render();

    /*
    NOTE:
        - Finally rendering everything.
    */
    SDL_RenderPresent(this->renderer);
}
