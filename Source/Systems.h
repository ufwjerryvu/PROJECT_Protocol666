#pragma once

/*
IMPORTING THE C++ STANDARD LIBRARIES
*/
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <utility>
#include <map>

/*
IMPORTING THE C STANDARD LIBRARIES
*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
IMPORTING THE SDL LIBRARIES
*/
#ifdef _WIN32
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
#elif __APPLE__
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_mixer.h>
#endif

/*
IMPORTING THE SQLITE DATABASE MANAGEMENT LIBRARY
*/
#include <sqlite3.h>

using namespace std;

/*
DECLARING THE USER-EVENT STRUCTURE
*/
struct UserEvent
{
	bool *key_down, *key_up;
	const Uint8 *current_key_states;

	bool *mouse_down, *mouse_up;
	int *mouse_x, *mouse_y;

	bool *simultaneous_horizontal_keys_pressed;
	int *current_horizontal_key;
};