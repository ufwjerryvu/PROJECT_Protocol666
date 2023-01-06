/*
@ COLLABORATORS: An Luu
*/

#pragma once

#include "LIBDECLARATIONS.h"

vector<string> split(string arg, string delimiter) {
	/*
	NOTE:
		- Declare variables for iteration
			+ `temp` to insert interated characters in to form a string
			+ `i` for iteration counter
			+ retvec for the vector to be returned
	*/

	string temp = "";
	int i = 0;
	vector<string> retvec;

	/*
	NOTE:
		- Iterate over `arg` string

		- Insert iterated characters into `temp`

		- When encounter 1st character of delimiter, insert `temp` into retvec,
		skip i over delimiter length. Delimiter is resetted.

		- When encounter last character of `arg`, insert current temp into retvec
	*/
	while (i < arg.length()) {
		if (arg[i] == delimiter[0]) {
			retvec.push_back(temp);
			temp = "";
			i = i + delimiter.length();
			continue;
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
