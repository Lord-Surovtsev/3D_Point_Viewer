#ifndef MATHIMPLIMINTATION_H
#define MATHIMPLIMINTATION_H

#include "Matrix.h"
#include "CustomException.h"

template<class A>
Matrix<A> MultMatr(Matrix<A>& m1, Matrix<A>& m2)
{

    if (m1.getCol() != m2.getRow())
    {
        throw new CustomException("wrong size");
    }
    Matrix<A> result(m2.getCol(), m1.getRow());

    for (int i = 0; i < m2.getCol(); i++)
    {
        for (int j = 0; j < m1.getRow(); j++)
        {
            A sum = 0;
            for (int k = 0; k < m1.getCol(); k++)
            {
                sum += m1[k][j] * m2[i][k];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

template<class A>
Point3D<A> Mult(Point3D<A>& p, Matrix<A>& m)
{
    if ((m.getCol() != 4) || (m.getRow() != 4))
    {
        throw new CustomException("wrong size");
    }
    Point3D<A> result;
    result.setX(m[0][0] * p.getX() + m[1][0] * p.getY() + m[2][0] * p.getZ() + m[3][0]);
    result.setY(m[0][1] * p.getX() + m[1][1] * p.getY() + m[2][1] * p.getZ() + m[3][1]);
    result.setZ(m[0][2] * p.getX() + m[1][2] * p.getY() + m[2][2] * p.getZ() + m[3][2]);

    return result;
}

template<class A>
Matrix<A> ResizeMatrix(Matrix<A>& m, int newCol, int newRow)
{
    Matrix<A> result(newCol, newRow);
    int col = m.getCol();
    int row = m.getRow();
    if (newRow > m.getRow())
    {
        for (int i = 0; i < newCol; i++)
        {
            for (int j = row; j < newRow; j++)
            {
                result[i][j] = 0;
            }
        }
    }
    for (int i = col; i < newCol; i++)
    {
        for (int j = 0; j < row; j++)
        {
            result[i][j] = 0;
        }
    }
    if (newCol < m.getCol())
    {
        col = newCol;
    }
    if (newRow < row)
    {
        row = newRow;
    }

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            result[i][j] = m[i][j];
        }
    }
    return result;
}

template<class A>
Matrix<A> Transpose(Matrix<A> m)
{
    int col = m.getRow();
    int row = m.getCol();

    Matrix<A> result(col, row);

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            result[i][j] = m[j][i];
        }
    }
    return result;
}

#endif // MATHIMPLIMINTATION_H
