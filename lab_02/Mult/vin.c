#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int **multiMatrixVin(ivMatrix M1, ivMatrix M2)
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
    }
    int d = M1.m/2;               // 1
    // I Сумма в строках
    int rowFactor[M1.n];
    for (int i = 0; i < M1.n; i++)    // n1*(10*d+9+2)+2 = n1*(10*d+11)+2 = 10*d*n1 + 11*n1 + 2
    {                                        // (10*d+9 + 2)
        rowFactor[i] = M1.matrix[i][0]*M1.matrix[i][1];   // 1 + 1 + 2 + 1 + 2 = 7
        for (int j = 1; j < d; j++)         // [d * (8 + 2) + 2]    = 10*d +2
        {
            rowFactor[i] = rowFactor[i] + M1.matrix[i][2*j+1] * M1.matrix[i][2*j];    //1+1+1+2+1+2 = 8
        }
    }
 
    // II Сумма столбцов
    int columnFactor[M2.m];
    for (int i = 0; i < M2.m; i++)
    {
        columnFactor[i] = M2.matrix[0][i]*M2.matrix[1][i];
        for (int j = 1; j < d; j++)
        {
            columnFactor[i] = columnFactor[i] + M2.matrix[2*j+1][i] * M2.matrix[2*j][i];
        }
    }
 
    // III Вычисление R
    for (int i = 0; i < M1.n; i++)
    {
        for (int j = 0; j < M2.m; j++)
        {
            result[i][j] = -rowFactor[i] - columnFactor[j];
            for (int k = 0; k < d; k++)
            {
                result[i][j] = result[i][j] + (M1.matrix[i][2*k] + M2.matrix[2*k+1][j])*(M1.matrix[i][2*k+1] + M2.matrix[2*k][j]);
            }
        }
    }
 
    // IV Добавление членов в случае нечетной общей размерности
    if (M1.m % 2)
    {
        for (int i = 0; i < M1.n; i++)
        {
            for (int j = 0; j < M2.m; j++)
            {
                result[i][j] = result[i][j] + M1.matrix[i][M1.m-1]*M2.matrix[M2.n-1][j];
            }
        }
    }
 
    return result;
}