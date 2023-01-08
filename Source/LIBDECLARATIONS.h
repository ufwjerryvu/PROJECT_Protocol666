#pragma once

/*
IMPORTING THE STANDARD LIBRARIES
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
IMPORTING THE SDL LIBRARIES
*/
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

/*
INITIALIZING GLOBAL VARIABLES
*/
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 500;

/*
INITIALIZING SDL-RELATED INSTANCES
*/
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

