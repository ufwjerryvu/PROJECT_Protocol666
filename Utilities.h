/*
@ COLLABORATORS: An Luu
*/

#pragma once

#include "LIBDECLARATIONS.h"

class Utilities {
public:
	vector<string> split(string arg, string delimiter);
	bool checkFloat(string arg);
	string strToUpper(string arg);
	string strToLower(string arg);

};

vector<string> Utilities::split(string arg, string delimiter) {
	/*
	NOTE:
		- Declare variables for iteration
			+ `i` for iteration counter
			+ retvec for the vector to be returned
	*/


	vector<string> retvec;
	string temp = "";


	/*
	NOTE:
		- Iterate over `arg` string

		- Insert iterated characters into `temp`

		- If iterator encounters a character that equals to 1st character of delimiter, declare `test` string then insert
		subsequent chars to `test` string. (length of `test` = length of `delimiter`)
			+ Compare `test` to `delimiter`
			+ If they are the same, insert `temp` into `retvec` and the iterator will skip over the delimiter
			+ Else, continue to interate normally and populate temp
			
		- When encounter last character of `arg`, insert current temp into retvec

	*/

	for (int i = 0; i < arg.length();) {
		if (arg[i] == delimiter[0]) {
			string test = "";
			for (int j = 0, k = i; j < delimiter.length(); j++) {
				test += arg[k];
				k++;

			}

			if (test == delimiter) {
				retvec.push_back(temp);
				temp = "";
				i = i + delimiter.length();
			}
			else {
				temp += arg[i];
				i++;
			}
		}
		else {
			temp += arg[i];
			if (i == arg.length() - 1) {
				retvec.push_back(temp);
			}
			i++;
		}
	}
	return retvec;
}

bool Utilities::checkFloat(string arg) {
	/*
	NOTE:
		- If there's an empty string, return false.
	*/
	if (arg == "") {
		return false;
	}

	for (int i = 0; i < arg.length(); i++) {
	/*
	NOTE:
		- Iterate through the whole string. If character is a non-float character, 
		return false.
	*/
		if (arg[i] < '-' || arg[i] > '9' || arg[i] == '/') {
			return false;
		}
	/*
	NOTE:
		- Else, if the character is `.` or `-`, count to see of there are duplicates. 
		If there are, return false.
	*/

		else if (arg[i] == '-' || arg[i] == '.') {
			int dot_count = 0;
			int minus_count = 0;
			for (int j = 0; j < arg.length(); j++) {
				if (arg[j] == '.') {
					dot_count++;
				}
				if (arg[j] == '-') {
					minus_count++;
				}
				if (dot_count > 1 || minus_count > 1) {
					return false;
				}

			/*
			NOTE:
				- Else, if no numbers come after `.`, return false

				- Else, if there are numbers before `-`, return false
			*/
			}
			if (arg[i] == arg.back()) {
				return false;
			}
			if (arg[i] == '-' && arg[i] != arg.front()) {
				return false;
			}
		}
	}
	return true;

}

string Utilities::strToUpper(string arg) {
	/*
	NOTE:
		- Iterate `arg`, check for lower case characters, substract them by
		ASCII difference (32).
	*/
	const int ASCII_DIFFERENCE = 32;
	string temp = "";
	for (int i = 0; i < arg.length(); i++) {
		if (arg[i] >= 'a' && arg[i] <= 'z') {
			temp += arg[i] - ASCII_DIFFERENCE;
		}
		else {
			temp += arg[i];
		}
	}
	return temp;
}

string Utilities::strToLower(string arg) {
	/*
	NOTE:
		- Iterate `arg`, check for upper case characters, add them by
		ASCII difference (32).
	*/
	const int ASCII_DIFFERENCE = 32;
	string temp = "";
	for (int i = 0; i < arg.length(); i++) {
		if (arg[i] >= 'A' && arg[i] <= 'Z') {
			temp += arg[i] + ASCII_DIFFERENCE;
		}
		else {
			temp += arg[i];
		}
	}
	return temp;
}
