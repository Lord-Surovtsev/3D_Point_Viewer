#ifndef POINT2D_H
#define POINT2D_H

#include "NormImgCoord.h"

template<class A>
class Point2D
{
public:
    Point2D(A x = 0, A y = 0)
    {
        _x = x;
        _y = y;
    }

    Point2D(const Point2D& p)
    {
        _x = p._x;
        _y =p._y;
    }

    virtual ~Point2D()
    {

    }

    Point2D& operator= (const Point2D& other)
    {
        if (this != &other)
        {
            _x = other._x;
            _y = other._y;
        }
        return *this;
    }

    operator NormImgCoord<A>()
    {
        return NormImgCoord<A>(_x, _y);
    }

    A getX()
    {
        return _x;
    }

    A getY()
    {
        return _y;
    }

    void setX(A x)
    {
        _x = x;
    }

    void setY(A y)
    {
        _y = y;
    }

private:
    A _x;
    A _y;
};

#endif // POINT2D_H
