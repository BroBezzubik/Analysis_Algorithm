#include "Levenstain4.h"
#include "Levenstain3.h"
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace std;

int levenstain4(char* str1, char* str2) {

	unsigned lenstr1 = strlen(str1);
	unsigned lenstr2 = strlen(str2);
	
	if (lenstr1 < 2 || lenstr2 < 2)
		return levenstain3(str1, str2);
	
	unsigned columns = lenstr1 + 1;
	unsigned rows = lenstr2 + 1;

	int* storage[3];
	for (int i = 0; i < 3; i++)
		storage[i] = new int[rows];

	for (unsigned i = 0; i < rows; i++) {
		storage[0][i] = i;
	}

	storage[1][0] = 1;
	for (unsigned i = 1; i < rows; i++) {
		bool sumbNotSame = false;
		if (str1[i - 1] != str2[0]) {
			sumbNotSame = true;
		}
		storage[1][i] = min(min(storage[1][i - 1] + 1, storage[0][i] + 1), storage[0][i - 1] + sumbNotSame);
	}

	for (unsigned i = 2; i < columns; i++) {
		storage[2][0] = storage[1][0] + 1;
		bool symbNotSame = false;

		if (str1[1] != str2[i - 1]) {
			symbNotSame = true;
		}

		storage[2][1] = min(min(storage[2][0] + 1, storage[1][1] + 1), storage[1][0] + symbNotSame);
		
		for (unsigned j = 2; j < rows; j++) {
			symbNotSame = false;
			if (str2[j - 1] != str1[i - 1]) {
				symbNotSame = true;
			}

			int tmp;

			if (str1[i - 1] == str2[i] && str1[i] == str2[i - 1]) {
				tmp = min(min(
					storage[1][j] + 1, storage[2][j - 1] + 1),
					storage[1][j - 1] + symbNotSame);

			} else {
				tmp = min(min(min(
					storage[1][j] + 1, storage[2][j - 1] + 1),
					storage[1][j - 1] + symbNotSame),
					storage[0][j - 2] + 1);
			}

			storage[2][j] = tmp;
		}
		
		swap(storage[0], storage[1]);
		swap(storage[1], storage[2]);
	}
	
	int result = storage[1][rows - 1];
	
	delete storage[0];
	delete storage[1];
	delete storage[2];

	return result;
}