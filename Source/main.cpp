#include "LIBDECLARATIONS.h"

#include "Game.h"

int main(int argc, char* argv[]) {

	/*
	NOTE:
		- Keeping track of user-induced events.
	*/

	bool key_down = false, key_up = true;
	const Uint8* current_key_states = SDL_GetKeyboardState(NULL);

	bool mouse_down = false, mouse_up = true;
	int mouse_x = 0, mouse_y = 0;

	UserEvent user_actions = { &key_down, &key_up, current_key_states,
		&mouse_down, &mouse_up, &mouse_x, &mouse_y };

	/*
	NOTE:
		- Declaring the game object and within it, SDL
		subsystems are initialized.
	*/
	Game game(user_actions);

	/*
	NOTE:
		- Game loop.
	*/
	bool quit = false;
	SDL_Event action;

	const int TIME_PER_FRAME_MS = 1000 / game.FRAME_RATE;
	while (!quit) {
		int start_time = SDL_GetTicks();

		while (SDL_PollEvent(&action) != 0) {
			if (action.type == SDL_QUIT) {
				quit = true;
			}

			/*
			NOTE: 
				- Getting all user-related inputs.
			*/
			if (action.type == SDL_KEYDOWN) {
				key_down = true;
				key_up = false;
			}

			if (action.type == SDL_KEYUP) {
				key_down = false;
				key_up = true;
			}

			if (action.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&mouse_x, &mouse_y);
			}

			if (action.type == SDL_MOUSEBUTTONDOWN) {
				mouse_down = true;
				mouse_up = false;
			}

			if (action.type == SDL_MOUSEBUTTONUP) {
				mouse_down = false;
				mouse_up = true;
			}
		}

		/*
		NOTE:
			- The game logic gets updated here and 
			then it gets rendered afterwards.
		*/
		game.update();
		game.render();

		/*
		NOTE:
			- This delay is kept for a constant frame rate
			as defined in the Game class.
		*/
		int end_time = SDL_GetTicks();

		if (end_time - start_time < TIME_PER_FRAME_MS) {
			SDL_Delay(TIME_PER_FRAME_MS - (end_time - start_time));
		}
	}

	game.close();
	return 0;
}