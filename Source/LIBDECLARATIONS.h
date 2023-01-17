#pragma once

/*
IMPORTING THE STANDARD LIBRARIES
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

/*
IMPORTING THE SDL LIBRARIES
*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

/*
DECLARING THE USER-EVENT STRUCTURE
*/
struct UserEvent {
	bool* key_down, * key_up;
	const Uint8* current_key_states;

	bool* mouse_down, * mouse_up;
	int* mouse_x, * mouse_y;
};
