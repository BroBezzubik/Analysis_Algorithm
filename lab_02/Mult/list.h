#pragma once

#ifndef LIST_FUNC
#define LIST_FUNC

#define MATRIX_SIZE 2

typedef struct
{
    int m, n;
    int **matrix;//[MATRIX_SIZE][MATRIX_SIZE];
} ivMatrix;

int **multiMatrixStd(ivMatrix M1, ivMatrix M2);
int **multiMatrixVin(ivMatrix M1, ivMatrix M2);
int **multiMatrixVin2(ivMatrix M1, ivMatrix M2);

#endif
