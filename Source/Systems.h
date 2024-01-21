#pragma once

/*
IMPORTING THE STANDARD LIBRARIES
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>

/*
IMPORTING THE SDL LIBRARIES
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/*
IMPORTING THE SQLITE DATABASE MANAGEMENT LIBRARY
*/
#include <SQLite3.h>

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

/*
REDEFINING THE EXCEPTION THROWING
*/
void throwException(string msg = "Error: exception thrown\n"){
	throw runtime_error(msg + "\n");
}