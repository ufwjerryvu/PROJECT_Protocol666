#include "Creator.h"

#include <Gameplay.h>

/*
SECTION 1: CONSTRUCTORS AND DESTRUCTORS
*/
Creator::Creator()
{
    /*
    NOTE:
        - Empty, permanently.
    */
}

Creator::~Creator()
{
    /*
    NOTE:
        - Empty, permanently.
    */
}

/*
SECTION 2: CREATOR FUNCTIONS
*/
Button Creator::createButton(SDL_Renderer *renderer, string name, Coordinates position)
{
    FileHandler file = FileHandler();
    string types[] = {"idle", "hover", "pressed"};
    map<string, SDL_Texture *> animation;

    for (string type : types)
    {
        string path = "../Assets/Sprite/Button/" + name + "_" + type + ".png";
        animation[type] = file.loadTexture(renderer, path);
    }

    return Button(position, animation);
}

Player *Creator::createPlayer(Gameplay *context)
{
    Player *player = new Player(context);

    Animator<string> animator;
    vector<SDL_Texture *> seq;
    map<string, Animation> animations;

    // RUN ANIMATION ----------------------------------------------
    SDL_Renderer *renderer = context->getContext()->getRenderer();
    for (char i = '1'; i < '9'; i++)
    {
        string dir = "../Assets/Sprite/Character/Player/Ragdoll/run" + string(1, i);
        dir += ".png";
        seq.push_back(FileHandler().loadTexture(renderer, dir));
    }

    animations["run"] = Animation();
    animations["run"].setFrames(seq);
    animations["run"].setInterval(5);

    // ROLL ANIMATION ----------------------------------------------
    seq = {};
    for (char i = '1'; i < '9'; i++)
    {
        string dir = "../Assets/Sprite/Character/Player/Ragdoll/roll" + string(1, i);
        dir += ".png";
        seq.push_back(FileHandler().loadTexture(renderer, dir));
    }

    animations["roll"] = Animation();
    animations["roll"].setFrames(seq);
    animations["roll"].setInterval(4);

    // IDLE ANIMATION ----------------------------------------------
    seq = {};
    for (char i = '1'; i < '5'; i++)
    {
        string dir = "../Assets/Sprite/Character/Player/Ragdoll/idle" + string(1, i);
        dir += ".png";
        seq.push_back(FileHandler().loadTexture(renderer, dir));
    }

    animations["idle"] = Animation();
    animations["idle"].setFrames(seq);
    animations["idle"].setInterval(9);

    // FALL ANIMATION ----------------------------------------------
    seq = {};

    string dir = "../Assets/Sprite/Character/Player/Ragdoll/fall.png";

    seq.push_back(FileHandler().loadTexture(renderer, dir));

    animations["fall"] = Animation();
    animations["fall"].setFrames(seq);
    animations["fall"].setInterval(0);

    // JUMP ANIMATION ----------------------------------------------
    seq = {};

    dir = "../Assets/Sprite/Character/Player/Ragdoll/jump.png";

    seq.push_back(FileHandler().loadTexture(renderer, dir));

    animations["jump"] = Animation();
    animations["jump"].setFrames(seq);
    animations["jump"].setInterval(0);

    // OTHER SETTERS ------------------------------------------------

    animator.setAnimations(animations);
    animator.setKey("idle");

    player->setAnimator(animator);
    player->setAbsolutePosition(Coordinates(100, 100));
    player->setDirectionFacing(Direction::LEFT);
    player->Fallable::setGravitationalAcceleration(2);
    player->Fallable::setTerminalVelocity(12);
    player->Jumpable::setInitialVelocity(8);
    player->Verticality::setInterval(6);
    player->Runnable::setSpeed(4);
    player->Rollable::setSpeed(6);
    player->setTexture(animator.getCurrentFrame());

    return player;
}