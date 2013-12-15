#ifndef MATRIX_H
#define MATRIX_H

#include "Array.h"
#include "CustomException.h"

#include <iostream>
using namespace std;

template<class A>
class Matrix{
public:
    Matrix(int col, int row)
    {
        _col = col;
        _row = row;
        if (col < 0)
            _col = 0;
        if (row < 0)
            _row = 0;
        if (_col == 0)
        {
            _array = NULL;
        }
        else
        {
            _array = new Array<A>[_col];
        }
        for (int i = 0; i < col; i++)
        {
            _array[i] = Array<A>(_row);
        }
    }

    Matrix(const Matrix<A>& other)
    {
//        cout << "copy constructor\n";
//        cout.flush();
        _col = other._col;
        _row = other._row;
        if (_col == 0)
        {
            _array = NULL;
        }
        else
        {
            _array = new Array<A>[_col];
            std::copy(other._array, other._array + other._col, _array);
        }
    }

    Matrix<A>& operator= (const Matrix<A>& other)
    {
//        cout << "operator=\n";
//        cout.flush();
        if (this != &other)
        {
            _col = other._col;
            _row = other._row;
            if (_array == NULL)
            {
                delete[] _array;
            }
            if (_col == 0)
            {
                _array = NULL;
            }
            else
            {
                _array = new Array<A>[_col];
                std::copy(other._array, other._array + other._col, _array);
            }
        }
        return *this;
    }

    virtual ~Matrix()
    {
        if (_array != NULL)
        {
            delete[] _array;
        }
    }

    int getCol()
    {
        return _col;
    }

    int getRow()
    {
        return _row;
    }

    Array<A>& operator[] (const int nIndex)
    {
        if ((nIndex < 0) || (nIndex >= _col))
            throw new CustomException("wrong index");
        return _array[nIndex];
    }

//    A get(int col, int row)
//    {
//        if ((col >= _col) || (row >= _row)
//         || (col < 0) || (row < 0))
//            throw CustomException("wrong index");
//        return _array[col][row];
//    }

//    void set(int col, int row, A elem)
//    {
//        if ((col >= _col) || (row >= _row)
//         || (col < 0) || (row < 0))
//            throw CustomException("wrong index");
//        _array[col][row] = elem;
//    }

    void Print()
    {
        int c = _col;
        int r = _row;
        for (int j = 0; j < r; j++)
        {
            for (int i = 0; i < c; i++)
            {
                cout << _array[i][j] << " ";
            }
            cout << "\n";
        }
        cout.flush();
    }

    void Print(string name)
    {
        cout << "--------- " << name << endl;
        int c = _col;
        int r = _row;
        for (int j = 0; j < r; j++)
        {
            for (int i = 0; i < c; i++)
            {
                cout << _array[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "----------------" << endl;
        cout.flush();
    }

private:
    int _col;
    int _row;
    Array<A>* _array;

};

#endif // MATRIX_H
