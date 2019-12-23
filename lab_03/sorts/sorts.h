#ifndef SORTS_H
#define SORTS_H

#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdint.h>


void bubbleSort(int*& array, unsigned size, clock_t& time);
void insertionSort(int*& array, unsigned arraySize, clock_t& time);
void selectionSort(int*& array, unsigned arraySize, clock_t& time);



#endif // SORTS_H
