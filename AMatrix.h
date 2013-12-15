#ifndef AMATRIX_H
#define AMATRIX_H

#include "JoinedCoordinates.h"
#include "Gauss-JordanEllumination.h"
//#include "CustomException.h"

class AMatrix
{
public:
    AMatrix(JoinedCoordinates** jCs, int count)
    {
        _rowCount = 0;
        for (int i = 0; i < count; i++)
        {
            if (NULL != jCs[i])
            {
                _rowCount++;
            }
        }

        _matrix = new double*[9];
        for (int i = 0; i < 9; i++)
        {
            _matrix[i] = new double[_rowCount];
        }

        int pos = 0;
        for (int i =0; i < count; i++)
        {
            JoinedCoordinates* jC = jCs[i];
            if (NULL != jC)
            {
                for (int j = 0; j < 9; j++)
                {
                    _matrix[j][pos] = jC->get(j);
                }
                pos++;
                if (pos == _rowCount)
                {
                    break;
                }
            }
        }
    }

    virtual ~AMatrix()
    {
        for (int i = 0; i < 9; i++)
        {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }

    double** getMatrix()
    {
        return _matrix;
    }

    int getColCount()
    {
        return 9;
    }

    int getRowCount()
    {
        return _rowCount;
    }

    void SimplifyMatrix()
    {
        EliminateMatrix(_matrix, 9, _rowCount);
    }

    double* getDiag()
    {
//        if (_rowCount < 9)
//        {
//            throw new CustomException("the rowCount is lower than 9");
//        }
        double* result = new double[_rowCount];
        for (int i = 0; i < _rowCount; i++)
        {
            result[i] = _matrix[i][i];
        }
        return result;
    }

private:
    double** _matrix;
    int _rowCount;
};

#endif // AMATRIX_H
