/*
@ COLLABORATORS: Kenny Nguyen
@ CLASS DESIGNERS: Kenny Nguyen
*/
#pragma once

class ExceptionHandling {
public:
	/*
	SECTION 0: GAME'S BOUNRDARY ATTRIBUTES
	*/

	/*
	NOTE:
		- The following attributes, level_width, level_height are
		used to check with the game's boundaries

		- The attribute current_level is needed to use
		FileHandling.h parseLevelWidth() and parseLevelHeight()

	*/
	int level_width;
	int level_height;
	int current_level = 0;

	/*
	SECTION 1: CONSTRUCTORS AND DESTRUCTORS
	*/
	ExceptionHandling();

	/*
	SECTION 2: METHODS TO CHECK FOR EXCEPTIONS
	*/
	bool checkXCoordinate(int x);
	bool checkYCoordinate(int y);

	bool checkInBoundX(int x, int width);
	bool checkInBoundY(int y, int height);
};

ExceptionHandling::ExceptionHandling() {
	/*
	NOTE:
		- Default constructor initializes the level_width and 
		level_height to be compared with other attributes relating 
		to positions/coordinates
	*/

	FileHandling file_io;
	vector<string> level_config_paths = file_io.parseLevelConfigPaths();

	this->level_width = file_io.parseLevelWidth(level_config_paths[this->current_level]);
	this->level_height = file_io.parseLevelHeight(level_config_paths[this->current_level]);
}

bool ExceptionHandling::checkXCoordinate(int x) {
	/*
	NOTE:
		- Returns boolean as the result whether the exception 
		check validates the X-Coordinate. This goes for every
		other exception check.

		- ALL methods under this class has the same boolean 
		return methodology
	*/

	bool valid = true;

	try {
	/*
	NOTE:
		- Given two cases, try tests both to identify which 
		boundary the x-coordinate exceeds (assuming the 
		game level has no negative coordinates)
	*/ 

		if (x >= this->level_width) {
			valid = false;
			throw 1;
		}
		else if (x <= 0) {
			valid = false;
			throw 2;
		}
	}

	catch (int exception) {
	/* 
	NOTE: 
		- Depending on the exception, a message is called to 
		console to display what is the error.

		- This error display method is applied for ALL methods 
		under this class.
	*/

		switch (exception) {
		case 1:
			cerr << "OutOfBounds: The x_coordinate of an object " << x << " is outside the level's width " << this->level_width;

		case 2:
			cerr << "OutOfBounds: The x_coordinate of an object " << x << " is outside the level's width " << 0;
		}
	}

	return valid;
}

bool ExceptionHandling::checkYCoordinate(int y) {
	bool valid = true;

	/*
	NOTE:
		- Given two cases, try tests both to identify which 
		boundary the y-coordinate exceeds (assuming the game 
		level has no negative coordinates)
	*/

	try {
		if (y >= this->level_height) {
			valid = false;
			throw 1;
		}
		else if (y <= 0) {
			valid = false;
			throw 2;
		}
	}

	catch (int exception) {
		switch (exception) {
		case 1:
			cerr << "OutOfBounds: The y_coordinate of an object " << y << " is outside the level's height " << this->level_height;

		case 2:
			cerr << "OutOfBounds: The y_coordinate of an object " << y << " is outside the level's height " << 0;
		}
	}

	return valid;
}

bool ExceptionHandling::checkInBoundX(int x, int width) {
	bool valid = true;

	try {
	/*
	NOTE:
		- Given two cases, 'try' tests both to identify which boundary
		the Texture's x-related coordinates (x-coordinate + width) 
		exceeds (assuming the game level has no negative coordinates)
	*/

		if (x + width >= this->level_width) {
			valid = false;
			throw x;
		}
		else if (x <= 0) {
			valid = false;
			throw x;
		}
	}

	catch (int exception) {
		switch (exception) {
		case 1:
			cerr << "OutOfBounds: The object has the x_coordinate " << x << " and width of " << width << " is outside the level's width " << this->level_width;

		case 2:
			cerr << "OutOfBounds: The object has the x_coordinate " << x << " and width of " << width << " is outside the level's width " << 0;
		}
	}

	return valid;
}

bool ExceptionHandling::checkInBoundY(int y, int height) {
	bool valid = true;

	try {
	/*
	NOTE:
		- Given two cases, 'try' tests both to identify which boundary
		the Texture's y-related coordinates (y-coordinate + height)
		exceeds (assuming the game level has no negative coordinates)
	*/

		if (y + height >= this->level_height) {
			valid = false;
			throw y;
		}
		else if (y <= 0) {
			valid = false;
			throw y;
		}
	}

	catch (int exception) {
		switch (exception) {
		case 1:
			cerr << "OutOfBounds: The object has the x_coordinate " << y << " and height of " << height << " is outside the level's height " << this->level_height;

		case 2:
			cerr << "OutOfBounds: The object has the x_coordinate " << y << " and height of " << height << " is outside the level's height " << 0;
		}
	}

	return valid;
}