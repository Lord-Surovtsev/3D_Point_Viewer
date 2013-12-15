#ifndef ARRAY_H
#define ARRAY_H

#include "CustomException.h"

template <class A>
class Array{
public:
    Array()
    {
        _col = 0;
        _array = NULL;
    }

    Array(int col)
    {
        _col = col;
        if (col < 0)
            _col = 0;
        if (_col == 0)
        {
            _array = NULL;
        }
        else
        {
            _array = new A[_col];
        }
        for (int i = 0; i < _col; i++)
        {
            _array[i] = NULL;
        }
    }

//    Array(const Array<A>& other)
//    {
//        _col = other._col;
//        if (_col == 0)
//        {
//            _array = NULL;
//        }
//        else
//        {
//            _array = new A[_col];
//            std::copy(other._array, other._array + other._col, _array);
//        }
//    }

    Array<A>& operator= (const Array<A>& other)
    {
        if (this != &other)
        {
            _col = other._col;
            if (_array != NULL)
            {
                delete[] _array;
            }
            if (_col == 0)
            {
                _array = NULL;
            }
            else
            {
                _array = new A[_col];
                std::copy(other._array, other._array + other._col, _array);
            }
        }
        return *this;
    }

    virtual ~Array()
    {
        if (_array != NULL)
        {
            delete[] _array;
        }
    }

    A& operator[] (const int nIndex)
    {
        if ((nIndex < 0) || (nIndex >= _col))
            throw new CustomException("wrong index");
        return _array[nIndex];
    }

private:
    int _col;
    A* _array;
};

#endif // ARRAY_H
