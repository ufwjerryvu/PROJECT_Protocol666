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

	string parseTextFile(string path);

	vector<string> parseLevelConfigPaths();

	vector<int> parseDimensions(string level_config_path);
	int parseLevelWidth(string level_config_path);
	int parseLevelHeight(string level_config_path);

	Player loadTestRagdoll(SDL_Renderer* renderer, UserEvent user_actions);
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

vector<string> FileHandling::parseLevelConfigPaths() {

	/*
	NOTE:
		- Parse txt file into `file_content` using FileHandling::parseTextFile()
		- split content of `file_content` line by line and return a vector<string> using Utilities::split()
		- Add the paths in the `split_content` vector into paths_vector, ignoring comments and empty lines.
	*/

	vector<string> paths_vector;
	Utilities util;
	string file_content = parseTextFile("Configurations/paths_level_config.txt");
	
	vector<string> split_content = util.split(file_content, "\n");

	for (int i = 0; i < split_content.size(); i++) {
		if (split_content[i][0] == '#' || split_content[i] == "") {
			continue;
		}
		paths_vector.push_back(split_content[i]);
	}

	return paths_vector;
}

vector<int> FileHandling::parseDimensions(string level_config_path) {
	/*
	 NOTE:
		- This function parses the Level Configuration text file to read and
		return a vector<int> for dimensions

		- The text file content is first read into a string

		- Then the contents of this string is split into smaller vectors until a vector
		containing only dimension values is created (`dimension.str`)

		- Elements inside `dimension.str` is converted into floats and added to `dimensions`

		- Function returns `dimensions`
	*/
	
	vector<int> dimensions;
	Utilities util;

	string file_content = parseTextFile(level_config_path);

	vector<string> content_vec = util.split(file_content, "\n\n");

	vector<string> second_line = util.split(content_vec[1], "\n");

	vector<string> dimension_str = util.split(second_line[1], ",");

	for (int i = 0; i < dimension_str.size(); i++) {
		int conversion = util.strToFloat(dimension_str[i]);
		dimensions.push_back(conversion);
	}

	return dimensions;
}

int FileHandling::parseLevelWidth(string level_config_path) {
	vector<int> dimension = parseDimensions(level_config_path);
	int width = dimension[0];
	return width;
}

int FileHandling::parseLevelHeight(string level_config_path) {
	vector<int> dimension = parseDimensions(level_config_path);
	int height = dimension[1];
	return height;
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
