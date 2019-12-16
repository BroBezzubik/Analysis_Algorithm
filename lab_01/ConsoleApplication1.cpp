#pragma warning(suppress : 4996)
#include <iostream>
#include "Levenstain3.h"
#include "Levenstain4.h"
#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <chrono>


using namespace std;


int test( int (*f)(char*, char*), char* str1, char* str2, int count) {

	int lev = 0;
	for (int i = 0; i < count; i++) { lev = f(str1, str2); }
	return lev;

}


void gen_random(char* s, const int len) {

	static const char alphanum[] =
		"0123456789"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i) {
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	s[len] = 0;

}


void case1(void) {

	char str1[30];
	cout << "Str1: ";
	cin >> str1;

	char str2[30];
	cout << "Str2: ";
	cin >> str2;

	auto start = chrono::high_resolution_clock::now();
	int lev1 = test(levenstain3, str1, str2, 100);
	cout << clock();
	auto end = chrono::high_resolution_clock::now();
	cout << clock();
	chrono::duration<double> diff = end - start;
	
	cout << "### LEV ###" << endl
		<< str1 << endl
		<< str2 << endl
		<< "Lev: " << lev1 << endl
		<< "Time: " << diff.count() << endl << endl;

	start = chrono::high_resolution_clock::now();
	cout << clock();
	int lev2 = test(levenstainRec3, str1, str2, 100);
	cout << clock();
	end = chrono::high_resolution_clock::now();
	diff = end - start;
	
	cout << "### LEV REC ###" << endl
		<< str1 << endl
		<< str2 << endl
		<< "Lev: " << lev2 << endl
		<< "Time: " << diff.count() << endl << endl;

	start = chrono::high_resolution_clock::now();
	int lev3 = test(levenstain4, str1, str2, 1);
	end = chrono::high_resolution_clock::now();
	diff = end - start;
	
	cout << "### LEV MOD ###" << endl
		<< str1 << endl
		<< str2 << endl
		<< "Lev: " << lev3 << endl
		<< "Time: " << diff.count() << endl << endl;

}


void case2(void) {
	char str1[1001];
	char str2[1001];

	gen_random(str1, 1000);
	gen_random(str2, 1000);

	int count = 100;

	auto start = chrono::high_resolution_clock::now();
	int lev1 = test(levenstain3, str1, str2, count);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = (end - start) / count;
	
	cout << "### LEV ###" << endl
		<< str1 << endl
		<< str2 << endl
		<< "Lev: " << lev1 << endl
		<< "Time: " << diff.count() << endl << endl;

	//start = chrono::high_resolution_clock::now();
	//int lev2 = test(levenstainRec3, str1, str2, count);
	//end = chrono::high_resolution_clock::now();
	//diff = (end - start) / count;
	
	//cout << "### LEV REC ###" << endl
	//	<< str1 << endl
	//	<< str2 << endl
	//	<< "Lev: " << lev2 << endl
	//	<< "Time: " << diff.count() << endl << endl;

	start = chrono::high_resolution_clock::now();
	int lev3 = test(levenstain4, str1, str2, count);
	end = chrono::high_resolution_clock::now();
	diff = (end - start) / count;
	
	cout << "### LEV MOD ###" << endl
		<< str1 << endl
		<< str2 << endl
		<< "Lev: " << lev3 << endl
		<< "Time: " << diff.count() << endl << endl;
}


int main()
{
	int key = 0;
	cout << "1 - User input" << endl
		<< "2 - Random" << endl;

	cout << "Selecet opetation: ";
	cin >> key; 

	switch (key)
	{
	case 1:
		case1();
		break;
	case 2:
		case2();
		break;
	default:
		break;
	}

}