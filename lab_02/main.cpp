#include <iostream>
#include <exception>
#include <ctime>
#include <random>
#include <stdint.h>
#include "Matrix.h"


int main(){

	unsigned size = 500;
	unsigned topRandom = 1000;

	Matrix original(topRandom, size, size);
	Matrix mult(topRandom, size, size);

	std::clock_t timeClassic = 0;
	std::clock_t timeClassicBuffer = 0;
	std::clock_t timeVinograd = 0;
	std::clock_t timeVinogradImpr = 0;

	unsigned numberOfTests = 10;
	std::clock_t buffer = 0;

	std::cout << "Counting classic...";
	for (unsigned i = 0; i < numberOfTests; ++i) {
		original.classicMult(mult, buffer);
		timeClassic += buffer;
	}
	std::cout << "  finished in " << timeClassic << " ticks!" << std::endl;

	std::cout << "Counting classic+buffer...";
	for (unsigned i = 0; i < numberOfTests; ++i) {
		original.classicBufferMult(mult, buffer);
		timeClassicBuffer += buffer;
	}

	std::cout << "  finished in " << timeClassicBuffer << " ticks!" << std::endl;

	std::cout << "Counting Vinograd...";
	for (unsigned i = 0; i < numberOfTests; ++i) {
		original.vinogradMult(mult, buffer);
		timeVinograd += buffer;
	}
	std::cout << "  finished in " << timeVinograd << " ticks!" << std::endl;


	std::cout << "Counting improved Vinograd...";
	for (unsigned i = 0; i < numberOfTests; ++i) {
		original.vinogradImprMult(mult, buffer);
		timeVinogradImpr += buffer;
	}
	std::cout << "  finished in " << timeVinogradImpr << " ticks!" << std::endl;

	if (timeClassicBuffer < timeVinograd) {
		std::cout << "ClassicBuffer win Vinograd by " << (timeVinograd - timeClassicBuffer) * 100 / timeVinograd << "%" << std::endl;
	}
	else {
		std::cout << "Vinograd win ClassicBuffer by " << (timeClassicBuffer - timeVinograd) * 100 / timeClassicBuffer << "%" << std::endl;
	}

	if (timeClassic < timeVinograd) {
		std::cout << "Classic win by " << (timeVinograd - timeClassic) * 100 / timeVinograd << "%" << std::endl;
	}
	else {
		std::cout << "Vinograd win by " << (timeClassic - timeVinograd) * 100 / timeClassic << "%" << std::endl;
	}

	if (timeVinograd < timeVinogradImpr) {
		std::cout << "Classic Vinograd win by " << (timeVinogradImpr - timeVinograd) * 100 / timeVinogradImpr << "%" << std::endl;
	}
	else {
		std::cout << "Improved Vinograd win by " << (timeVinograd - timeVinogradImpr) * 100 / timeVinograd << "%" << std::endl;
	}

	if (size < 10) {

		original.outStream();
		mult.outStream();

	}

	return 0;

}
