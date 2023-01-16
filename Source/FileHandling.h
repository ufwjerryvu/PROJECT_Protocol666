/*
@ COLLABORATORS: Jerry Vu, An Luu
@ CLASS DESIGNERS: Jerry Vu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Utilities.h"

#include "Sprite.h"

#include "Character.h"
#include "Player.h"

/*
NOTE:
	- This class will be handling all file input/output.
*/
class FileHandling {
public:
	SDL_Texture* loadTexture(SDL_Renderer* renderer, string path);

	Player loadTestRagdoll(SDL_Renderer* renderer, UserEvent user_actions);

	string parseTextFile(string path);
};

SDL_Texture* FileHandling::loadTexture(SDL_Renderer* renderer, string path) {
	/*
	NOTE:
		- Standard texture-loading method.
	*/
	SDL_Texture* temp = IMG_LoadTexture(renderer, path.c_str());

	if (temp == NULL) {
		cerr << "Error from FileHandling.loadTexture(): cannot "
			<< "load texture from the specified path \'" << path
			<< "\'." << endl;
	}
	return temp;
}

Player FileHandling::loadTestRagdoll(SDL_Renderer* renderer, UserEvent user_actions) {
	/*
	NOTE:
		- This reads in a ragdoll for testing purposes.
	*/

	int x = 0, y = 0;

	vector<SDL_Texture*> anm_frames_idle;
	vector<SDL_Texture*> anm_frames_moving;

	anm_frames_idle.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/idle1.png"));
	anm_frames_idle.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/idle2.png"));
	anm_frames_idle.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/idle3.png"));
	anm_frames_idle.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/idle4.png"));


	anm_frames_moving.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/run1.png"));
	anm_frames_moving.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/run2.png"));
	anm_frames_moving.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/run3.png"));
	anm_frames_moving.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/run4.png"));
	anm_frames_moving.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/run5.png"));
	anm_frames_moving.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/run6.png"));
	anm_frames_moving.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/run7.png"));
	anm_frames_moving.push_back(loadTexture(renderer, "Assets/Sprite/Character/Player/Ragdoll/run8.png"));

	Player ragdolltest(x, y, anm_frames_idle, anm_frames_moving, user_actions);

	return ragdolltest;
}

string FileHandling::parseTextFile(string path) {
	/*
	NOTE:
		- Declare relevant variables
	*/
	ifstream input_file;
	string temp;
	string content;
	input_file.open(path);

	/*
	NOTE:
		- Loop through each line in file and assign each to `temp`.

		- Add string in `temp` to `content`, add '\n' after each line until EOF is reached
	*/

	while (getline(input_file, temp)) {
		content += temp;
		if (!input_file.eof()) {
			content += '\n';
		}

	}

	return content;

	input_file.close();
}

