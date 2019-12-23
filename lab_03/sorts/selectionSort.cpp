
#include<sorts.h>

void selectionSort(int*& array, unsigned arraySize, clock_t& time) {

    clock_t tickStart = clock();

    unsigned maxI = arraySize - 1;
    for (unsigned i = 0; i < maxI; ++i) {
        unsigned minIndex = i;
        for (unsigned j = i + 1; j < arraySize; ++j) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(array[i], array[minIndex]);
    }

    time = clock() - tickStart;
}
