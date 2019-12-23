#include"sorts.h"

void insertionSort(int*& array, unsigned arraySize, clock_t& time) {

    clock_t tickStart = clock();

    for (unsigned i = 1; i < arraySize; ++i) {
        int currentElement = array[i];
        bool first = true;
        for (unsigned j = i; j > 0; --j) {
            if (currentElement >= array[j - 1]) {
                memmove(array + j + 1, array + j, (i - j) * sizeof(int));
                array[j] = currentElement;
                first = false;
                break;
            }
        }
        if (first) {
            memmove(array + 1, array, i * sizeof(int));
            array[0] = currentElement;
        }
    }

    time = clock() - tickStart;
}
