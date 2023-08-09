/*
@ COLLABORATORS: Jerry Vu, An Luu
@ CLASS DESIGNERS: Jerry Vu, An Luu
*/

#pragma once

#include "LIBDECLARATIONS.h"

#include "Utilities.h"
#include "FileHandling.h"

#include "Sprite.h"

#include "Projectile.h"
#include "LaserBeam.h"
#include "FiftyCalibre.h"

#include "Character.h"
#include "Enemy.h"
#include "MeleeGoon.h"
#include "RangeGoon.h"
#include "Player.h"

#include "Terrain.h"
#include "Ground.h"
#include "Platform.h"
#include "SinglePlatform.h"
#include "MultiplePlatform.h"

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
	vector<string> parseFileForLoadingPaths(string file_path);
	Animation loadAnimation(SDL_Renderer* renderer, string file_for_animation_paths);
	vector<vector<SDL_Texture*>> loadSetupTextures(SDL_Renderer* renderer, string file_for_assembly_paths);

	/*
	SECTION 4: ASSETS LOADING
	*/
	vector<string> getLinesFromFlag(string content, string flag);
	string getFirstLineFromFlag(string content, string flag);

	Player loadPlayer(SDL_Renderer* renderer, string level_config_path, UserEvent user_actions, string chosen_type);
	vector<Ground> loadGrounds(SDL_Renderer* renderer, string level_config_path);
	vector<SinglePlatform> loadSinglePlatforms(SDL_Renderer* renderer, string level_config_path);
	vector<MultiplePlatform> loadMultiplePlatforms(SDL_Renderer* renderer, string level_config_path);
	vector<Platform> loadPlatforms(SDL_Renderer* renderer, string level_config_path);
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
vector<string> FileHandling::parseFileForLoadingPaths(string file_path) {
	vector<string> path_vec;
	Utilities util;
	string file_content = parseTextFile(file_path);

	vector<string> split_content = util.split(file_content, "\n");

	/*
	NOTE:
		- What this function basically does is 
		ignore all the comments and all the empty lines.
		This is similar to parseTextFile() except it returns
		a cleaner vector of strings.
	*/
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
	vector<string> anim_paths_vec = parseFileForLoadingPaths(file_for_animation_paths);
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
			|| anim_paths_vec[i] == "<jumping>" || anim_paths_vec[i] == "<falling>"
			|| anim_paths_vec[i] == "<shooting_idle>" || anim_paths_vec[i] == "<shooting_running>"
			|| anim_paths_vec[i] == "<shooting_jumping>" || anim_paths_vec[i] == "<shooting_falling>") {
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
		if (current_flag == "<shooting_idle>" && anim_paths_vec[i] != current_flag && anim_paths_vec[i] != "</shooting_idle>") {
			animation.frames_shooting_idle.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (current_flag == "<shooting_running>" && anim_paths_vec[i] != current_flag && anim_paths_vec[i] != "</shooting_running>") {
			animation.frames_shooting_running.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (current_flag == "<shooting_jumping>" && anim_paths_vec[i] != current_flag && anim_paths_vec[i] != "</shooting_jumping>") {
			animation.frames_shooting_jumping.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
		if (current_flag == "<shooting_falling>" && anim_paths_vec[i] != current_flag && anim_paths_vec[i] != "</shooting_falling>") {
			animation.frames_shooting_falling.push_back(loadTexture(renderer, anim_paths_vec[i]));
		}
	}

	return animation;
}

vector<vector<SDL_Texture*>> FileHandling::loadSetupTextures(SDL_Renderer* renderer, string file_for_assembly_paths) {
	/*
	NOTE:
		- This function loads in the texture setup blocks
		for Terrain objects.
	*/
	vector<vector<SDL_Texture*>> ret_vec;
	vector<SDL_Texture*> row;
	vector<string> assembly_anim_paths = parseFileForLoadingPaths(file_for_assembly_paths);

	bool load_flag = false;

	for (int index = 0; index < assembly_anim_paths.size(); index++) {
		if (assembly_anim_paths[index] == "<row>") {
			load_flag = true;
			continue;
		}
		if (assembly_anim_paths[index] == "</row>") {
			/*
			NOTE:
				- With every flag that ends a row, 
				we push back the return vector and 
				then we clear the row for the next
				set of iterations.
			*/
			load_flag = false;
			ret_vec.push_back(row);
			row.clear();
			continue;
		}
		if (load_flag) {
			row.push_back(this->loadTexture(renderer, assembly_anim_paths[index]));
		}
	}

	return ret_vec;
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

	ret_obj.loadLaserBeamTexture(this->loadTexture(renderer, "Assets/Sprite/Projectile/LaserBeam/test.png"));

	return ret_obj;
}

vector<Ground> FileHandling::loadGrounds(SDL_Renderer* renderer, string level_config_path) {
	Utilities util;
	/*
	NOTE:
		- We get the config lines that contain the flag 'Ground'.

		- The texture setup blocks are also loaded in using the
		assembly loading method defined earlier.
	*/
	vector<string> lines = getLinesFromFlag(this->parseTextFile(level_config_path), "Ground");
	vector<vector<SDL_Texture*>> texture_setup_blocks = this->loadSetupTextures(renderer, "Configurations/Assembly/Ground.txt");
	vector<Ground> ret_vec;

	/*
	NOTE:
		- Now, we're iterating through the config lines.
	*/
	for (int index = 0; index < lines.size(); index++) {
		vector<string> current_line_split = util.split(lines[index], ",");
		
		const int NUMBER_OF_ARGUMENTS = 5;
		/*
		NOTE:
			- If the formatting in the text file is invalid then the 
			function gives an error message.
		*/
		if (current_line_split.size() != NUMBER_OF_ARGUMENTS) {
			cerr << "Error from FileHandling::loadGrounds(): invalid formatting in the config file." << endl;
			return ret_vec;
		}

		/*
		NOTE:
			- Converting all the string objects being read from
			the file into floating points first and storing
			them into integer variables.
		*/
		int initial_x = util.strToFloat(current_line_split[1]);
		int initial_y = util.strToFloat(current_line_split[2]);
		int width_by_units = util.strToFloat(current_line_split[3]);
		int height_by_units = util.strToFloat(current_line_split[4]);

		/*
		NOTE:
			- Instantiating Ground objects normally and adding 
			the instance to the vector of Ground objects.
		*/
		Ground temp(initial_x, initial_y, texture_setup_blocks, 
			DiscreteDimensions{ width_by_units, height_by_units});

		ret_vec.push_back(temp);
	}

	return ret_vec;
}

vector<SinglePlatform> FileHandling::loadSinglePlatforms(SDL_Renderer* renderer, string level_config_path) {
	Utilities util;

	/*
	NOTE:
		- Single platforms and half-single platforms are the same type 
		of platform with the very same behaviors. They just have different
		textures.

		- In the level config file, full-height extendable single platforms
		are flagged by 'FullSinglePlatform' and half-height extendable single
		platforms are flagged by 'HalfSinglePlatform'.
	*/
	vector<string> lines_single_platform = getLinesFromFlag(this->parseTextFile(level_config_path), "FullSinglePlatform");
	vector<string> lines_halfsingle_platform = getLinesFromFlag(this->parseTextFile(level_config_path), "HalfSinglePlatform");

	vector<vector<SDL_Texture*>> texture_setup_blocks_sp = 
		this->loadSetupTextures(renderer, "Configurations/Assembly/FullSinglePlatform.txt");
	vector<vector<SDL_Texture*>> texture_setup_blocks_hsp =
		this->loadSetupTextures(renderer, "Configurations/Assembly/HalfSinglePlatform.txt");

	/*
	NOTE:
		- This is the vector that will store all the single platform 
		objects.
	*/
	vector<SinglePlatform> ret_vec;

	/*
	NOTE:
		- This loop is for full-height extendable platforms.
	*/
	for (int index = 0; index < lines_single_platform.size(); index++) {
		vector<string> current_line_split = util.split(lines_single_platform[index], ",");

		const int NUMBER_OF_ARGUMENTS = 4;
		/*
		NOTE:
			- If the level config line has an invalid format
			then we print out an error message. It should have
			at least 4 arguments.
		*/
		if (current_line_split.size() != NUMBER_OF_ARGUMENTS) {
			cerr << "Error from FileHandling::loadSinglePlatforms(): invalid formatting in the config file." << endl;
			return ret_vec;
		}

		int width_by_units = util.strToFloat(current_line_split[3]);
		int height_by_units = 1;

		/*
		NOTE:
			- Notice that `temp` takes in `texture_setup_blocks_sp` and not
			`texture_setup_blocks_hsp`.
		*/
		SinglePlatform temp(util.strToFloat(current_line_split[1]), util.strToFloat(current_line_split[2]), texture_setup_blocks_sp,
			DiscreteDimensions{ width_by_units, height_by_units });

		ret_vec.push_back(temp);
	}

	/*
	NOTE:
		- This loop is to instantiate half-height extendable platforms
		from the level config file.
	*/
	for (int index = 0; index < lines_halfsingle_platform.size(); index++) {
		vector<string> current_line_split = util.split(lines_halfsingle_platform[index], ",");

		const int NUMBER_OF_ARGUMENTS = 4;
		/*
		NOTE:
			- Again, we're checking for the validity of the config file's
			formatting.
		*/
		if (current_line_split.size() != NUMBER_OF_ARGUMENTS) {
			cerr << "Error from FileHandling::loadSinglePlatforms(): invalid formatting in the config file." << endl;
			return ret_vec;
		}

		int width_by_units = util.strToFloat(current_line_split[3]);
		int height_by_units = 1;

		/*
		NOTE:
			- Notice that `temp` takes in `texture_setup_blocks_hsp` and not
			`texture_setup_blocks_sp`.
		*/
		SinglePlatform temp(util.strToFloat(current_line_split[1]), util.strToFloat(current_line_split[2]), texture_setup_blocks_hsp,
			DiscreteDimensions{ width_by_units, height_by_units });

		ret_vec.push_back(temp);
	}

	return ret_vec;
}

vector<MultiplePlatform> FileHandling::loadMultiplePlatforms(SDL_Renderer* renderer, string level_config_path) {
	Utilities util;

	/*
	NOTE:
		- MultiplePlatform objects are kind of similar to Ground objects.
		It only takes in 3x3 two-dimensional texture vectors.
	*/
	vector<string> lines_mult_platform = getLinesFromFlag(this->parseTextFile(level_config_path), "MultiplePlatform");

	vector<vector<SDL_Texture*>> texture_setup_blocks =
		this->loadSetupTextures(renderer, "Configurations/Assembly/MultiplePlatform.txt");

	/*
	NOTE:
		- This is the vector that will store all the MultiplePlatform
		objects.
	*/
	vector<MultiplePlatform> ret_vec;

	for (int index = 0; index < lines_mult_platform.size(); index++) {
		vector<string> current_line_split = util.split(lines_mult_platform[index], ",");

		const int NUMBER_OF_ARGUMENTS = 5;
		/*
		NOTE:
			- If the level config line has an invalid format
			then we print out an error message. It should have
			at least 6 arguments.
		*/
		if (current_line_split.size() != NUMBER_OF_ARGUMENTS) {
			cerr << "Error from FileHandling::loadMultiplePlatforms(): invalid formatting in the config file." << endl;
			return ret_vec;
		}

		int initial_x = util.strToFloat(current_line_split[1]);
		int initial_y = util.strToFloat(current_line_split[2]);
		int width_by_units = util.strToFloat(current_line_split[3]);
		int height_by_units = util.strToFloat(current_line_split[4]);

		/*
		NOTE:
			- Notice that `temp` takes in `texture_setup_blocks_sp` and not
			`texture_setup_blocks_hsp`.
		*/
		MultiplePlatform temp(initial_x, initial_y, texture_setup_blocks,
			DiscreteDimensions{ width_by_units, height_by_units });

		ret_vec.push_back(temp);
	}

	return ret_vec;
}

vector<Platform> FileHandling::loadPlatforms(SDL_Renderer* renderer, string level_config_path) {
	vector<Platform> ret_vec;

	vector<SinglePlatform> splat_vec = this->loadSinglePlatforms(renderer, level_config_path);
	vector<MultiplePlatform> mplat_vec = this->loadMultiplePlatforms(renderer, level_config_path);

	/*
	NOTE:
		- Storing all SinglePlatform objects into one Platform 
		vector.
	*/
	for (int index = 0; index < splat_vec.size(); index++) {
		ret_vec.push_back(splat_vec[index]);
	}

	/*
	NOTE:
		- Storing all MultiplePlatform objects into one Platform
		vector.
	*/
	for (int index = 0; index < mplat_vec.size(); index++) {
		ret_vec.push_back(mplat_vec[index]);
	}

	return ret_vec;
}