#ifndef NORMIMGCOORD_H
#define NORMIMGCOORD_H

#include "Matrix.h"

template<class A>
class NormImgCoord: public Matrix<A>
{
public:
    NormImgCoord(): Matrix<A>(1, 3)
    {
    }

    NormImgCoord(A x, A y): Matrix<A>(1, 3)
    {
        this[0][0] = x;
        this[0][1] = y;
        this[0][2] = 1;
    }

    NormImgCoord(const NormImgCoord<A>& obj): Matrix<A>(1, 3)
    {
        this[0][0] = obj[0][0];
        this[0][1] = obj[0][1];
        this[0][2] = 1;
    }
};

#endif // NORMIMGCOORD_H
