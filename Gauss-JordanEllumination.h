#ifndef GAUSSJORDANELLUMINATION_H
#define GAUSSJORDANELLUMINATION_H

#include <cmath>
using namespace std;

void DeleteRow(double** matrix, int from, int what, int pos, int colCount, int rowCount)
{
    double up = matrix[pos][from];
    double down = matrix[pos][what];
    double min = 0.000000000001;
    if (up == 0 || down == 0)
    {
        return;
    }
    for (int i = 0; i < colCount; i++)
    {
        matrix[i][from] -= matrix[i][what] / down * up;
        if (abs(matrix[i][from]) < min)
        {
            matrix[i][from] = 0;
        }
    }
}

void AddRow(double** matrix, int to, int what, int colCount, int rowCount)
{
    for (int i = 0; i < colCount; i++)
    {
        matrix[i][to] += matrix[i][what];
    }
}

void EliminateMatrix(double** matrix, int colCount, int rowCount)//, iliminateMode mode)
{
    if (colCount == 0)
    {
        return;
    }
    int i = 0;
    int j = 0;
    while (i < colCount)
    {
        if (j >= rowCount)
        {
            break;
        }
        if (0 == matrix[i][j])
        {
            for (int k = j + 1; k < rowCount; k++)
            {
                if (0 != matrix[i][k])
                {
                    AddRow(matrix, j, k, colCount, rowCount);
                    break;
                }
            }
            i++;
            continue;
        }
        for (int k = 0; k < j; k++)
        {
            DeleteRow(matrix, k, j, i, colCount, rowCount);
        }
        for (int k = (j + 1); j < rowCount; k++)
        {
            DeleteRow(matrix, k, j, i, colCount, rowCount);
        }
    }
 /*
    for (int i = 0; (i < rowCount) && (i < colCount); i++)
    {
        for (int k = 0; (k + i) < colCount; k++)
        {
        //int k = 0;
            if (matrix[i + k][i] == 0)
            {
                for (int j = i + 1; j < rowCount; j++)
                {
                    if (matrix[i][j] != 0)
                    {
                        AddRow(matrix, i, j, colCount, rowCount);
                        break;
                    }
                }
            }
            if (matrix[i + k][i] == 0)
            {
                continue;
            }
            for (int j = i + 1; j < rowCount; j++)
            {
                DeleteRow(matrix, j, i, i + k, colCount, rowCount);
            }
            //Print(matrix);
            break;
        }
    }
    //for (int i = 0; i < colCount; i++)
    //{
    //    for (int j = 0; j < rowCount; j++)
    //    {
    //        if (matrix[i][j] == 0)
    //        {
    //            for (int k = i + 1; k < rowCount; k++)
    //            {
    //                if (matrix[i][k] != 0)
    //                {
    //                    AddRow(matrix, i, k);
    //                    break;
    //                }
    //            }
    //        }
    //        if (matrix[i][j] == 0)
    //        {
    //            continue;
    //        }
    //        for (int k = i + 1; k < rowCount; k++)
    //        {
    //            DeleteRow(matrix, k, i, i);
    //            //Print(matrix);
    //        }
    //        break;
    //    }
    //}
    //if (mode == iliminateMode.forFindXYZ)
    //{
    //    for (int j = 0; j < rowCount; j++)
    //    {
    //        int count = 0;
    //        for (int i = 0; i < colCount; i++)
    //        {
    //            if (matrix[i][j] != 0)
    //            {
    //                count++;
    //            }
    //        }
    //        if (count == 1)
    //        {
    //            for (int i = 0; i < colCount; i++)
    //            {
    //                matrix[i][j] = 0;
    //            }
    //        }
    //    }
    //}
    if (true)
    {
        for (int i = 1; i < rowCount; i++)
        {
            for (int j = 0; j < colCount; j++)
            {
                if (matrix[j][i] != 0)
                {
                    for (int k = 0; k < i; k++)
                    {
                        DeleteRow(matrix, k, i, j, colCount, rowCount);
                    }
                    //Print(matrix);
                    break;
                }
            }
        }
    }
*/
    //Console.WriteLine("-------------rref(matrix)----------");
    //Print(matrix);
    //Console.WriteLine("------------/rref(matrix)----------");
}

#endif // GAUSSJORDANELLUMINATION_H
