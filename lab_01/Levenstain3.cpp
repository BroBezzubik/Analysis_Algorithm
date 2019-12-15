#include "Levenstain3.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int levenstain3(char* str1, char* str2) {

	if (strcmp(str1, str2) == 0) {
		return 0;
	}

	if (strlen(str1) == 0) {
		return strlen(str2);
	}

	if (strlen(str2) == 0) {
		return strlen(str1);
	}

	unsigned columns = strlen(str1) + 1;
	unsigned rows = strlen(str2) + 1;

	int* storage[2];
	storage[0] = new int[rows];
	storage[1] = new int[rows];

	for (unsigned i = 0; i < rows; i++) {
		storage[0][i] = i;
	}

	for (unsigned i = 1; i < columns; i++) {
		storage[1][0] = storage[0][0] + 1;
		for (unsigned j = 1; j < rows; j++) {
			bool symbNotSame = false;
			if (str1[i - 1] != str2[j - 1]) {
				symbNotSame = true;
			}

			storage[1][j] = min(min(
								storage[0][j] + 1, storage[1][j - 1] + 1), 
								storage[0][j - 1] + symbNotSame);
		}
		swap(storage[0], storage[1]);
	}
	
	int result = storage[0][rows - 1];
	
	delete storage[0];
	delete storage[1];

	return result;
}


int levenstainRec3(char* str1, char* str2) {

	if (strcmp(str1, str2) == 0) {
		return 0;
	}

	if (strlen(str1) == 0) {
		return strlen(str2);
	}

	if (strlen(str2) == 0) {
		return strlen(str1);
	}


	bool symbNotSame = false;
	if (*str1 != *str2) {
		symbNotSame = true;
	}

	int result = min(min(levenstainRec3(str1 + 1, str2) + 1, levenstainRec3(str1, str2 + 1) + 1), 
					levenstainRec3(str1 + 1, str2 + 1) + symbNotSame);

	return result;
}