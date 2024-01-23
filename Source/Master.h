/*
@ COLLABORATORS: Jerry Vu
@ DESIGNERS: Jerry Vu
*/

#pragma once

#include <Systems.h>

#include <Sprite.h>

class Navigation;

class Master
{
private:
	/*
	SECTION 0A: SYSTEM VARIABLES, CONSTANTS, AND THE EVENT HANDLER
	*/
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	static const int SCREEN_WIDTH = 900;
	static const int SCREEN_HEIGHT = 500;

	UserEvent user_actions;

	const int FRAME_RATE = 60;

	/*
	SECTION 0B: STATE CONTROL AND BRANCHES
	*/
	Navigation *navigation;
	// Gameplay *gampelay;

public:
	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	Master(UserEvent user_actions);

	/*
	SECTION 2: SYSTEM INITIALIZATIONS AND DESTRUCTIONS
	*/
	bool initialize();
	void close();

	/*
	SECTION 3: STATE CHANGES
	*/
	void setNavigation(Navigation *navigation);
	// void setGameplay(Gameplay gameplay);

	/*
	SECTION 4: GETTERS
	*/
	SDL_Window *getWindow();
	SDL_Renderer *getRenderer();
	int getScreenWidth();
	int getScreenHeight();
	UserEvent *getUserActions();
	int getFrameRate();

	/*
	SECTION 5: UPDATE AND DISPLAY
	*/
	void update();
	void render();
};