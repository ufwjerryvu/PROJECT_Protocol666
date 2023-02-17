/*
@ COLLABORATORS: Jerry Vu, An Luu
@ CLASS DESIGNERS: Jerry Vu, An Luu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Utilities.h"

#include "Sprite.h"

#include "Character.h"
#include "Player.h"

#include "Terrain.h"
#include "Ground.h"
#include "Platform.h"

/*
NOTE:
	- This class will be handling all file input/output.
*/
class FileHandling {
public:
	/*
	SECTION 1: BASIC LOADING
	*/
	SDL_Texture* loadTexture(SDL_Renderer* renderer, string path);
	string parseTextFile(string path);

	/*
	SECTION 2: CONFIGURATIONS LOADING
	*/
	vector<string> parseLevelConfigPaths();
	vector<int> parseLevelDimensions(string level_config_path);
	int parseLevelWidth(string level_config_path);
	int parseLevelHeight(string level_config_path);

	/*
	SECTION 3: ANIMATION/ASSEMBLY LOADING
	*/
	vector<string> parseFileForAnimationPaths(string file_for_animation_paths);
	Animation loadAnimation(SDL_Renderer* renderer, string file_for_animation_paths);

	/*
	SECTION 4: ASSETS LOADING
	*/
	vector<string> getLinesFromFlag(string content, string flag);
	string getFirstLineFromFlag(string content, string flag);

	Player loadPlayer(SDL_Renderer* renderer, string level_config_path, UserEvent user_actions, string chosen_type);
};

/*
SECTION 1: BASIC LOADING
*/
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

/*
SECTION 2: CONFIGURATIONS LOADING
*/
vector<string> FileHandling::parseLevelConfigPaths() {

	/*
	NOTE:
		- Parse txt file into `file_content` using 
		FileHandling::parseTextFile().
	*/

	vector<string> paths_vector;
	Utilities util;
	string file_content = parseTextFile("Configurations/paths_level_config.txt");
	
	/*
	NOTE:
		- Split content of `file_content` line by
		line and return a vector<string> using 
		Utilities::split().
	*/
	vector<string> split_content = util.split(file_content, "\n");

	/*
	NOTE:
		- Add the paths in the `split_content` 
		vector into paths_vector, ignoring comments
		and empty lines.
	*/
	for (int i = 0; i < split_content.size(); i++) {
		if (split_content[i][0] == '#' || split_content[i] == "") {
			continue;
		}
		paths_vector.push_back(split_content[i]);
	}

	return paths_vector;
}

vector<int> FileHandling::parseLevelDimensions(string level_config_path) {
	/*
	NOTE:
		- Parsing the level config text file
		and splitting its content into a vector of
		strings.
	*/
	Utilities util;
	string file_content = this->parseTextFile(level_config_path);
	vector<string> file_content_split = util.split(file_content, "\n");
	vector<int> dimensions_vec;

	/*
	NOTE:
		- Iterating through the contents of the file.
	*/
	for (int index = 0; index < file_content_split.size(); index++) {
		/*
		NOTE:
			- If it's an empty line then we ignore that
			line.
		*/
		if (file_content_split[index] == "") {
			continue;
		}
		else if (file_content_split[index].length()) {
			/*
			NOTE:
				- But if it's a non-empty line but is 
				denoted by a hashtag -- which is a comment
				then we also ignore it.
			*/
			if (file_content_split[index][0] == '#') {
				continue;
			}
			else {
				vector<string> line_split = util.split(file_content_split[index], ",");
				const int NUMBER_OF_DIMENSIONS = 2;
				/*
				NOTE:
					- If there are less than two arguments then the
					formatting is invalid.
				*/
				if (line_split.size() != NUMBER_OF_DIMENSIONS) {
					cerr << "Error from FileHandling::parseDimensions(): invalid number of arguments." << endl;
				}
				else {
					/*
					NOTE:
						- If the first element or the second element isn't
						a number then the formatting is also invalid.
					*/
					if (!util.checkFloat(line_split[0]) || !util.checkFloat(line_split[1])) {
						cerr << "Error from FileHandling::parseDimensions(): dimensions must be numerical." << endl;
					}
					else {
						dimensions_vec.push_back(util.strToFloat(line_split[0]));
						dimensions_vec.push_back(util.strToFloat(line_split[1]));
					}
				}

				/*
				NOTE:
					- We break out of the loop because dimensions 
					will always be the first configuration line in the
					text file.
				*/
				break;
			}
		}
	}

	return dimensions_vec;
}

int FileHandling::parseLevelWidth(string level_config_path) {
	vector<int> dimension = parseLevelDimensions(level_config_path);
	int width = dimension[0];
	return width;
}
int FileHandling::parseLevelHeight(string level_config_path) {
	vector<int> dimension = parseLevelDimensions(level_config_path);
	int height = dimension[1];
	return height;
}

/*
SECTION 3: ANIMATION / ASSEMBLY LOADING
*/
vector<string> FileHandling::parseFileForAnimationPaths(string file_for_animation_paths) {
	vector<string> path_vec;
	Utilities util;
	string file_content = parseTextFile(file_for_animation_paths);

	vector<string> split_content = util.split(file_content, "\n");

	for (int i = 0; i < split_content.size(); i++) {
		if (split_content[i] == "") {
			continue;
		}
		if (split_content[i].length() >= 0) {
			if (split_content[i][0] == '#') {
				continue;
			}
		}
		path_vec.push_back(split_content[i]);
	}

	return path_vec;
}

Animation FileHandling::loadAnimation(SDL_Renderer* renderer, string file_for_animation_paths) {
	/*
	NOTE:
		- This function returns an initialized Animation structure 
		with animation frames of all types read from a text file
		containing the paths to each respective frame image.
	*/

	FileHandling file;
	Animation animation;

	/*
	NOTE:
		- After parsing each individual paths, each line is split 
		and assigned into the `anim_paths_vec` string vector.
	*/
	vector<string> anim_paths_vec = parseFileForAnimationPaths(file_for_animation_paths);
	string current_flag = "";

	/*
	NOTE:
		- Each element in `anim_paths_vec` is iterated. Upon each iteration,
		when encountering a path to a frame image, loadTexture() is called to 
		load an SDL_Texture variable using the encountered path as parameter. 
		This texture is then added to the animation struture.
	*/
	for (int i = 0; i < anim_paths_vec.size(); i++) {
		/*
		NOTE:
			- Setting a flag for the animation type.
		*/
		if (anim_paths_vec[i] == "<idle>" || anim_paths_vec[i] == "<running>" 
			|| anim_paths_vec[i] == "<jumping>" || anim_paths_vec[i] == "<falling>") {
			current_flag = anim_paths_vec[i];
		}

		/*
		NOTE:
			- Loading the animation textures in given the paths.
		*/
		if (current_flag == "<idle>" && anim_paths_vec[i] != current_flag && anim_paths_vec[i] != "</idle>") {
			animation.frames_idle.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (current_flag == "<running>" && anim_paths_vec[i] != current_flag && anim_paths_vec[i] != "</running>") {
			animation.frames_running.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (current_flag == "<jumping>" && anim_paths_vec[i] != current_flag && anim_paths_vec[i] != "</jumping>") {
			animation.frames_jumping.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (current_flag == "<falling>" && anim_paths_vec[i] != current_flag && anim_paths_vec[i] != "</falling>") {
			animation.frames_falling.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
	}

	return animation;
}

/*
SECTION 4: ASSETS LOADING
*/
vector<string> FileHandling::getLinesFromFlag(string content, string flag) {
	Utilities util;
	vector<string> split_content = util.split(content, "\n");

	vector<string> current_line_split;
	vector<string> ret_vec;


	/*
	NOTE:
		- Looping through the contents of the config file.
	*/
	for (int index = 0; index < split_content.size(); index++) {
		/*
		NOTE:
			- We ignore the lines that are empty.
		*/
		if (!split_content[index].length() || split_content[index] == "") {
			continue;
		}
		else {
			/*
			NOTE:
				- We ignore the comments as well.
			*/
			if (split_content[index][0] == '#') {
				continue;
			}

			current_line_split = util.split(split_content[index], ",");
			if (current_line_split.size()) {
				/*
				NOTE:
					- If we see the flag then we return the
					current element in the split content
					vector.
				*/
				if (current_line_split[0] == flag) {
					ret_vec.push_back(split_content[index]);
				}
			}
		}
	}

	return ret_vec;
}

string FileHandling::getFirstLineFromFlag(string content, string flag) {
	vector<string> lines = getLinesFromFlag(content, flag);

	if (lines.size()) {
		return lines[0];
	}

	return "";
}

Player FileHandling::loadPlayer(SDL_Renderer* renderer, string level_config_path, UserEvent user_actions, string chosen_type = "ragdoll") {
	Utilities util;
	Animation animation;

	/*
	NOTE:
		- These are the standard characters and animation frames
		for the characters.
	*/
	if (chosen_type == "ragdoll") {
		animation = this->loadAnimation(renderer, "Configurations/Animation/Ragdoll.txt");
	}
	else if (chosen_type == " theresa") {
		animation = this->loadAnimation(renderer, "Configurations/Animation/Theresa.txt");
	}
	else if(chosen_type == "may") {
		animation = this->loadAnimation(renderer, "Configurations/Animation/May.txt");
	}

	/*
	NOTE: 
		- We get the line that we want to initialize the player.
	*/
	string player_config = this->getFirstLineFromFlag(this->parseTextFile(level_config_path), "Player");

	const int NUMBER_OF_ARGUMENTS = 3;
	if (util.split(player_config, ",").size() != NUMBER_OF_ARGUMENTS) {
		cerr << "Error from FileHandling::loadPlayer(): invalid configuration formatting." << endl;
		return Player();
	}

	int initial_x = util.strToFloat(util.split(player_config, ",")[1]);
	int initial_y = util.strToFloat(util.split(player_config, ",")[2]);

	Player ret_obj(initial_x, initial_y, animation, user_actions);

	return ret_obj;
}

