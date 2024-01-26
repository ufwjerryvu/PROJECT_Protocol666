#pragma once

#include <Systems.h>
#include <Sprite.h>
#include <FileHandler.h>

class Master;
class Player;

class Gameplay
{
private:
    Master *context;

    int level_width = 1400;
    int level_height = 2800;

    SDL_Rect camera;

    Player *player;
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Gameplay();
    Gameplay(Master *context);
    ~Gameplay();

    /*
    SECTION 2: GETTER AND SETTER METHODS
    */
    Master* getContext();
    int getLevelWidth();
    int getLevelHeight();

    /*
    SECTION 3: OTHER METHODS
    */
    void updateCamera();
    void updateRenderPos();

    void update();
    void render();
};