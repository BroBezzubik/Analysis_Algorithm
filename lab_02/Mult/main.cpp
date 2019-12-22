#include "list.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int **multiMatrixStd(ivMatrix M1, ivMatrix M2);
int **multiMatrixVin(ivMatrix M1, ivMatrix M2);
int **multiMatrixVin2(ivMatrix M1, ivMatrix M2);

void printMatrix(ivMatrix &m){
    for (int i = 0; i < 3; i++){

        for (int j = 0; j < 3; j++){

            cout << m.matrix[i][j];

        }

        cout << endl;

    }
}

int main(){

   ivMatrix a;
   a.m = 3; a.n = 3;


   a.matrix = new int*[3];
   for (int i = 0; i < 3; i++){

       a.matrix[i] = new int[3];
       for (int j = 0; j < 3; j++){

           a.matrix[i][j] = j;

       }
   }

  ivMatrix b;
  b.m = 3; b.n = 3;

  b.matrix = new int*[3];
  for (int i = 0; i < 3; i++){

      b.matrix[i] = new int[3];
      for (int j = 0; j < 3; j++){

          b.matrix[i][j] = 0;

      }
  }

  b.matrix[0][0] = 1;
  b.matrix[1][1] = 1;
  b.matrix[2][2] = 1;

  cout << "Matrix a and matrix b: " << endl;
  printMatrix(a);
  cout << endl;
  printMatrix(b);

  ivMatrix c;

  c.matrix = multiMatrixStd(a, b);
  cout << endl << "Classic: " << endl;
  printMatrix(c);


  c.matrix = multiMatrixVin(a, b);
  cout << endl << "Vin" << endl;
  printMatrix(c);

  c.matrix = multiMatrixVin2(a, b);
  cout << endl << "Vin mod" << endl;
  printMatrix(c);


}


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


int **multiMatrixVin2(ivMatrix M1,  ivMatrix M2){
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
