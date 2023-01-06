/*
@ COLLABORATORS: An Luu
*/

#pragma once

#include "LIBDECLARATIONS.h"

class Utilities {
	public:
	vector<string> split(string arg, string delimiter);
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

