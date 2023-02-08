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

	vector<string> parseAnimationPaths(string level_config_path);
	Animation loadAnimation(SDL_Renderer* renderer, string level_config_path);

	Player loadPlayer(SDL_Renderer* renderer, string level_config_path, string animation_path, Animation animation, UserEvent user_actions);
	Ground loadGround(string level_config_path, vector<vector<SDL_Texture*>> texture_blocks, 
						DiscreteDimensions discrete_dimensions);

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
		
		- Split content of `file_content` line by line and return a vector<string> using Utilities::split()
		
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
		- This function returns a vector<int> containing dimensions of the window read from the Level Configuration
		txt file.

		- After parsing file contents at `level_config_path`, each line is split and assigned into the `content_vec`
		string vector.

		- `Content_vec` is iterated to search for the "# Dimensions format: level_width,level_height" element.
		Once found, the line below this line is split and assigned into the `dimension_vec_str` string vector.

		- Elements that contain initial xy coordinates in `dimension_vec_str` is converted to float. Results from the conversion is
		added into the `dimensions_vec` vector with element[0] being the x value and [1] being the y value.

		- `dimensions_vec` is returned.
	*/
	
	vector<int> dimensions_vec;
	Utilities util;
	string file_content = parseTextFile(level_config_path);

	vector<string> dimensions_vec_str;

	vector<string> content_vec = util.split(file_content, "\n");
	for (int i = 0; i < content_vec.size(); i++) {
		if (content_vec[i] == "# Dimensions format: level_width,level_height") {
			dimensions_vec_str = util.split(content_vec[i + 1], ",");
			break;
		}
	}

	for (int i = 0; i < dimensions_vec_str.size(); i++) {
		if (util.checkFloat(dimensions_vec_str[i])) {
			int conversion = util.strToFloat(dimensions_vec_str[i]);
			dimensions_vec.push_back(conversion);
		}
		else {
			continue;
		}
	}

	return dimensions_vec;
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

vector<string> FileHandling::parseAnimationPaths(string level_config_path) {
	vector<string> path_vec;
	Utilities util;
	string file_content = parseTextFile(level_config_path);

	vector<string> split_content = util.split(file_content, "\n");

	for (int i = 0; i < split_content.size(); i++) {
		if (split_content[i][0] == '#' || split_content[i] == "") {
			continue;
		}
		path_vec.push_back(split_content[i]);
	}

	return path_vec;
}

Animation FileHandling::loadAnimation(SDL_Renderer* renderer, string level_config_path) {
	/*
	NOTE:
		- This function returns an initialized Animation structure with animation frames of all types read from a text file
		containing the paths to each respective frame image.

		- After parsing each individual paths, each line is split and assigned into the `anim_paths_vec`
		string vector.

		- Each element in `anim_paths_vec` is iterated. Upon each iteration, when encountering a path to a frame image,
		loadTexture() is called to load an SDL_Texture variable using the encountered path as parameter. This texture is then
		added to the animation struture.
	*/

	FileHandling file;
	Animation animation;

	vector<string> anim_paths_vec = parseAnimationPaths(level_config_path);
	string temp = "";

	for (int i = 0; i < anim_paths_vec.size(); i++) {
		if (anim_paths_vec[i] == "<idle" || anim_paths_vec[i] == "<running>" || anim_paths_vec[i] == "<jumping>" || anim_paths_vec[i] == "<falling>") {
			temp = anim_paths_vec[i];
		}

		if (temp == "<idle>" && anim_paths_vec[i] != temp && anim_paths_vec[i] != "</idle>") {
			animation.frames_idle.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (temp == "<running>" && anim_paths_vec[i] != temp && anim_paths_vec[i] != "</running>") {
			animation.frames_idle.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (temp == "<jumping>" && anim_paths_vec[i] != temp && anim_paths_vec[i] != "</jumping>") {
			animation.frames_idle.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (temp == "<falling>" && anim_paths_vec[i] != temp && anim_paths_vec[i] != "</falling>") {
			animation.frames_idle.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
	}

	return animation;
}

Player FileHandling::loadPlayer(SDL_Renderer* renderer, string level_config_path, string animation_path, Animation animation, UserEvent user_actions) {

	/*
	NOTE:
		- This function returns an initialized Player object with initial xy coordinates read from the 
		Level Configurations text file

		- After parsing file contents at `level_config_path`, each line is split and assigned into the `content_vec` 
		string vector.

		- `Content_vec` is iterated to search for the "# Player format: Object,initial_x,initial_y" element. 
		Once found, the line below this line is split and assigned into the `position_vec_str` string vector.

		- Elements that contain initial xy coordinates in `position_vec_str` is converted to float. Results from the conversion is
		added into the xy_pos vector with element[0] being the x value and [1] being the y value.

		- player's animation is loaded using loadAnimation, with parameters being `renderer` and `animation_path`

		- Player object is constructed with these xy values and returned.
	*/

	Player player;

	vector<int> xy_pos;
	Utilities util;
	string file_content = parseTextFile(level_config_path);
	vector<string> position_vec_str;

	vector<string> content_vec = util.split(file_content, "\n");
	for (int i = 0; i < content_vec.size(); i++) {
		if (content_vec[i] == "# Player format: Object,initial_x,initial_y") {
			position_vec_str = util.split(content_vec[i+1], ",");
			break;
		}
	}

	for (int i = 0; i < position_vec_str.size(); i++) {
		if (util.checkFloat(position_vec_str[i])) {
			int conversion = util.strToFloat(position_vec_str[i]);
			xy_pos.push_back(conversion);
		}
		else {
			continue;
		}
	}
	int x = xy_pos[0];
	int y = xy_pos[1];

	animation = loadAnimation(renderer, animation_path);

	player = Player(x, y, animation, user_actions);

	return player;
}

Ground FileHandling::loadGround(string level_config_path, vector<vector<SDL_Texture*>> texture_blocks,
	DiscreteDimensions discrete_dimensions) {

	/*
	NOTE:
		- This function returns an initialized Ground object with initial xy coordinates as well as discrete dimensions 
		read from the Level Configurations text file.

		- After parsing file contents at `level_config_path`, each line is split and assigned into the `content_vec`
		string vector.

		- `Content_vec` is iterated to search for the "# Ground format: Object,initial_x,initial_y,width_by_units,height_by_units" 
		element. Once found, the line below this line is split and assigned into the `format_vec_str` string vector.

		- Elements that contain initial xy coordinates in `format_vec_str` is converted to float. Results from the conversion is
		added into the format_vec vector with element[0] being the x value, [1] being the y value, [2] being width_by_units
		and [3] being height by units.

		- Player object is constructed with these values and returned.
	*/


	Ground ground;

	vector<int> format_vec;
	Utilities util;
	string file_content = parseTextFile(level_config_path);

	vector<string> format_vec_str;

	vector<string> content_vec = util.split(file_content, "\n");
	for (int i = 0; i < content_vec.size(); i++) {
		if (content_vec[i] == "# Ground format: Object,initial_x,initial_y,width_by_units,height_by_units") {
			format_vec_str = util.split(content_vec[i + 1], ",");
			break;
		}
	}

	for (int i = 0; i < format_vec_str.size(); i++) {
		if (util.checkFloat(format_vec_str[i])) {
			int conversion = util.strToFloat(format_vec_str[i]);
			format_vec.push_back(conversion);
		}
		else {
			continue;
		}
	}
	int x = format_vec[0];
	int y = format_vec[1];

	int width = format_vec[2];
	int height = format_vec[3];

	discrete_dimensions = { width, height };


	for (int i = 0; i < format_vec.size(); i++) {
		cout << format_vec[i] << endl;
	}


	ground = Ground(x, y, texture_blocks, discrete_dimensions);

	return ground;
}
