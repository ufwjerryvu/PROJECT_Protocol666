#pragma once

#include <Systems.h>

#include <Sprite.h>

class Master;
class Creator;
class Player;
class Ground;
class Platform;

class Gameplay
{
private:
    Master *context;

    /*
    TEMPORARY:
        - These are temporary numbers.
    */
    int level_width = 1500;
    int level_height = 800;

    SDL_Rect camera;

    Player *player;
    vector<Ground *> grounds;
    vector<Platform *> platforms;

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
    Master *getContext();
    int getLevelWidth();
    int getLevelHeight();

    /*
    SECTION 3: OTHER METHODS
    */
    void updateCamera();
    void updateRenderPos();
    void updateCollisions();

    void update();
    void render();
};