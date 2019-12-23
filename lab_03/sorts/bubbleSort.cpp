#include "sorts.h"


void bubbleSort(int *& array, unsigned size, clock_t& time) {

    clock_t tickStart = clock();
    bool swapped = true;
    unsigned iMaxPos = size - 1;
    unsigned jMaxPos = size - 1;
    for (unsigned i = 0; i < iMaxPos && swapped == true; ++i, --jMaxPos) {
        swapped = false;
        for (unsigned j = 0; j < jMaxPos; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
    }
    time = clock() - tickStart;
}
