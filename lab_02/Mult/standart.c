#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Умножение матрицы
int** multiMatrixStd(ivMatrix M1, ivMatrix M2)
{
    if (M1.m != M2.n)
    {
        printf("Неподходящие размеры. %d != %d", M1.m, M2.n);
        return (int**)NULL;
    }
 
    // Исходные размеры будут [n1, m2]
    int n = M1.n, m = M2.m;
 
    int **result = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
    {
        result[i] = (int*)malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++)
        {
            result[i][j] = 0;
        }
    }
 
    for (int i = 0; i < M1.n; i++)
    {
        for (int j = 0; j < M2.m; j++)
        {
            for (int k = 0; k < M1.m; k++)
            {
                result[i][j] = result[i][j] + M1.matrix[i][k]*M2.matrix[k][j];
            }
        }
    }
 
    return result;
}