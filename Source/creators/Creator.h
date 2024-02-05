/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/
#pragma once 

#include <Systems.h>

#include <FileHandler.h>
#include <Button.h>
#include <Player.h>
#include <Direction.h>
#include <Animator.h>
#include <Animation.h>
#include <Master.h>
#include <Ground.h>
#include <Moveable.h>
#include <Platform.h>
#include <ArrayPlatform.h>

class Gameplay;

class Creator
{
public:
    /*
    SECTION 1: CONSTRUCTORS AND DESTRUCTORS
    */
    Creator();
    ~Creator();

    /*
    SECTION 2: CREATOR FUNCTIONS
    */
    Button createButton(SDL_Renderer* renderer, string name, Coordinates position);
    Player *createPlayer(Gameplay* context);
    Ground *createGround(Gameplay* context);
    ArrayPlatform *createThinPlatform(Gameplay *context, Coordinates position);
    ArrayPlatform *createThickPlatform(Gameplay *context, Coordinates position);
    vector<Platform *> createArrayPlatforms(Gameplay *context);
};