#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int **multiMatrixVin2(ivMatrix M1,  ivMatrix M2)
{
    /*  Оптимизация
     *  1) Замена  на +=
     *  2) Убираем умножение в индексах (j += 2)
     *  3) Снова меняем += для R
    */
 
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
 
    int m_1 = M1.m-1;
    // I Сумма в строках
    int rowFactor[M1.n];
    for (int i = 0; i < M1.n; i++)
    {
        rowFactor[i] = 0;
        for (int j = 0; j < m_1; j += 2)
        {
            rowFactor[i] += M1.matrix[i][j]*M1.matrix[i][j+1];
        }
    }
 
    // II Сумма столбцов
    int columnFactor[M2.m];
    for (int i = 0; i < M2.m; i++)
    {
        columnFactor[i] = 0;
        for (int j = 0; j < m_1; j += 2)
        {
            columnFactor[i] += M2.matrix[j][i] * M2.matrix[j+1][i];
        }
    }
 
 
    // III Вычисление R
    for (int i = 0; i < M1.n; i++)
    {
        for (int j = 0; j < M2.m; j++)
        {
            result[i][j] = -rowFactor[i] - columnFactor[j];
            for (int k = 0; k < m_1; k += 2)
            {
                result[i][j] += (M1.matrix[i][k] + M2.matrix[k+1][j])*(M1.matrix[i][k+1] + M2.matrix[k][j]);
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
                result[i][j] += M1.matrix[i][m_1]*M2.matrix[m_1][j];
            }
        }
    }
 
    return result;
}