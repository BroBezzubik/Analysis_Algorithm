
#include<sorts.h>


void printArray(int* array, unsigned size) {
	for (unsigned i = 0; i < size; ++i) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void fillArray(int*& array, unsigned arraySize, int key = 0) {
	if (key == -1) {
        int element = static_cast<int>(arraySize);
		for (unsigned i = 0; i < arraySize; ++i, --element) {
			array[i] = element;
		}
	}
	else if (key == 1) {
		for (unsigned i = 0; i < arraySize; ++i) {
            array[i] = static_cast<int>(i);
		}
	}
	else {
        for (unsigned i = 0; i < arraySize; ++i){
            array[i] = rand() % static_cast<int>(arraySize);
		}
	}
}

int* makeArray(unsigned arraySize, int key = 0) {
	int* array = new int[arraySize];
	fillArray(array, arraySize, key);
	return array;
}


void testAlgorithm(unsigned arraySize, void (*func)(int*&, unsigned, clock_t&), unsigned numberOfTests = 10) {

	clock_t sortTimeBest = 0;
	clock_t sortTimeWorst = 0;
	clock_t sortTimeRandom = 0;

	int* arrayBest = makeArray(arraySize, 1);
	int* arrayWorst = makeArray(arraySize, -1);
	int* arrayRandom = makeArray(arraySize);

	clock_t bufferTime;
	for (unsigned i = 0; i < numberOfTests; ++i){
		func(arrayBest, arraySize, bufferTime);
		sortTimeBest += bufferTime;
		func(arrayWorst, arraySize, bufferTime);
		sortTimeWorst += bufferTime;
		func(arrayRandom, arraySize, bufferTime);
		sortTimeRandom += bufferTime;

		fillArray(arrayBest, arraySize, 1);
		fillArray(arrayWorst, arraySize, -1);
		fillArray(arrayRandom, arraySize, 0);
	}

	std::cout << "BEST:   " << sortTimeBest << std::endl;
	std::cout << "WORST:  " << sortTimeWorst << std::endl;
	std::cout << "RANDOM: " << sortTimeRandom << std::endl;

	delete[] arrayBest;
	delete[] arrayWorst;
	delete[] arrayRandom;
}

int main()
{
    int key = 0;
    switch (key) {
    case 0:{

        clock_t tmp;
        int *arr1 = new int[5]{1, 3, 5, 3, 5};
        int *arr2 = new int[5]{1, 3, 5, 3, 5};
        int *arr3 = new int[5]{1, 3, 5, 3, 5};

        bubbleSort(arr1, 5, tmp);
        insertionSort(arr2, 5, tmp);
        selectionSort(arr3, 5, tmp);

        for (int i = 0; i < 5; i++){ std::cout << arr1[i]; }
        std::cout << std::endl;
        for (int i = 0; i < 5; i++){ std::cout << arr2[i]; }
        std::cout << std::endl;
        for (int i = 0; i < 5; i++){ std::cout << arr3[i]; }
        std::cout << std::endl;

        break;
    }
    case 1: {
        unsigned numberOfTests = 100;
        std::vector<unsigned> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
        for (unsigned arraySize : sizes) {
            std::cout << "\narraySize: " << arraySize << std::endl;

            std::cout << "Selection sort:" << std::endl;
            testAlgorithm(arraySize, selectionSort, numberOfTests);

            std::cout << "\nInsertion sort:" << std::endl;
            testAlgorithm(arraySize, insertionSort, numberOfTests);

            std::cout << "\nBubble sort:" << std::endl;
            testAlgorithm(arraySize, bubbleSort, numberOfTests);

        }
        break;
    }
    }

	return 0;
}
